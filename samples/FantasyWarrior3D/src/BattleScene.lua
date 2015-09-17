require "Helper"
require "Manager"
require "MessageDispatchCenter"
require "GlobalVariables"

currentLayer = nil
uiLayer = nil
gameMaster = nil
local specialCamera = {valid = false, position = cc.p(0,0)}
local size = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()
local cameraOffset =  cc.V3(150, 0, 0)
local cameraOffsetMin = {x=-300, y=-400}
local cameraOffsetMax = {x=300, y=400}

local function moveCamera(dt)
    --cclog("moveCamera")
    if camera == nil then return end

    local cameraPosition = getPosTable(camera)
    local focusPoint = getFocusPointOfHeros()
    if specialCamera.valid == true then
        local position = cc.pLerp(cameraPosition, cc.p(specialCamera.position.x, (cameraOffset.y + focusPoint.y-size.height*3/4)*0.5), 5*dt)
        
        camera:setPosition(position)
        camera:lookAt(cc.V3(position.x, specialCamera.position.y, 50.0), cc.V3(0.0, 1.0, 0.0))
    elseif List.getSize(HeroManager) > 0 then
        local temp = cc.pLerp(cameraPosition, cc.p(focusPoint.x+cameraOffset.x, cameraOffset.y + focusPoint.y-size.height*3/4), 2*dt)
        local position = cc.V3(temp.x, temp.y, size.height/2-100)
        camera:setPosition3D(position)
        camera:lookAt(cc.V3(position.x, focusPoint.y, 50.0), cc.V3(0.0, 0.0, 1.0))
        --cclog("\ncalf %f %f %f \ncalf %f %f 50.000000", position.x, position.y, position.z, focusPoint.x, focusPoint.y)            
    end
end

local function updateParticlePos()
    --cclog("updateParticlePos")
    for val = HeroManager.first, HeroManager.last do
        local sprite = HeroManager[val]
        if sprite._effectNode ~= nil then        
            sprite._effectNode:setPosition(getPosTable(sprite))
        end
    end
end

local function createBackground()
    local spriteBg = cc.Sprite3D:create("model/scene/changing.c3b")

    currentLayer:addChild(spriteBg)
    spriteBg:setScale(2.65)
    spriteBg:setPosition3D(cc.V3(-2300,-1000,0))
    spriteBg:setRotation3D(cc.V3(90,0,0))
    spriteBg:setGlobalZOrder(-10)
        
    local water = cc.Water:create("shader3D/water.png", "shader3D/wave1.jpg", "shader3D/18.jpg", {width=5500, height=400}, 0.77, 0.3797, 1.2)
    currentLayer:addChild(water)
    water:setPosition3D(cc.V3(-3500,-580,-110))
    water:setAnchorPoint(0,0)
    water:setGlobalZOrder(-10)
    
end

local function setCamera()
    camera = cc.Camera:createPerspective(60.0, size.width/size.height, 10.0, 4000.0)
    camera:setGlobalZOrder(10)
    camera:setCameraFlag(UserCameraFlagMask)
    currentLayer:addChild(camera)
    currentLayer:setCameraMask(UserCameraFlagMask)

    for val = HeroManager.first, HeroManager.last do
        local sprite = HeroManager[val]
        if sprite._puff then
            sprite._puff:setCamera(camera)
        end
    end      
    
    uiLayer:setCameraMask(UserCameraFlagMask)
    camera:addChild(uiLayer)
end

local function gameController(dt)
    gameMaster:update(dt)
    collisionDetect(dt)
    solveAttacks(dt)
    moveCamera(dt)
end

local function initUILayer()
    uiLayer = require("BattleFieldUI").create()

    uiLayer:setPositionZ(-cc.Director:getInstance():getZEye()/4)
    uiLayer:setScale(0.25)
    uiLayer:ignoreAnchorPointForPosition(false)
    uiLayer:setGlobalZOrder(3000)
end

