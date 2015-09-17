require "Helper"
require "GlobalVariables"

--declare a class extends scene
local MainMenuScene = class("MainMenuScene",function()
    return cc.Scene:create()
end
)

--constructor init member variable
function MainMenuScene:ctor()
    --get win size
    self.size = cc.Director:getInstance():getVisibleSize()
    self._isBloodLabelShowing = false
    math.randomseed(os.time())
    ccexp.AudioEngine:stopAll()
    AUDIO_ID.MAINMENUBGM = ccexp.AudioEngine:play2d(BGM_RES.MAINMENUBGM, true,1)
end

function MainMenuScene.create()
    local scene = MainMenuScene.new()
    --add layer
    local layer = scene:createLayer()
    scene:addChild(layer)
    
    return scene
end

--crate a main layer
function MainMenuScene:createLayer()
    local mainLayer = cc.Layer:create()
    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_AUTO)
    --add bg
    self:addBg(mainLayer)
    
    --add cloud
    self:addCloud(mainLayer)
    
    --add logo
    self:addLogo(mainLayer)
    
    --add pointlight
    self:addPointLight(mainLayer)
    
    --add button
    self:addButton(mainLayer)
        
    --when replease scene unschedule schedule
    local function onExit(event)
        if "exit" == event then
            cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.logoSchedule)
            cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.scheduleCloudMove)
        end
    end
    mainLayer:registerScriptHandler(onExit)
    
    return mainLayer
end

function MainMenuScene:addLogo(layer)
    --add logo
    local logo = cc.EffectSprite:create("mainmenuscene/logo.png")
    self._logoSize = logo:getContentSize()
    logo:setPosition(self.size.width*0.53,self.size.height*0.55)
    logo:setScale(0.1)
    self._logo = logo
    layer:addChild(logo,4)
    
    local action = cc.EaseElasticOut:create(cc.ScaleTo:create(2,1.1))
    
    logo:runAction(action)
    
    --logo shake
    local time = 0
    --logo animation
    local function logoShake()
        --rand_n = range * math.sin(math.rad(time*speed+offset))
        local rand_x = 0.1*math.sin(math.rad(time*0.5+4356))
        local rand_y = 0.1*math.sin(math.rad(time*0.37+5436)) 
        local rand_z = 0.1*math.sin(math.rad(time*0.2+54325))
        logo:setRotation3D({x=math.deg(rand_x),y=math.deg(rand_y),z=math.deg(rand_z)})
        time = time+1
    end
    self.logoSchedule = cc.Director:getInstance():getScheduler():scheduleScriptFunc(logoShake,0,false)
end

