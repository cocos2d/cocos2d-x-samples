require "GlobalVariables"
require "Actor"

local BattlefieldUI = class("battlefieldUI",function() return cc.Layer:create() end)

function BattlefieldUI.create()
    local layer = BattlefieldUI.new()
	return layer
end

function BattlefieldUI:ctor()
    self:avatarInit()
    self:bloodbarInit()
    self:angrybarInit()
    self:touchButtonInit()
    self:timeInit()
--    self:showVictoryUI()
    
    ccexp.AudioEngine:stopAll()
    AUDIO_ID.BATTLEFIELDBGM = ccexp.AudioEngine:play2d(BGM_RES.BATTLEFIELDBGM, true,0.6)
end

function BattlefieldUI:avatarInit()

    local offset = 8
    local scale =0.7
    self.MagePng = cc.Sprite:createWithSpriteFrameName("UI-1136-640_18.png")
    self.MagePng:setPosition3D(cc.V3(1070/1136*G.winSize.width,70/640*G.winSize.height,2))
    self.MagePng:setScale(scale)    
    self:addChild(self.MagePng,2)
    self.MagePngFrame = cc.Sprite:createWithSpriteFrameName("UI-2.png")
    self.MagePngFrame:setScale(scale)
    self.MagePngFrame:setPosition3D(cc.V3(self.MagePng:getPositionX()+1,self.MagePng:getPositionY()-offset,1))
    self:addChild(self.MagePngFrame,1)
    
    self.KnightPng = cc.Sprite:createWithSpriteFrameName("UI-1136-640_03.png")
    self.KnightPng:setPosition3D(cc.V3(-self.MagePng:getContentSize().width*2 + self.MagePng:getPositionX()+40,70/640*G.winSize.height,2))
    self.KnightPng:setScale(scale)
    self:addChild(self.KnightPng,2)           
    self.KnightPngFrame = cc.Sprite:createWithSpriteFrameName("UI-2.png")
    self.KnightPngFrame:setScale(scale)
    self.KnightPngFrame:setPosition3D(cc.V3(self.KnightPng:getPositionX()+1,self.KnightPng:getPositionY()-offset,1))
    self:addChild(self.KnightPngFrame,1)
     
    self.ArcherPng = cc.Sprite:createWithSpriteFrameName("UI-1136-640_11.png")
    self.ArcherPng:setPosition3D(cc.V3(-self.MagePng:getContentSize().width + self.MagePng:getPositionX()+20,70/640*G.winSize.height,2))
    self.ArcherPng:setScale(scale)
    self:addChild(self.ArcherPng,2)
    self.ArcherPngFrame = cc.Sprite:createWithSpriteFrameName("UI-2.png")
    self.ArcherPngFrame:setScale(scale)
    self.ArcherPngFrame:setPosition3D(cc.V3(self.ArcherPng:getPositionX()+1,self.ArcherPng:getPositionY()-offset,1))
    self:addChild(self.ArcherPngFrame,1)
    

end

