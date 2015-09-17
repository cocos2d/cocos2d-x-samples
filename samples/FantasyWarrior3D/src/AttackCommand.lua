require "Helper"
require "Manager"
require "GlobalVariables"

AttackManager = List.new()
function solveAttacks(dt)
    for val = AttackManager.last, AttackManager.first, -1 do
        local attack = AttackManager[val]
        local apos = getPosTable(attack) 
        if attack.mask == EnumRaceType.HERO then
            --if heroes attack, then lets check monsters
            for mkey = MonsterManager.last, MonsterManager.first, -1 do
                --check distance first
                local monster = MonsterManager[mkey]
                local mpos = monster._myPos
                local dist = cc.pGetDistance(apos, mpos)
                if dist < (attack.maxRange + monster._radius) and dist > attack.minRange then
                    --range test passed, now angle test
                    local angle = radNormalize(cc.pToAngleSelf(cc.pSub(mpos,apos)))
                    local afacing = radNormalize(attack.facing)
                    
                    if(afacing + attack.angle/2)>angle and angle > (afacing- attack.angle/2) then
                        attack:onCollide(monster)
                    end
                end
            end
        elseif attack.mask == EnumRaceType.MONSTER then
            --if heroes attack, then lets check monsters
            for hkey = HeroManager.last, HeroManager.first, -1 do
                --check distance first
                local hero = HeroManager[hkey]
                local hpos = hero._myPos
                local dist = cc.pGetDistance(getPosTable(attack), hpos)
                if dist < (attack.maxRange + hero._radius) and dist > attack.minRange then
                    --range test passed, now angle test
                    local angle = cc.pToAngleSelf(cc.pSub(hpos,getPosTable(attack)))
                    if(attack.facing + attack.angle/2)>angle and angle > (attack.facing- attack.angle/2) then
                        attack:onCollide(hero)
                    end
                end
            end
        end
        attack.curDuration = attack.curDuration+dt
        if attack.curDuration > attack.duration then
            attack:onTimeOut()
            List.remove(AttackManager,val)
        else
            attack:onUpdate(dt)
        end
    end
end

BasicCollider = class("BasicCollider", function()
    local node = cc.Sprite3D:create()
    node:setCascadeColorEnabled(true)
    return node
end)

function BasicCollider:ctor()
    self.minRange = 0   --the min radius of the fan
    self.maxRange = 150 --the max radius of the fan
    self.angle    = 120 --arc of attack, in radians
    self.knock    = 150 --default knock, knocks 150 units 
    self.mask     = 1   --1 is Heroes, 2 is enemy, 3 ??
    self.damage   = 100
    self.facing    = 0 --this is radians
    self.duration = 0
    self.curDuration = 0
    self.speed = 0 --traveling speed}
    self.criticalChance = 0
end
--callback when the collider has being solved by the attack manager, 
--make sure you delete it from node tree, if say you have an effect attached to the collider node
function BasicCollider:onTimeOut()
    self:removeFromParent()
end

function BasicCollider:playHitAudio()
    ccexp.AudioEngine:play2d(CommonAudios.hit, false,0.7)
end

function BasicCollider:hurtEffect(target)
    
    local hurtAction = cc.Animate:create(animationCache:getAnimation("hurtAnimation"))
    local hurtEffect = cc.BillBoard:create()
    hurtEffect:setScale(1.5)
    hurtEffect:runAction(cc.Sequence:create(hurtAction, cc.RemoveSelf:create()))
    hurtEffect:setPosition3D(cc.V3(0,0,50))
    hurtEffect:setCameraMask(UserCameraFlagMask)
    target:addChild(hurtEffect)
end

function BasicCollider:onCollide(target)
    
    self:hurtEffect(target)
    self:playHitAudio()    
    target:hurt(self)
end

function BasicCollider:onUpdate()
    -- implement this function if this is a projectile
end

function BasicCollider:initData(pos, facing, attackInfo)
    copyTable(attackInfo, self)
    
    self.facing = facing or self.facing
    self:setPosition(pos)
    List.pushlast(AttackManager, self)
    currentLayer:addChild(self, -10)
end

function BasicCollider.create(pos, facing, attackInfo)
    local ret = BasicCollider.new()    
    ret:initData(pos,facing,attackInfo)
    return ret
end


KnightNormalAttack = class("KnightNormalAttack", function()
    return BasicCollider.new()
end)

