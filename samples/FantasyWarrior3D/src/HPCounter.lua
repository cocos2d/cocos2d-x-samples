local HPCounter = class("HPCounter",function()
    return cc.Node:create()
end)

function HPCounter:create()
    self._isBlooding = false
    self._num = 0
    return HPCounter.new()
end

function HPCounter:showBloodLossNum(damage,actor,attack)
    local time = 1
    local function getRandomXYZ()
        local rand_x = 20*math.sin(math.rad(time*0.5+4356))
        local rand_y = 20*math.sin(math.rad(time*0.37+5436)) 
        local rand_z = 20*math.sin(math.rad(time*0.2+54325))
        return {x=rand_x,y=rand_y,z=rand_z}
    end
    
    local function getBlood()
        local num = self._num
        local tm = 0.5
        local pointZ = 50
        
        local effect = cc.BillBoard:create()
        local ttfconfig = {outlineSize=7,fontSize=50,fontFilePath="fonts/britanic bold.ttf"}
        local blood = cc.Label:createWithTTF(ttfconfig,"-"..num,cc.TEXT_ALIGNMENT_CENTER,400)
        blood:enableOutline(cc.c4b(0,0,0,255))
        blood:setScale(0.1)
        blood:setGlobalZOrder(FXZorder)
        
        local targetScale = 0.6
        if num > 1000 then 
            blood:setColor(cc.c3b(254,58,19))
        elseif num > 300 then
            targetScale = 0.45
            blood:setColor(cc.c3b(255,247,153))
        else
            targetScale = 0.55
            blood:setColor(cc.c3b(189,0,0))
        end
        
        if actor._racetype ~= EnumRaceType.MONSTER then
            blood:setColor(cc.c3b(0,180,255))
        end
        
        local function getAction()
            local sequence = cc.Sequence:create(cc.EaseElasticOut:create(cc.ScaleTo:create(tm/2,targetScale),0.4),
                cc.FadeOut:create(tm/2),
                cc.RemoveSelf:create(),
                cc.CallFunc:create(function()
                    self._isBlooding=false 
                    self._num = 0
                end)
            )
            local spawn = cc.Spawn:create(sequence,
                cc.MoveBy:create(tm,{x=0,y=0,z=pointZ}),
                cc.RotateBy:create(tm,math.random(-40,40)))
            return spawn
        end
        
        if attack then
            local criticalAttack = cc.Sprite:createWithSpriteFrameName("hpcounter.png")
            criticalAttack:setGlobalZOrder(FXZorder)
            tm = 1
            criticalAttack:runAction(getAction())
            if actor._name == "Rat" then
                criticalAttack:setPositionZ(G.winSize.height*0.25)
            end
            effect:addChild(criticalAttack)
            pointZ = 80
            targetScale = targetScale*2
        end
        
        self._blood = blood
        self._blood:runAction(getAction())
        effect:addChild(blood)
      
        return effect
    end
    
    if self._isBlooding == false then
        self._isBlooding = true
        self._num = damage
    else
        self._blood:stopAllActions()
        self._blood:removeFromParent()
        self._num = self._num+damage
    end
    
    return getBlood()
end

return HPCounter