function BattlefieldUI:bloodbarInit()

    local offset = 45
    local scale = 0.7
    self.KnightBlood = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.KnightBlood:setColor(cc.c3b(149,254,26))
    self.KnightBlood:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.KnightBlood:setBarChangeRate(cc.vertex2F(1,0))
    self.KnightBlood:setMidpoint(cc.vertex2F(0,0))
    self.KnightBlood:setPercentage(100)
    self.KnightBlood:setPosition3D(cc.V3(self.KnightPng:getPositionX()-1, self.KnightPng:getPositionY()-offset,4))
    self.KnightBlood:setScale(scale)
    self:addChild(self.KnightBlood,4)
        
    self.KnightBloodClone = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.KnightBloodClone:setColor(cc.c3b(255,83,23))
    self.KnightBloodClone:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.KnightBloodClone:setBarChangeRate(cc.vertex2F(1,0))
    self.KnightBloodClone:setMidpoint(cc.vertex2F(0,0))
    self.KnightBloodClone:setPercentage(100)
    self.KnightBloodClone:setPosition3D(cc.V3(self.KnightPng:getPositionX()-1, self.KnightPng:getPositionY()-offset,3))
    self.KnightBloodClone:setScale(scale)
    self:addChild(self.KnightBloodClone,3)
        
    self.ArcherBlood = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.ArcherBlood:setColor(cc.c3b(149,254,26))
    self.ArcherBlood:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.ArcherBlood:setMidpoint(cc.vertex2F(0,0))
    self.ArcherBlood:setBarChangeRate(cc.vertex2F(1,0))
    self.ArcherBlood:setPercentage(100)
    self.ArcherBlood:setPosition3D(cc.V3(self.ArcherPng:getPositionX()-1, self.ArcherPng:getPositionY()-offset,4))
    self.ArcherBlood:setScale(scale)
    self:addChild(self.ArcherBlood,4)

    self.ArcherBloodClone = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.ArcherBloodClone:setColor(cc.c3b(255,83,23))
    self.ArcherBloodClone:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.ArcherBloodClone:setBarChangeRate(cc.vertex2F(1,0))
    self.ArcherBloodClone:setMidpoint(cc.vertex2F(0,0))
    self.ArcherBloodClone:setPercentage(100)
    self.ArcherBloodClone:setPosition3D(cc.V3(self.ArcherPng:getPositionX()-1, self.ArcherPng:getPositionY()-offset,3))
    self.ArcherBloodClone:setScale(scale)
    self:addChild(self.ArcherBloodClone,3)
 
    self.MageBlood = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.MageBlood:setColor(cc.c3b(149,254,26))
    self.MageBlood:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.MageBlood:setMidpoint(cc.vertex2F(0,0))
    self.MageBlood:setBarChangeRate(cc.vertex2F(1,0))
    self.MageBlood:setPercentage(100)
    self.MageBlood:setPosition3D(cc.V3(self.MagePng:getPositionX()-1, self.MagePng:getPositionY()-offset,4))
    self.MageBlood:setScale(scale)
    self:addChild(self.MageBlood,4)
    
    self.MageBloodClone = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.MageBloodClone:setColor(cc.c3b(255,83,23))
    self.MageBloodClone:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.MageBloodClone:setBarChangeRate(cc.vertex2F(1,0))
    self.MageBloodClone:setMidpoint(cc.vertex2F(0,0))
    self.MageBloodClone:setPercentage(100)
    self.MageBloodClone:setPosition3D(cc.V3(self.MagePng:getPositionX()-1, self.MagePng:getPositionY()-offset,3))
    self.MageBloodClone:setScale(scale)
    self:addChild(self.MageBloodClone,3)
end

