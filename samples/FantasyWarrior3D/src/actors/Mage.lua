require "GlobalVariables"
require "MessageDispatchCenter"
require "Helper"
require "AttackCommand"

local file = "model/mage/mage.c3b"

Mage = class("Mage", function()
    return require "Actor".create()
end)

function Mage:ctor()
    self._useWeaponId = ReSkin.mage.weapon
    self._useArmourId = ReSkin.mage.armour
    self._useHelmetId = ReSkin.mage.helmet
    if uiLayer~=nil then
        self._bloodBar = uiLayer.MageBlood
        self._bloodBarClone = uiLayer.MageBloodClone
        self._avatar = uiLayer.MagePng
    end

    copyTable(ActorCommonValues, self)
    copyTable(MageValues,self)

    self:init3D()
    self:initActions()
end
function Mage:hurtSoundEffects()
    ccexp.AudioEngine:play2d(MageProperty.wounded, false,1)
end

function Mage:playDyingEffects()
    ccexp.AudioEngine:play2d(MageProperty.dead, false,1)
end

function Mage:normalAttack()
    ccexp.AudioEngine:play2d(MageProperty.normalAttackShout, false,0.4)
    ccexp.AudioEngine:play2d(MageProperty.ice_normal, false,0.8)
    MageNormalAttack.create(getPosTable(self), self._curFacing, self._normalAttack, self._target, self)
end

function Mage:specialAttack()
    self._specialAttackChance = MageValues._specialAttackChance
    self._angry = ActorCommonValues._angry
    local anaryChange = {_name = self._name, _angry = self._angry, _angryMax = self._angryMax}
    MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)      
    
    --mage will create 3 ice spikes on the ground
    --get 3 positions
    ccexp.AudioEngine:play2d(MageProperty.specialAttackShout, false,0.5)
    ccexp.AudioEngine:play2d(MageProperty.ice_special, false,1)
    local pos1 = getPosTable(self)
    local pos2 = getPosTable(self)
    local pos3 = getPosTable(self)
    pos1.x = pos1.x+130
    pos2.x = pos2.x+330
    pos3.x = pos3.x+530
    pos1 = cc.pRotateByAngle(pos1, self._myPos, self._curFacing)
    pos2 = cc.pRotateByAngle(pos2, self._myPos, self._curFacing)
    pos3 = cc.pRotateByAngle(pos3, self._myPos, self._curFacing)
    MageIceSpikes.create(pos1, self._curFacing, self._specialAttack, self)
    local function spike2()
        MageIceSpikes.create(pos2, self._curFacing, self._specialAttack, self)
    end
    local function spike3()
        MageIceSpikes.create(pos3, self._curFacing, self._specialAttack, self)
    end
    delayExecute(self,spike2,0.25)
    delayExecute(self,spike3,0.5)

end

function Mage:init3D()
    self:initShadow()
    self:initPuff()
    self._sprite3d = cc.EffectSprite3D:create(file)
    self._sprite3d:setScale(1.9)
    self._sprite3d:addEffect(cc.V3(0,0,0),CelLine, -1)
    self:addChild(self._sprite3d)
    self._sprite3d:setRotation3D({x = 90, y = 0, z = 0})        
    self._sprite3d:setRotation(-90)
    self:setDefaultEqt()
end

-- init Mage animations=============================
do
    Mage._action = {
        idle = createAnimation(file,206,229,0.7),
        walk = createAnimation(file,99,119,0.7),
        attack1 = createAnimation(file,12,30,0.7),
        attack2 = createAnimation(file,31,49,0.7),
        specialattack1 = createAnimation(file,56,74,1),
        specialattack2 = createAnimation(file,75,92,1),
        defend = createAnimation(file,1,5,0.7),
        knocked = createAnimation(file,126,132,0.7),
        dead = createAnimation(file,139,199,0.7)
    }
end
-- end init Mage animations========================
function Mage:initActions()
    self._action = Mage._action
end

