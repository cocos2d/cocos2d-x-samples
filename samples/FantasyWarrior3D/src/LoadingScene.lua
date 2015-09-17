require "ParticleManager"
require "Slime"

local LoadingScene = class("loadingScene",
function ()
    return cc.Scene:create()
end
)

local particleRes = {
    {"FX/iceTrail.plist","iceTrail"},
    {"FX/magic.plist","magic"},
    {"FX/pixi.plist","pixi"},
    {"FX/puffRing.plist","puffRing"},
    {"FX/puffRing2.plist","puffRing2"},
    {"FX/walkingPuff.plist","walkpuff"},
}
local spriteFrameRes = {
    "FX/FX.plist",
    "chooseRole/chooserole.plist",
    "battlefieldUI/battleFieldUI.plist",
    "mainmenuscene/mainmenuscene.plist",
}

function LoadingScene:ctor()
    self._num = table.getn(particleRes)+table.getn(spriteFrameRes)
    self._totalResource = self._num
    self.size = cc.Director:getInstance():getWinSize()
    self._pm = ParticleManager:getInstance()
end

function LoadingScene:create()
    local loadingScene = LoadingScene:new()
    local layer = loadingScene:init()
    loadingScene:addChild(layer)
    return loadingScene
end

function LoadingScene:init()
    local layer = cc.Layer:create()
    
    --add background

    -- Holder for background
    local node3d = cc.Sprite3D:create()

    local background = cc.Sprite:create("loadingscene/bg.jpg")
    background:setPosition(self.size.width/2,self.size.height/2)
    background:setPositionZ(-250)
    background:setScale(1.5)
    background:setGlobalZOrder(-1)

    node3d:addChild(background)
    layer:addChild(node3d)

    
    --add loadingbar
    local loadingbar = ccui.LoadingBar:create("loadingscene/sliderProgress.png")
    loadingbar:setDirection(ccui.LoadingBarDirection.LEFT)
    loadingbar:setPosition(self.size.width/2,self.size.height*0.2)
    loadingbar:setScale(3,2)
    loadingbar:setColor(cc.c3b(0,0,0))
    loadingbar:setOpacity(70)
    loadingbar:setPercent(0)
    local loadingbarSize = loadingbar:getContentSize().width*3
    layer:addChild(loadingbar)
    
    --add label
    self:addLoadingText(layer)
    
    --add slime
    self:slimeAction(layer)
    
    --update
    local update = function(dt)
        self._num = self._num-1
        loadingbar:setPercent((self._totalResource-self._num)/self._totalResource*100)
        --loading text action
        local loadingAction = cc.JumpBy:create(dt,cc.p(0,0),50,1)
        local loadingIndex = (self._totalResource-self._num)%(table.getn(self._loading)+1)
        self._loading[loadingIndex>1 and loadingIndex or 1]:runAction(loadingAction)
        --slime action
        self._slime:runAction(cc.MoveTo:create(dt,cc.p(self._slimeOriginX+loadingbarSize*loadingbar:getPercent()/100,self._slimeOriginY)))
        
        --load resource
        if self._totalResource-self._num > table.getn(particleRes) then
            self:cachedTextureRes()
        else
            self:cachedParticleRes()
        end
        
        --replace scene
        if(self._num == -1) then
            cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self.scheduleID)
            local scene = require("MainMenuScene")
            cc.Director:getInstance():replaceScene(scene:create())
        end
    end
    self.scheduleID = cc.Director:getInstance():getScheduler():scheduleScriptFunc(update,0.1,false)
    
    return layer
end

function LoadingScene:addLoadingText(layer)
    local ttfconfig = {outlineSize=5,fontSize=55,fontFilePath="chooseRole/actor_param.ttf"}
    local loading = {}
    for i,v in pairs({"l","o","a","d","i","n","g"}) do
        loading[i] = cc.Label:createWithTTF(ttfconfig,v)
        loading[i]:enableOutline(cc.c4b(104,151,161,255))
        loading[i]:setPosition(self.size.width*0.13+self.size.width*0.1*i,self.size.height*0.6)
        layer:addChild(loading[i])
    end
    self._loading = loading
end

function LoadingScene:slimeAction(layer)
    local slime = Slime.create()
    slime:setAIEnabled(false)
    self._slimeOriginX = self.size.width*0.2
    self._slimeOriginY = self.size.height*0.3
    slime:setPosition(self._slimeOriginX,self._slimeOriginY)
    slime:setRotation3D({x=-90,y=-90,z=0})
    self._slime = slime
    layer:addChild(slime)
    
    local dur = 0.6
    local bsc = 27

    slime._sprite3d:runAction(cc.RepeatForever:create(
        cc.Spawn:create(
            cc.Sequence:create(
                cc.DelayTime:create(dur/8),
                cc.JumpBy3D:create(dur*7/8, cc.V3(0,0,0),30,1)
            ),
            cc.Sequence:create(
                cc.EaseSineOut:create(cc.ScaleTo:create(dur/8, bsc*1.4, bsc*1.4, bsc*0.75)),
                cc.EaseSineOut:create(cc.ScaleTo:create(dur/8, bsc*0.85, bsc*0.85, bsc*1.3)),
                cc.EaseSineOut:create(cc.ScaleTo:create(dur/8, bsc*1.2, bsc*1.2, bsc*0.9)),
                cc.EaseSineOut:create(cc.ScaleTo:create(dur/8, bsc*0.95, bsc*0.95, bsc*1.1)),
                cc.EaseSineOut:create(cc.ScaleTo:create(dur*4/8, bsc, bsc, bsc))
            )
        )
    ))
end

function LoadingScene:cachedParticleRes()
--    print(particleRes[self._totalResource-self._num][1],particleRes[self._totalResource-self._num][2])
    self._pm:AddPlistData(particleRes[self._totalResource-self._num][1],particleRes[self._totalResource-self._num][2])
end

function LoadingScene:cachedTextureRes()
    if self._num < 0 then
        return
    end
--    print(spriteFrameRes[self._totalResource-self._num-table.getn(particleRes)])
    cc.SpriteFrameCache:getInstance():addSpriteFrames(spriteFrameRes[self._totalResource-self._num-table.getn(particleRes)])
end

return LoadingScene