function BattlefieldUI:angrybarInit()

    local offset = 53
    local fullAngerStarOffset=70
    local yellow = cc.c3b(255,255,0)
    local grey = cc.c3b(113,103,76)
    local action = cc.RepeatForever:create(cc.RotateBy:create(1,cc.V3(0,0,360)))

    self.KnightAngry = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.KnightAngry:setColor(yellow)
    self.KnightAngry:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.KnightAngry:setBarChangeRate(cc.vertex2F(1,0))
    self.KnightAngry:setMidpoint(cc.vertex2F(0,0))
    self.KnightAngry:setPercentage(0)
    self.KnightAngry:setPosition3D(cc.V3(self.KnightPng:getPositionX()-1, self.KnightPng:getPositionY() - offset,4))
    self.KnightAngry:setScale(0.7)
    self:addChild(self.KnightAngry,4)

    self.KnightAngryClone = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.KnightAngryClone:setColor(grey)
    self.KnightAngryClone:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.KnightAngryClone:setBarChangeRate(cc.vertex2F(1,0))
    self.KnightAngryClone:setMidpoint(cc.vertex2F(0,0))
    self.KnightAngryClone:setPercentage(100)
    self.KnightAngryClone:setPosition3D(cc.V3(self.KnightPng:getPositionX()-1, self.KnightPng:getPositionY() - offset,3))
    self.KnightAngryClone:setScaleX(0.7)
    self.KnightAngryClone:setScaleY(0.75)
    self:addChild(self.KnightAngryClone,3)
    
    self.KnightAngryFullSignal = cc.Sprite:createWithSpriteFrameName("specialLight.png")
    self.KnightAngryFullSignal:setPosition3D(cc.V3(self.KnightPng:getPositionX(), self.KnightPng:getPositionY() + fullAngerStarOffset,4))
    self.KnightAngryFullSignal:runAction(action)
    self.KnightAngryFullSignal:setScale(1)
    self:addChild(self.KnightAngryFullSignal,4)
    self.KnightAngryFullSignal:setVisible(false)

    self.ArcherAngry = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.ArcherAngry:setColor(yellow)
    self.ArcherAngry:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.ArcherAngry:setMidpoint(cc.vertex2F(0,0))
    self.ArcherAngry:setBarChangeRate(cc.vertex2F(1,0))
    self.ArcherAngry:setPercentage(0)
    self.ArcherAngry:setPosition3D(cc.V3(self.ArcherPng:getPositionX()-1, self.ArcherPng:getPositionY() - offset,4))
    self.ArcherAngry:setScale(0.7)
    self:addChild(self.ArcherAngry,4)

    self.ArcherAngryClone = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.ArcherAngryClone:setColor(grey)
    self.ArcherAngryClone:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.ArcherAngryClone:setBarChangeRate(cc.vertex2F(1,0))
    self.ArcherAngryClone:setMidpoint(cc.vertex2F(0,0))
    self.ArcherAngryClone:setPercentage(100)
    self.ArcherAngryClone:setPosition3D(cc.V3(self.ArcherPng:getPositionX()-1, self.ArcherPng:getPositionY() - offset,3))
    self.ArcherAngryClone:setScaleX(0.7)
    self.ArcherAngryClone:setScaleY(0.75)
    self:addChild(self.ArcherAngryClone,3)

    self.ArcherAngryFullSignal = cc.Sprite:createWithSpriteFrameName("specialLight.png")
    self.ArcherAngryFullSignal:setPosition3D(cc.V3(self.ArcherPng:getPositionX(), self.ArcherPng:getPositionY() + fullAngerStarOffset,4))
    self:addChild(self.ArcherAngryFullSignal,4)
    self.ArcherAngryFullSignal:runAction(action:clone())
    self.ArcherAngryFullSignal:setScale(1)
    self.ArcherAngryFullSignal:setVisible(false)

    self.MageAngry = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.MageAngry:setColor(yellow)
    self.MageAngry:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.MageAngry:setMidpoint(cc.vertex2F(0,0))
    self.MageAngry:setBarChangeRate(cc.vertex2F(1,0))
    self.MageAngry:setPercentage(0)
    self.MageAngry:setPosition3D(cc.V3(self.MagePng:getPositionX()-1, self.MagePng:getPositionY() - offset,4))
    self.MageAngry:setScale(0.7)
    self:addChild(self.MageAngry,4)

    self.MageAngryClone = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("UI-1136-640_36_clone.png"))
    self.MageAngryClone:setColor(grey)
    self.MageAngryClone:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    self.MageAngryClone:setBarChangeRate(cc.vertex2F(1,0))
    self.MageAngryClone:setMidpoint(cc.vertex2F(0,0))
    self.MageAngryClone:setPercentage(100)
    self.MageAngryClone:setPosition3D(cc.V3(self.MagePng:getPositionX()-1, self.MagePng:getPositionY() - offset,3))
    self.MageAngryClone:setScaleX(0.7)
    self.MageAngryClone:setScaleY(0.75)
    self:addChild(self.MageAngryClone,3)
    
    self.MageAngryFullSignal = cc.Sprite:createWithSpriteFrameName("specialLight.png")
    self.MageAngryFullSignal:setPosition3D(cc.V3(self.MagePng:getPositionX(), self.MagePng:getPositionY() + fullAngerStarOffset,4))
    self:addChild(self.MageAngryFullSignal,4)
    self.MageAngryFullSignal:runAction(action:clone())
    self.MageAngryFullSignal:setScale(1)
    self.MageAngryFullSignal:setVisible(false)
end