function MainMenuScene:getLightSprite()
    self._lightSprite = cc.Sprite:createWithSpriteFrameName("light.png")
    self._lightSprite:setBlendFunc(gl.ONE,gl.ONE_MINUS_SRC_ALPHA)
    self._lightSprite:setScale(1.2)
    
    self._lightSprite:setPosition3D(cc.vec3(self.size.width*0.5,self.size.height*0.5,0))
    local light_size = self._lightSprite:getContentSize()
    local rotate_top = cc.RotateBy:create(0.05,50)
    local rotate_bottom = cc.RotateBy:create(0.05,-50)
    local origin_degree = 20
    local sprite_scale = 0
    local opacity = 100
    local scale_action = cc.ScaleTo:create(0.07,0.7)
    
    local swing_l1 = cc.Sprite:createWithSpriteFrameName("swing_l1.png")
    swing_l1:setScale(sprite_scale)
    swing_l1:setAnchorPoint(cc.p(1,0))
    swing_l1:setPosition(light_size.width/2,light_size.height/2)
    swing_l1:setRotation(-origin_degree)
    swing_l1:setOpacity(opacity)
    swing_l1:setBlendFunc(gl.ONE , gl.ONE)
    self._lightSprite:addChild(swing_l1,5)
    
    local swing_l2 = cc.Sprite:createWithSpriteFrameName("swing_l2.png")
    swing_l2:setAnchorPoint(cc.p(1,1))
    swing_l2:setScale(sprite_scale)
    swing_l2:setPosition(light_size.width/2,light_size.height/2)
    swing_l2:setRotation(origin_degree)
    swing_l2:setOpacity(opacity)
    self._lightSprite:addChild(swing_l2,5)
    
    local swing_r1 = cc.Sprite:createWithSpriteFrameName("swing_r1.png")
    swing_r1:setAnchorPoint(cc.p(0,0))
    swing_r1:setScale(sprite_scale)
    swing_r1:setPosition(light_size.width/2,light_size.height/2)
    swing_r1:setRotation(origin_degree)
    swing_r1:setOpacity(opacity)
    swing_r1:setBlendFunc(gl.ONE , gl.ONE)
    self._lightSprite:addChild(swing_r1,5)
    
    local swing_r2 = cc.Sprite:createWithSpriteFrameName("swing_r2.png")
    swing_r2:setAnchorPoint(cc.p(0,1))
    swing_r2:setScale(sprite_scale)
    swing_r2:setPosition(light_size.width/2,light_size.height/2)
    swing_r2:setRotation(-origin_degree)
    swing_r2:setOpacity(opacity)
    self._lightSprite:addChild(swing_r2,5)
    
    --runaction
    local sequence_l1 = cc.Sequence:create(rotate_top,rotate_top:reverse())
    local sequence_r1 = cc.Sequence:create(rotate_top:reverse():clone(),rotate_top:clone())
    local sequence_l2 = cc.Sequence:create(rotate_bottom,rotate_bottom:reverse())
    local sequence_r2 = cc.Sequence:create(rotate_bottom:reverse():clone(),rotate_bottom:clone())
    swing_l1:runAction(cc.RepeatForever:create(cc.Spawn:create(sequence_l1,scale_action)))
    swing_r1:runAction(cc.RepeatForever:create(cc.Spawn:create(sequence_r1,scale_action)))
    swing_l2:runAction(cc.RepeatForever:create(cc.Spawn:create(sequence_l2,scale_action)))
    swing_r2:runAction(cc.RepeatForever:create(cc.Spawn:create(sequence_r2,scale_action)))
end

--add pointlight
function MainMenuScene:addPointLight(layer)
    --add pointlight
    self._pointLight = cc.PointLight:create(cc.vec3(0,0,-100),cc.c3b(255,255,255),10000)
    self._pointLight:setCameraMask(1)
    self._pointLight:setEnabled(true)

    --add lightsprite
    self:getLightSprite()
    self._lightSprite:addChild(self._pointLight)
    self:addChild(self._lightSprite,10)
    self._lightSprite:setPositionZ(100)

    -- effectNormalMap
    local effectNormalMapped = cc.EffectNormalMapped:create("mainmenuscene/logo_normal.png");
    effectNormalMapped:setPointLight(self._pointLight)
    effectNormalMapped:setKBump(50)
    self._logo:setEffect(effectNormalMapped)
    
    --action
    local function getBezierAction()
        local bezierConfig1 = {
            cc.p(self.size.width*0.9,self.size.height*0.4),
            cc.p(self.size.width*0.9,self.size.height*0.8),
            cc.p(self.size.width*0.5,self.size.height*0.8)
        }
        local bezierConfig2 = {
            cc.p(self.size.width*0.1,self.size.height*0.8),
            cc.p(self.size.width*0.1,self.size.height*0.4),
            cc.p(self.size.width*0.5,self.size.height*0.4)
        }
        local bezier1 = cc.BezierTo:create(5,bezierConfig1)
        local bezier2 = cc.BezierTo:create(5,bezierConfig2)
        local bezier = cc.Sequence:create(bezier1,bezier2)

        return bezier
    end
    self._lightSprite:runAction(cc.RepeatForever:create(getBezierAction()))
    
    --touch eventlistener
    local function onTouchBegin(touch,event)
        self._lightSprite:stopAllActions()
        
        local location = touch:getLocation()
        self._prePosition = location

        local function movePoint(dt)
            local lightSpritePos = getPosTable(self._lightSprite)
            local point = cc.pLerp(lightSpritePos,self._prePosition,dt*2)
            self._lightSprite:setPosition(point)
            local z = math.sin(math.rad(math.random(0,2*math.pi)))*100+100
            --self._lightSprite:setPositionZ(z)
        end
        self._scheduleMove = cc.Director:getInstance():getScheduler():scheduleScriptFunc(movePoint,0,false)
        
        return true
    end
    local function onTouchMoved(touch,event)
        --again set prePosition
        local location = touch:getLocation()
        self._prePosition = location
        
        self._angle =cc.pToAngleSelf(cc.pSub(location,getPosTable(self._lightSprite)))
    end
    local function onTouchEnded(touch,event)
        --unschedule and stop action
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self._scheduleMove)
        self._lightSprite:stopAllActions()
        --self._lightSprite:setPositionZ(100)
        self._lightSprite:runAction(cc.RepeatForever:create(getBezierAction()))      
    end
    
    --add event listener
    local touchEventListener = cc.EventListenerTouchOneByOne:create()
    touchEventListener:registerScriptHandler(onTouchBegin,cc.Handler.EVENT_TOUCH_BEGAN)
    touchEventListener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED)
    touchEventListener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED)
    layer:getEventDispatcher():addEventListenerWithSceneGraphPriority(touchEventListener,layer)