-- set default equipments
function Mage:setDefaultEqt()
    self:updateWeapon()
    self:updateHelmet()
    self:updateArmour()
end

function Mage:updateWeapon()
    if self._useWeaponId == 0 then
        local weapon = self._sprite3d:getMeshByName("fashi_wuqi01")
        weapon:setVisible(true)
        weapon = self._sprite3d:getMeshByName("fashi_wuqi2")
        weapon:setVisible(false)
    else
        local weapon = self._sprite3d:getMeshByName("fashi_wuqi2")
        weapon:setVisible(true)
        weapon = self._sprite3d:getMeshByName("fashi_wuqi01")
        weapon:setVisible(false)
    end
end

function Mage:updateHelmet()
    if self._useHelmetId == 0 then
        local helmet = self._sprite3d:getMeshByName("fashi_tou01")
        helmet:setVisible(true)
        helmet = self._sprite3d:getMeshByName("fashi_tou2")
        helmet:setVisible(false)
    else
        local helmet = self._sprite3d:getMeshByName("fashi_tou2")
        helmet:setVisible(true)
        helmet = self._sprite3d:getMeshByName("fashi_tou01")
        helmet:setVisible(false)
    end
end

function Mage:updateArmour()
    if self._useArmourId == 0 then
        local armour = self._sprite3d:getMeshByName("fashi_shenti01")
        armour:setVisible(true)
        armour = self._sprite3d:getMeshByName("fashi_shenti2")
        armour:setVisible(false)
    else
        local armour = self._sprite3d:getMeshByName("fashi_shenti2")
        armour:setVisible(true)
        armour = self._sprite3d:getMeshByName("fashi_shenti01")
        armour:setVisible(false)
    end
end

--swicth weapon
function Mage:switchWeapon()
    self._useWeaponId = self._useWeaponId+1
    if self._useWeaponId > 1 then
        self._useWeaponId = 0;
    end
    self:updateWeapon()
end

--switch helmet
function Mage:switchHelmet()
    self._useHelmetId = self._useHelmetId+1
    if self._useHelmetId > 1 then
        self._useHelmetId = 0;
    end
    self:updateHelmet()
end

--switch armour
function Mage:switchArmour()
    self._useArmourId = self._useArmourId+1
    if self._useArmourId > 1 then
        self._useArmourId = 0;
    end
    self:updateArmour()
end

-- get weapon id
function Mage:getWeaponID()
    return self._useWeaponId
end

-- get armour id
function Mage:getArmourID()
    return self._useArmourId
end

-- get helmet id
function Mage:getHelmetID()
    return self._useHelmetId
end

function Mage.create()
    local ret = Mage.new()
    ret:idleMode()
    ret._AIEnabled = true
    --this update function do not do AI
    function update(dt)
        ret:baseUpdate(dt)
        ret:stateMachineUpdate(dt)
        ret:movementUpdate(dt)
    end
    ret:scheduleUpdateWithPriorityLua(update, 0) 

    local function specialAttack()
        if ret._specialAttackChance == 1 then return end
        ret._specialAttackChance = 1

        --        ret._attackTimer = ret._attackFrequency   
    end
    MessageDispatchCenter:registerMessage(MessageDispatchCenter.MessageType.SPECIAL_MAGE, specialAttack)    
    return ret
end
function Mage:hurt(collider, dirKnockMode)
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
        if self._name == "Rat" then
            blood:setPositionZ(G.winSize.height*0.25)
        end
        blood:setCameraMask(UserCameraFlagMask)
        self:addEffect(blood)
        local bloodMinus = {_name = self._name, _maxhp= self._maxhp, _hp = self._hp, _bloodBar=self._bloodBar, _bloodBarClone=self._bloodBarClone,_avatar =self._avatar}
        MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.BLOOD_MINUS, bloodMinus)

        local anaryChange = {_name = self._name, _angry = self._angry, _angryMax = self._angryMax}
        MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)
        self._angry = self._angry + damage
        return damage        
    end
    return 0
end

return Mage