function BattlefieldUI:touchButtonInit()

    self._setBtn =cc.Sprite:createWithSpriteFrameName("UI-1136-640_06.png")
    self._setBtn:setPosition3D(cc.V3(1093/1136*G.winSize.width,591/640*G.winSize.height,3))
    self._setBtn:setScale(0.8)
    self:addChild(self._setBtn,3)
    
    self._chest = cc.Sprite:createWithSpriteFrameName("chest.png")
    self._chest:setPosition3D(cc.V3(861/1136*G.winSize.width,595/640*G.winSize.height,3))
    self._chest:setScale(0.8)
    self:addChild(self._chest,3)
    
    self._coin = cc.Sprite:createWithSpriteFrameName("coins.png")
    self._coin:setPosition3D(cc.V3(1028.49/1136*G.winSize.width,593/640*G.winSize.height,3))
    self._coin:setScaleX(0.8)
    self._coin:setScaleY(0.8)
    self:addChild(self._coin,3)
    
    self._chestAmount = cc.Sprite:createWithSpriteFrameName("UI-1.png")
    self._chestAmount:setPosition3D(cc.V3(785/1136*G.winSize.width,590/640*G.winSize.height,2))
    self._chestAmount:setScaleX(0.8)
    self._chestAmount:setScaleY(0.7)
    self:addChild(self._chestAmount,2)
    
    self._coinAmount = cc.Sprite:createWithSpriteFrameName("UI-1.png")
    self._coinAmount:setPosition3D(cc.V3(957/1136*G.winSize.width,590/640*G.winSize.height,2))
    self._coinAmount:setScaleX(0.8)
    self._coinAmount:setScaleY(0.7)
    self:addChild(self._coinAmount,2)
end

local scheduleID = nil

function BattlefieldUI:shakeAvatar()
    return cc.Repeat:create(cc.Spawn:create(cc.Sequence:create(cc.ScaleTo:create(0.075,0.75),
                                            cc.ScaleTo:create(0.075,0.7)),
                                            cc.Sequence:create(cc.MoveBy:create(0.05,{x=6.5,y=0}),
                                            cc.MoveBy:create(0.05,{x=-13,y=0}),
                                            cc.MoveBy:create(0.05,{x=6.5,y=0}))),2)
end

function BattlefieldUI:bloodDrop(heroActor)
    local progressTo
    local progressToClone
    local tintTo
    local percent = heroActor._hp/heroActor._maxhp*100
    heroActor._bloodBar:stopAllActions()
    heroActor._bloodBarClone:stopAllActions()
    heroActor._avatar:runAction(BattlefieldUI:shakeAvatar())
    
    if heroActor._hp > 0 and percent>50 then

        progressTo = cc.ProgressTo:create(0.3,percent)
        progressToClone = cc.ProgressTo:create(1,percent)
        heroActor._bloodBar:runAction(progressTo)
        heroActor._bloodBarClone:runAction(progressToClone)
        
    elseif heroActor._hp>0 and percent <=50 then
        
        progressTo = cc.ProgressTo:create(0.3,percent)
        progressToClone = cc.ProgressTo:create(1,percent) 
        tintTo = cc.TintTo:create(0.5,254,225,26)   
        
        heroActor._bloodBar:runAction(cc.Spawn:create(progressTo,tintTo))
        heroActor._bloodBarClone:runAction(progressToClone)
    elseif heroActor._hp>0 and percent <=30 then

        progressTo = cc.ProgressTo:create(0.3,percent)
        progressToClone = cc.ProgressTo:create(1,percent) 
        
        tintTo = cc.TintTo:create(0.5,254,26,69)   
        heroActor._bloodBar:runAction(cc.Spawn:create(progressTo,tintTo))
        heroActor._bloodBarClone:runAction(progressToClone)
    elseif heroActor._hp  <=0 then
        progressTo = cc.ProgressTo:create(0.3,0)
        progressToClone = cc.ProgressTo:create(1,2)
        
        heroActor._bloodBar:runAction(progressTo)
        heroActor._bloodBarClone:runAction(progressToClone)
    end
end