local BattleScene = class("BattleScene",function()
    return cc.Scene:create()
end)

local function bloodMinus(heroActor)
        uiLayer:bloodDrop(heroActor)
end

local function angryChange(angry)
        uiLayer:angryChange(angry)
end

local function specialPerspective(param)
    if specialCamera.valid == true then return end
    
    specialCamera.position = param.pos
    specialCamera.valid = true
    currentLayer:setColor(cc.c3b(125, 125, 125))--deep grey

    local function restoreTimeScale()
        specialCamera.valid = false
        currentLayer:setColor(cc.c3b(255, 255, 255))--default white        
        cc.Director:getInstance():getScheduler():setTimeScale(1.0)
        param.target:setCascadeColorEnabled(true)--restore to the default state  
    end    
    delayExecute(currentLayer, restoreTimeScale, param.dur)

    cc.Director:getInstance():getScheduler():setTimeScale(param.speed)
end

function BattleScene:enableTouch()
    local function onTouchBegin(touch,event)
        --cclog("onTouchBegin: %0.2f, %0.2f", touch:getLocation())        
        return true
    end
    
    local function onTouchMoved(touch,event)
        if self:UIcontainsPoint(touch:getLocation()) == nil then
            local delta = touch:getDelta()
            cameraOffset = cc.pGetClampPoint(cc.pSub(cameraOffset, delta),cameraOffsetMin,cameraOffsetMax)
        end
    end
    
    local function onTouchEnded(touch,event)
        local location = touch:getLocation()
        local message = self:UIcontainsPoint(location)
        if message ~= nil then
            MessageDispatchCenter:dispatchMessage(message, 1)            
        end
    end

    local touchEventListener = cc.EventListenerTouchOneByOne:create()
    touchEventListener:registerScriptHandler(onTouchBegin,cc.Handler.EVENT_TOUCH_BEGAN)
    touchEventListener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED)
    touchEventListener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED)
    currentLayer:getEventDispatcher():addEventListenerWithSceneGraphPriority(touchEventListener, currentLayer)        
end

function BattleScene:UIcontainsPoint(position)
    local message  = nil

    local rectKnight = uiLayer.KnightPngFrame:getBoundingBox()
    local rectArcher = uiLayer.ArcherPngFrame:getBoundingBox()
    local rectMage = uiLayer.MagePngFrame:getBoundingBox()
    
    if cc.rectContainsPoint(rectKnight, position) and uiLayer.KnightAngry:getPercentage() == 100 then
        --cclog("rectKnight")
        message = MessageDispatchCenter.MessageType.SPECIAL_KNIGHT        
    elseif cc.rectContainsPoint(rectArcher, position) and uiLayer.ArcherAngry:getPercentage() == 100  then
        --cclog("rectArcher")
        message = MessageDispatchCenter.MessageType.SPECIAL_ARCHER   
    elseif cc.rectContainsPoint(rectMage, position)  and uiLayer.MageAngry:getPercentage() == 100 then
        --cclog("rectMage")
        message = MessageDispatchCenter.MessageType.SPECIAL_MAGE         
    end   
        
    return message 
end

function BattleScene.create()
    local scene = BattleScene:new()
    currentLayer = cc.Layer:create()
    currentLayer:setCascadeColorEnabled(true)
    scene:addChild(currentLayer)

    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RG_B565)

    scene:enableTouch()    
    createBackground()
    initUILayer()
    gameMaster = require("GameMaster").create()
    setCamera()
    gameControllerScheduleID = scheduler:scheduleScriptFunc(gameController, 0, false)

    MessageDispatchCenter:registerMessage(MessageDispatchCenter.MessageType.BLOOD_MINUS, bloodMinus)
    MessageDispatchCenter:registerMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, angryChange)
    MessageDispatchCenter:registerMessage(MessageDispatchCenter.MessageType.SPECIAL_PERSPECTIVE,specialPerspective)

    return scene
end

return BattleScene