end

--add button to start game
function MainMenuScene:addButton(layer)
    local isTouchButton = false
    local button_callback = function(sender,eventType)
        if isTouchButton == false then
            isTouchButton = true
            if eventType == ccui.TouchEventType.began then
                ccexp.AudioEngine:play2d(BGM_RES.MAINMENUSTART, false,1)
                ccexp.AudioEngine:stop(AUDIO_ID.MAINMENUBGM)
            	cc.Director:getInstance():replaceScene(require("ChooseRoleScene").create())
            end
        end
    end

    local button = ccui.Button:create("start.png","","",ccui.TextureResType.plistType)
    button:setPosition(self.size.width*0.5,self.size.height*0.15)
    button:addTouchEventListener(button_callback)
    layer:addChild(button,4)
    
    local effectNormalMapped = cc.EffectNormalMapped:create("mainmenuscene/start_normal.png")
    effectNormalMapped:setPointLight(self._pointLight)
    effectNormalMapped:setKBump(100)
    
    local effectSprite = cc.EffectSprite:create("mainmenuscene/start.png")
    effectSprite:setPosition(self.size.width*0.5,self.size.height*0.15)
    layer:addChild(effectSprite,5)
    effectSprite:setEffect(effectNormalMapped)
end

-- cloud action
function MainMenuScene:addCloud(layer)
    --cloud
    local cloud0 = cc.Sprite:createWithSpriteFrameName("cloud1.png")
    local cloud1 = cc.Sprite:createWithSpriteFrameName("cloud1.png")
    local cloud3 = cc.Sprite:createWithSpriteFrameName("cloud2.png")
    
    --setScale
    local scale = 2
    cloud0:setScale(scale)
    cloud1:setScale(scale)
    cloud3:setScale(scale)
    
    --setPosition
    cloud0:setPosition(self.size.width*1.1,self.size.height*0.9)
    cloud1:setPosition(self.size.width*0.38,self.size.height*0.6)
    cloud3:setPosition(self.size.width*0.95,self.size.height*0.5)
    
    --add to layer
    layer:addChild(cloud0,2)
    layer:addChild(cloud1,2)
    layer:addChild(cloud3,2)
    local clouds = {cloud0,cloud1,cloud3}
    
    --move cloud
    local function cloud_move()
        --set cloud move speed
        local offset = {-0.5,-1.0,-1.2}
        for i,v in pairs(clouds) do
            local point = v:getPositionX()+offset[i]
            if(point<-v:getContentSize().width*scale/2) then
                point = self.size.width+v:getContentSize().width*scale/2
            end
            v:setPositionX(point)
        end
    end
    self.scheduleCloudMove = cc.Director:getInstance():getScheduler():scheduleScriptFunc(cloud_move,1/60,false)
end

--bg
function MainMenuScene:addBg(layer)
    --background
    local bg_back = cc.Sprite:create("mainmenuscene/bg.jpg")
    bg_back:setPosition(self.size.width/2,self.size.height/2)
    layer:addChild(bg_back,1)
end

return MainMenuScene