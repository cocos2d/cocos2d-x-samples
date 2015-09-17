require "GlobalVariables"
require "MessageDispatchCenter"
require "Helper"
require "AttackCommand"

local file = "model/rat/rat.c3b"

Rat = class("Rat", function()
    return require "Actor".create()
end)

function Rat:ctor()
    copyTable(ActorCommonValues, self)
    copyTable(RatValues,self)

    self:init3D()
    self:initActions()
end

function Rat:reset()
    copyTable(ActorCommonValues, self)
    copyTable(RatValues,self)
    self:walkMode()
    self:setPositionZ(0)
end

function Rat.create()
    local ret = Rat.new()
    ret._AIEnabled = true

    --this update function do not do AI
    function update(dt)
        ret:baseUpdate(dt)
        ret:stateMachineUpdate(dt)
        ret:movementUpdate(dt)
    end
    ret:scheduleUpdateWithPriorityLua(update, 0.5) 
    return ret
end

function Rat:normalAttackSoundEffects()
    ccexp.AudioEngine:play2d(MonsterRatValues.attack, false,1)
end

function Rat:hurtSoundEffects()
    ccexp.AudioEngine:play2d(MonsterRatValues.wounded, false,1)
end

function Rat:playDyingEffects()
    ccexp.AudioEngine:play2d(MonsterRatValues.dead, false,1)
end

function Rat:init3D()
    self:initShadow()
    self._sprite3d = cc.EffectSprite3D:create(file)
    self._sprite3d:setScale(20)
    self._sprite3d:addEffect(cc.V3(0,0,0),CelLine, -1)
    self:addChild(self._sprite3d)
    self._sprite3d:setRotation3D({x = 90, y = 0, z = 0})        
    self._sprite3d:setRotation(-90)
end

-- init Rat animations=============================
do
    Rat._action = {
        idle = createAnimation(file,0,23,1),
        knocked = createAnimation(file,30,37,0.5),
        dead = createAnimation(file,41,76,0.2),
        attack1 = createAnimation(file,81,99,0.7),
        attack2 = createAnimation(file,99,117,0.7),
        walk = createAnimation(file,122,142,0.4)
    }
end
-- end init Rat animations========================
function Rat:initActions()
    self._action = Rat._action
end

function Rat:dyingMode(knockSource, knockAmount)
    self:setStateType(EnumStateType.DYING)
    self:playAnimation("dead")
    self:playDyingEffects()

    List.removeObj(MonsterManager,self) 
    local function recycle()
       self:removeFromParent()
       if gameMaster ~= nil then
           gameMaster:showVictoryUI()
       end
    end
    
    local function disableHeroAI()
       if List.getSize(HeroManager) ~= 0 then
            for var = HeroManager.first, HeroManager.last do
                 HeroManager[var]:setAIEnabled(false)
                 HeroManager[var]:idleMode()
                HeroManager[var]._goRight = false
             end
        end
    end
    self:runAction(cc.Sequence:create(cc.DelayTime:create(3),cc.CallFunc:create(disableHeroAI),cc.MoveBy:create(1.0,cc.V3(0,0,-50)),cc.CallFunc:create(recycle)))
    
    if knockAmount then
        local p = self._myPos
        local angle = cc.pToAngleSelf(cc.pSub(p, knockSource))
        local newPos = cc.pRotateByAngle(cc.pAdd({x=knockAmount,y=0}, p),p,angle)
        self:runAction(cc.EaseCubicActionOut:create(cc.MoveTo:create(self._action.knocked:getDuration()*3,newPos)))
    end
    self._AIEnabled = false
end


function Rat:hurt(collider, dirKnockMode)
    if self._isalive == true then 
        --TODO add sound effect

        local damage = collider.damage
        --calculate the real damage
        local critical = false
        local knock = collider.knock
        if math.random() < collider.criticalChance then
            damage = damage*1.5
            critical = true
            knock = knock*2
        end
        damage = damage + damage * math.random(-1,1) * 0.15        
        damage = damage - self._defense
        damage = math.floor(damage)

        if damage <= 0 then
            damage = 1
        end

        self._hp = self._hp - damage

        if self._hp > 0 then
            if critical == true then
                self:knockMode(collider, dirKnockMode)
                self:hurtSoundEffects()
            else
                self:hurtSoundEffects()
            end
        else
            self._hp = 0
            self._isalive = false
            self:dyingMode(getPosTable(collider),knock)        
        end

        --three param judge if crit
        local blood = self._hpCounter:showBloodLossNum(damage,self,critical)
        blood:setPositionZ(G.winSize.height*0.25)
        blood:setCameraMask(UserCameraFlagMask)
        self:addEffect(blood)

        return damage        
    end
    return 0
end