function BattlefieldUI:heroDead(hero)

    if hero._name =="Knight" then
        cc.GreyShader:setGreyShader(self.KnightPng)
        cc.GreyShader:setGreyShader(self.KnightPngFrame)    
        self.KnightAngryFullSignal:setVisible(false)   
        self.KnightAngryClone:setVisible(false)
    elseif hero._name =="Mage" then
        cc.GreyShader:setGreyShader(self.MagePng)
        cc.GreyShader:setGreyShader(self.MagePngFrame)
        self.MageAngryFullSignal:setVisible(false)
        self.MageAngryClone:setVisible(false)
    elseif hero._name=="Archer" then
        cc.GreyShader:setGreyShader(self.ArcherPng)
        cc.GreyShader:setGreyShader(self.ArcherPngFrame)
        self.ArcherAngryFullSignal:setVisible(false)
        self.ArcherAngryClone:setVisible(false)                
    end
end

function BattlefieldUI:angryChange(angry)
    local tintTo
    local percent = angry._angry / angry._angryMax * 100
    local progressTo = cc.ProgressTo:create(0.3,percent)
    local progressToClone = cc.ProgressTo:create(1,percent+2)   
    
    local bar
    if angry._name == KnightValues._name then
        bar = self.KnightAngry
        if percent>=100 then
            self.KnightAngryFullSignal:setVisible(true)
        elseif percent == 0 then
            self.KnightAngryFullSignal:setVisible(false)                
        end
    elseif angry._name == ArcherValues._name then
        bar = self.ArcherAngry
        if percent>=100 then
            self.ArcherAngryFullSignal:setVisible(true)
        elseif percent == 0 then
            self.ArcherAngryFullSignal:setVisible(false)                
        end
    elseif angry._name == MageValues._name then
        bar = self.MageAngry
        if percent>=100 then
            self.MageAngryFullSignal:setVisible(true)
        elseif percent == 0 then
            self.MageAngryFullSignal:setVisible(false)                
        end
    end
    
    bar:runAction(progressTo)
end

function BattlefieldUI:timeInit()
    local tm = {"00","00"}
    tm = table.concat(tm,":")
   
    local ttfconfig = {outlineSize=1,fontSize=25,fontFilePath="fonts/britanic bold.ttf"}
    local tm_label = cc.Label:createWithTTF(ttfconfig,tm)
    tm_label:setAnchorPoint(0,0)
    tm_label:setPosition3D(cc.V3(G.winSize.width*0.02,G.winSize.height*0.915,2))
    tm_label:enableOutline(cc.c4b(0,0,0,255))
    self._tmlabel = tm_label
    self:addChild(tm_label,5)
    --time update
    local time = 0
    local function tmUpdate()
        time = time+1
        if time >= 3600 then
            time = 0
        end
        
        local dev = time
        local min = math.floor(dev/60)        
        local sec = dev%60
        if min<10 then
            min = "0"..min
        end
        if sec<10 then
            sec = "0"..sec
        end
        self._tmlabel:setString(min..":"..sec)
    end

    self._tmSchedule = cc.Director:getInstance():getScheduler():scheduleScriptFunc(tmUpdate,1,false)
end

function BattlefieldUI:showVictoryUI()
    --diable AI

    --color layer
    local layer = cc.LayerColor:create(cc.c4b(10,10,10,150))
    layer:ignoreAnchorPointForPosition(false)
    layer:setPosition3D(cc.V3(G.winSize.width*0.5,G.winSize.height*0.5,0))
    --add victory
    local victory = cc.Sprite:createWithSpriteFrameName("victory.png")
    victory:setPosition3D(cc.V3(G.winSize.width*0.5,G.winSize.height*0.5,3))
    victory:setScale(0.1)
    victory:setGlobalZOrder(UIZorder)
    layer:addChild(victory,1)
    
    --victory runaction
    local action = cc.EaseElasticOut:create(cc.ScaleTo:create(1.5,1))
    victory:runAction(action)
    
    --touch event
    local function onTouchBegan(touch, event)
        return true
    end
    local function onTouchEnded(touch,event)
        --stop schedule
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self._tmSchedule)
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(gameControllerScheduleID)
        --stop sound
        ccexp.AudioEngine:stop(AUDIO_ID.BATTLEFIELDBGM)
        --replace scene
        cc.Director:getInstance():replaceScene(require("ChooseRoleScene"):create())
    end
    local listener = cc.EventListenerTouchOneByOne:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener,layer)
    
    layer:setCameraMask(UserCameraFlagMask)
    self:addChild(layer)
end

return BattlefieldUI