function KnightNormalAttack.create(pos, facing, attackInfo, knight)
    local ret = KnightNormalAttack.new()
    ret:initData(pos,facing,attackInfo)
    ret.owner = knight
    ret:setCameraMask(UserCameraFlagMask)
    return ret
end

function KnightNormalAttack:onTimeOut()
    self:removeFromParent()
end

MageNormalAttack = class("MageNormalAttack", function()
    return BasicCollider.new()
end)

function MageNormalAttack.create(pos,facing,attackInfo, target, owner)
    local ret = MageNormalAttack.new()
    ret:initData(pos,facing,attackInfo)
    ret._target = target
    ret.owner = owner
    
    ret.sp = cc.BillBoard:create("FX/FX.png", RECTS.iceBolt, 0)
    --ret.sp:setCamera(camera)
    ret.sp:setPosition3D(cc.V3(0,0,50))
    ret.sp:setScale(2)
    ret:addChild(ret.sp)
    
    local smoke = cc.ParticleSystemQuad:create(ParticleManager:getInstance():getPlistData("iceTrail"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("puff.png")
    smoke:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    smoke:setScale(2)
    ret:addChild(smoke)
    smoke:setRotation3D({x=90, y=0, z=0})
    smoke:setGlobalZOrder(0)
    smoke:setPositionZ(50)
    
    local pixi = cc.ParticleSystemQuad:create(ParticleManager:getInstance():getPlistData("pixi"))
    local pixif = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    pixi:setTextureWithRect(pixif:getTexture(), pixif:getRect())
    pixi:setScale(2)
    ret:addChild(pixi)
    pixi:setRotation3D({x=90, y=0, z=0})
    pixi:setGlobalZOrder(0)
    pixi:setPositionZ(50)
    
    ret.part1 = smoke
    ret.part2 = pixi
    ret:setCameraMask(UserCameraFlagMask)
    return ret
end

function MageNormalAttack:onTimeOut()
    self.part1:stopSystem()
    self.part2:stopSystem()
    self:runAction(cc.Sequence:create(cc.DelayTime:create(1),cc.RemoveSelf:create()))
    
    local magic = cc.ParticleSystemQuad:create(ParticleManager:getInstance():getPlistData("magic"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    magic:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    magic:setScale(1.5)
    magic:setRotation3D({x=90, y=0, z=0})
    self:addChild(magic)
    magic:setGlobalZOrder(0)
    magic:setPositionZ(0)
    self:setCameraMask(UserCameraFlagMask)
    
    self.sp:setTextureRect(RECTS.iceSpike)
    self.sp:runAction(cc.FadeOut:create(1))
    self.sp:setScale(4)

end

function MageNormalAttack:playHitAudio()
    ccexp.AudioEngine:play2d(MageProperty.ice_normalAttackHit, false,1)
end

function MageNormalAttack:onCollide(target)

    self:hurtEffect(target)
    self:playHitAudio()    
    self.owner._angry = self.owner._angry + target:hurt(self)*0.3
    local anaryChange = {_name = MageValues._name, _angry = self.owner._angry, _angryMax = self.owner._angryMax}
    MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)
    --set cur duration to its max duration, so it will be removed when checking time out
    self.curDuration = self.duration+1
end

function MageNormalAttack:onUpdate(dt)
    local nextPos
    if self._target and self._target._isalive then
        local selfPos = getPosTable(self)
        local tpos = self._target._myPos
        local angle = cc.pToAngleSelf(cc.pSub(tpos,selfPos))
        nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,angle)
    else
        local selfPos = getPosTable(self)
        nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,self.facing)
    end
    self:setPosition(nextPos)
end


MageIceSpikes = class("MageIceSpikes", function()
    return BasicCollider.new()
end)

function MageIceSpikes:playHitAudio()
    ccexp.AudioEngine:play2d(MageProperty.ice_specialAttackHit, false,0.7)
end

function MageIceSpikes.create(pos, facing, attackInfo, owner)
    local ret = MageIceSpikes.new()
    ret:initData(pos,facing,attackInfo)
    ret.sp = cc.ShadowSprite:createWithSpriteFrameName("shadow.png")
    ret.sp:setGlobalZOrder(-ret:getPositionY()+FXZorder)
    ret.sp:setOpacity(100)
    ret.sp:setPosition3D(cc.V3(0,0,1))
    ret.sp:setScale(ret.maxRange/12)
    ret.sp:setGlobalZOrder(-1)
    ret:addChild(ret.sp)
    ret.owner = owner

    ---========
    --create 3 spikes
    local x = cc.Node:create()
    ret.spikes = x
    ret:addChild(x)
    for var=0, 10 do
        local rand = math.ceil(math.random()*3)
        local spike = cc.Sprite:createWithSpriteFrameName(string.format("iceSpike%d.png",rand))
        spike:setAnchorPoint(0.5,0)
        spike:setRotation3D(cc.V3(90,0,0))
        x:addChild(spike)
        if rand == 3 then
            spike:setScale(1.5)
        else
            spike:setScale(2)
        end
        spike:setOpacity(165)
        spike:setFlippedX(not(math.floor(math.random()*2)))
        spike:setPosition3D(cc.V3(math.random(-ret.maxRange/1.5, ret.maxRange/1.5),math.random(-ret.maxRange/1.5, ret.maxRange/1.5),1))
        spike:setGlobalZOrder(0)
        x:setScale(0)
        x:setPositionZ(-210)
    end
    x:runAction(cc.EaseBackOut:create(cc.MoveBy:create(0.3,cc.V3(0,0,200))))
    x:runAction(cc.EaseBounceOut:create(cc.ScaleTo:create(0.4, 1)))
    
    local magic = cc.BillboardParticleSystem:create(ParticleManager:getInstance():getPlistData("magic"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    magic:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    magic:setCamera(camera)
    magic:setScale(1.5)
    ret:addChild(magic)
    magic:setGlobalZOrder(-ret:getPositionY()*2+FXZorder)
    magic:setPositionZ(0)
    ret:setCameraMask(UserCameraFlagMask)

    
    return ret
end

function MageIceSpikes:onTimeOut()
    self.spikes:setVisible(false)
    local puff = cc.BillboardParticleSystem:create(ParticleManager:getInstance():getPlistData("puffRing"))
    --local puff = cc.ParticleSystemQuad:create("FX/puffRing.plist")
    local puffFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame("puff.png")
    puff:setTextureWithRect(puffFrame:getTexture(), puffFrame:getRect())
    puff:setCamera(camera)
    puff:setScale(3)
    self:addChild(puff)
    puff:setGlobalZOrder(-self:getPositionY()+FXZorder)
    puff:setPositionZ(20)
    
    local magic = cc.BillboardParticleSystem:create(ParticleManager:getInstance():getPlistData("magic"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    magic:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    magic:setCamera(camera)
    magic:setScale(1.5)
    self:addChild(magic)
    magic:setGlobalZOrder(-self:getPositionY()+FXZorder)
    magic:setPositionZ(0)
    self:setCameraMask(UserCameraFlagMask)
        
    self.sp:runAction(cc.FadeOut:create(1))
    self:runAction(cc.Sequence:create(cc.DelayTime:create(1),cc.RemoveSelf:create()))
end

function MageIceSpikes:playHitAudio()

end

function MageIceSpikes:onCollide(target)
    if self.curDOTTime > self.DOTTimer then
        self:hurtEffect(target)
        self:playHitAudio()    
        self.owner._angry = self.owner._angry + target:hurt(self)*0.1
        local anaryChange = {_name = MageValues._name, _angry = self.owner._angry, _angryMax = self.owner._angryMax}
        MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)
        self.DOTApplied = true
    end
end

function MageIceSpikes:onUpdate(dt)
-- implement this function if this is a projectile
    self.curDOTTime = self.curDOTTime + dt
    if self.DOTApplied then
        self.DOTApplied = false
        self.curDOTTime = 0
    end
end

ArcherNormalAttack = class("ArcherNormalAttack", function()
    return BasicCollider.new()
end)

function ArcherNormalAttack.create(pos,facing,attackInfo, owner)
    local ret = ArcherNormalAttack.new()
    ret:initData(pos,facing,attackInfo)
    ret.owner = owner
    
    ret.sp = Archer:createArrow()
    ret.sp:setRotation(RADIANS_TO_DEGREES(-facing)-90)
    ret:addChild(ret.sp)
    ret:setCameraMask(UserCameraFlagMask)

    return ret
end

function ArcherNormalAttack:onTimeOut()
    self:runAction(cc.RemoveSelf:create())
end

function ArcherNormalAttack:onCollide(target)
    self:hurtEffect(target)
    self:playHitAudio()    
    self.owner._angry = self.owner._angry + target:hurt(self, true)*0.3
    local anaryChange = {_name = ArcherValues._name, _angry = self.owner._angry, _angryMax = self.owner._angryMax}
    MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)
    --set cur duration to its max duration, so it will be removed when checking time out
    self.curDuration = self.duration+1
end

function ArcherNormalAttack:onUpdate(dt)
    local selfPos = getPosTable(self)
    local nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,self.facing)
    self:setPosition(nextPos)
end
ArcherSpecialAttack = class("ArcherSpecialAttack", function()
    return BasicCollider.new()
end)

function ArcherSpecialAttack.create(pos,facing,attackInfo, owner)
    local ret = ArcherSpecialAttack.new()
    ret:initData(pos,facing,attackInfo)
    ret.owner = owner
    ret.sp = Archer:createArrow()
    ret.sp:setRotation(RADIANS_TO_DEGREES(-facing)-90)
    ret:addChild(ret.sp)
    ret:setCameraMask(UserCameraFlagMask)
    
    return ret
end

function ArcherSpecialAttack:onTimeOut()
    self:runAction(cc.RemoveSelf:create())
end

function ArcherSpecialAttack:onCollide(target)
    if self.curDOTTime >= self.DOTTimer then
        self:hurtEffect(target)
        self:playHitAudio()    
        self.owner._angry = self.owner._angry + target:hurt(self, true)*0.3
        local anaryChange = {_name = ArcherValues._name, _angry = self.owner._angry, _angryMax = self.owner._angryMax}
        MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)
        self.DOTApplied = true
    end
end

function ArcherSpecialAttack:onUpdate(dt)
    local selfPos = getPosTable(self)
    local nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,self.facing)
    self:setPosition(nextPos)
    self.curDOTTime = self.curDOTTime + dt
    if self.DOTApplied then
        self.DOTApplied = false
        self.curDOTTime = 0
    end
end

Nova = class("nova", function()
    return BasicCollider.new()
end)

function Nova.create(pos, facing)
    local ret = Nova.new()
    ret:initData(pos, facing, BossValues.nova)
    
    ret.sp = cc.Sprite:createWithSpriteFrameName("nova1.png")
    ret.sp:setGlobalZOrder(-ret:getPositionY()+FXZorder)
    ret:addChild(ret.sp)
    ret.sp:setPosition(cc.V3(0,0,1))
    ret.sp:setScale(0)
    ret.sp:runAction(cc.EaseCircleActionOut:create(cc.ScaleTo:create(0.3, 3)))
    ret.sp:runAction(cc.FadeOut:create(0.7))
    ret:setCameraMask(UserCameraFlagMask)
    return ret
end
function Nova:onCollide(target)
    if self.curDOTTime > self.DOTTimer then
        self:hurtEffect(target)
        self:playHitAudio()    
        self.DOTApplied = true
        target:hurt(self)
    end
end

function Nova:onUpdate(dt)
    -- implement this function if this is a projectile
    self.curDOTTime = self.curDOTTime + dt
    if self.DOTApplied then
        self.DOTApplied = false
        self.curDOTTime = 0
    end
end

function Nova:onTimeOut()
    self:runAction(cc.Sequence:create(cc.DelayTime:create(1),cc.RemoveSelf:create()))
end
DragonAttack = class("DragonAttack", function()
    return BasicCollider.new()
end)

function DragonAttack.create(pos,facing,attackInfo)
    local ret = DragonAttack.new()
    ret:initData(pos,facing,attackInfo)

    ret.sp = cc.BillBoard:create("FX/FX.png", RECTS.fireBall)
    ret.sp:setPosition3D(cc.V3(0,0,48))
    ret.sp:setScale(1.7)
    ret:addChild(ret.sp)
    ret:setCameraMask(UserCameraFlagMask)

    return ret
end

function DragonAttack:onTimeOut()
    self:runAction(cc.Sequence:create(cc.DelayTime:create(0.5),cc.RemoveSelf:create()))

    local magic = cc.ParticleSystemQuad:create(ParticleManager:getInstance():getPlistData("magic"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    magic:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    magic:setScale(1.5)
    magic:setRotation3D({x=90, y=0, z=0})
    self:addChild(magic)
    magic:setGlobalZOrder(-self:getPositionY()*2+FXZorder)
    magic:setPositionZ(0)
    magic:setEndColor({r=1,g=0.5,b=0})
    self:setCameraMask(UserCameraFlagMask)

    local fireballAction = cc.Animate:create(animationCache:getAnimation("fireBallAnim"))
    self.sp:runAction(fireballAction)
    self.sp:setScale(2)
    
    
end

function DragonAttack:playHitAudio()
    ccexp.AudioEngine:play2d(MonsterDragonValues.fireHit, false,0.6)    
end

function DragonAttack:onCollide(target)
    self:hurtEffect(target)
    self:playHitAudio()    
    target:hurt(self)
    --set cur duration to its max duration, so it will be removed when checking time out
    self.curDuration = self.duration+1
end

function DragonAttack:onUpdate(dt)
    local selfPos = getPosTable(self)
    local nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,self.facing)
    self:setPosition(nextPos)
end

BossNormal = class("BossNormal", function()
    return BasicCollider.new()
end)

function BossNormal.create(pos,facing,attackInfo)
    local ret = BossNormal.new()
    ret:initData(pos,facing,attackInfo)

    ret.sp = cc.BillBoard:create("FX/FX.png", RECTS.fireBall)
    ret.sp:setPosition3D(cc.V3(0,0,48))
    ret.sp:setScale(1.7)
    ret:addChild(ret.sp)
    ret:setCameraMask(UserCameraFlagMask)

    return ret
end

function BossNormal:onTimeOut()
    self:runAction(cc.Sequence:create(cc.DelayTime:create(0.5),cc.RemoveSelf:create()))

    local magic = cc.ParticleSystemQuad:create(ParticleManager:getInstance():getPlistData("magic"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    magic:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    magic:setScale(1.5)
    magic:setRotation3D({x=90, y=0, z=0})
    self:addChild(magic)
    magic:setGlobalZOrder(-self:getPositionY()*2+FXZorder)
    magic:setPositionZ(0)
    magic:setEndColor({r=1,g=0.5,b=0})

    local fireballAction = cc.Animate:create(animationCache:getAnimation("fireBallAnim"))
    self.sp:runAction(fireballAction)
    self.sp:setScale(2)
    self:setCameraMask(UserCameraFlagMask)

    Nova.create(getPosTable(self), self._curFacing)
end

function BossNormal:playHitAudio()
    ccexp.AudioEngine:play2d(MonsterDragonValues.fireHit, false,0.6)    
end

function BossNormal:onCollide(target)
    --set cur duration to its max duration, so it will be removed when checking time out
    self.curDuration = self.duration+1
end

function BossNormal:onUpdate(dt)
    local selfPos = getPosTable(self)
    local nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,self.facing)
    self:setPosition(nextPos)
end

BossSuper = class("BossSuper", function()
    return BasicCollider.new()
end)

function BossSuper.create(pos,facing,attackInfo)
    local ret = BossSuper.new()
    ret:initData(pos,facing,attackInfo)

    ret.sp = cc.BillBoard:create("FX/FX.png", RECTS.fireBall)
    ret.sp:setPosition3D(cc.V3(0,0,48))
    ret.sp:setScale(1.7)
    ret:addChild(ret.sp)
    ret:setCameraMask(UserCameraFlagMask)

    return ret
end

function BossSuper:onTimeOut()
    self:runAction(cc.Sequence:create(cc.DelayTime:create(0.5),cc.RemoveSelf:create()))

    local magic = cc.ParticleSystemQuad:create(ParticleManager:getInstance():getPlistData("magic"))
    local magicf = cc.SpriteFrameCache:getInstance():getSpriteFrame("particle.png")
    magic:setTextureWithRect(magicf:getTexture(), magicf:getRect())
    magic:setScale(1.5)
    magic:setRotation3D({x=90, y=0, z=0})
    self:addChild(magic)
    magic:setGlobalZOrder(-self:getPositionY()*2+FXZorder)
    magic:setPositionZ(0)
    magic:setEndColor({r=1,g=0.5,b=0})

    local fireballAction = cc.Animate:create(animationCache:getAnimation("fireBallAnim"))
    self.sp:runAction(fireballAction)
    self.sp:setScale(2)
    self:setCameraMask(UserCameraFlagMask)

    Nova.create(getPosTable(self), self._curFacing)
end

function BossSuper:playHitAudio()
    ccexp.AudioEngine:play2d(MonsterDragonValues.fireHit, false,0.6)    
end

function BossSuper:onCollide(target)
    --set cur duration to its max duration, so it will be removed when checking time out
    self.curDuration = self.duration+1
end

function BossSuper:onUpdate(dt)
    local selfPos = getPosTable(self)
    local nextPos = cc.pRotateByAngle(cc.pAdd({x=self.speed*dt, y=0},selfPos),selfPos,self.facing)
    self:setPosition(nextPos)
end

return AttackManager