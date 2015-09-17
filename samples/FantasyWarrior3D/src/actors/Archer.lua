require "GlobalVariables"
require "MessageDispatchCenter"
require "Helper"
require "AttackCommand"

local file = "model/archer/archer.c3b"

Archer = class("Archer", function()
    return require "Actor".create()
end)

function Archer:ctor()
    self._useWeaponId = ReSkin.archer.weapon
    self._useArmourId = ReSkin.archer.armour
    self._useHelmetId = ReSkin.archer.helmet
    
    copyTable(ActorCommonValues, self)
    copyTable(ArcherValues,self)
    
    if uiLayer~=nil then
        self._bloodBar = uiLayer.ArcherBlood
        self._bloodBarClone = uiLayer.ArcherBloodClone
        self._avatar = uiLayer.ArcherPng
    end
    
    self:init3D()
    self:initActions()
end

function Archer.create()
    local ret = Archer.new()
    ret:idleMode()
    ret._AIEnabled = true
    --this update function do not do AI
    function update(dt)
        ret:baseUpdate(dt)
        ret:stateMachineUpdate(dt)
        ret:movementUpdate(dt)
    end
    ret:scheduleUpdateWithPriorityLua(update, 0)
    
    function specialAttack()
        if ret._specialAttackChance == 1 then return end
        ret._specialAttackChance = 1
    end
    MessageDispatchCenter:registerMessage(MessageDispatchCenter.MessageType.SPECIAL_ARCHER, specialAttack)
    return ret
end

function Archer:createArrow()
    local sprite3d = cc.Sprite3D:create("model/archer/arrow.obj")
    sprite3d:setTexture("model/archer/hunter01_tex_head.jpg")
    sprite3d:setScale(2)
    sprite3d:setPosition3D(cc.V3(0,0,50))
    sprite3d:setRotation3D({x = -90, y = 0, z = 0})        
    return sprite3d
end

local function ArcherlAttackCallback(audioID,filePath)
    ccexp.AudioEngine:play2d(Archerproperty.attack2, false,1)
end

function Archer:playDyingEffects()
    ccexp.AudioEngine:play2d(Archerproperty.dead, false,1)
end

function Archer:hurtSoundEffects()
    ccexp.AudioEngine:play2d(Archerproperty.wounded, false,1)
end

function Archer:normalAttack()
    ArcherNormalAttack.create(getPosTable(self), self._curFacing, self._normalAttack, self)
    ccexp.AudioEngine:play2d(Archerproperty.normalAttackShout, false,1)
    AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false,1)
--    ccexp.AudioEngine:play2d(Archerproperty.wow, false,1)
    ccexp.AudioEngine:setFinishCallback(AUDIO_ID.ARCHERATTACK,ArcherlAttackCallback)
end

function Archer:specialAttack()
    self._specialAttackChance = ArcherValues._specialAttackChance
    self._angry = ActorCommonValues._angry
    local anaryChange = {_name = self._name, _angry = self._angry, _angryMax = self._angryMax}
    MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)      
    
    ccexp.AudioEngine:play2d(Archerproperty.specialAttackShout, false,1)
    AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false,1)
    ccexp.AudioEngine:setFinishCallback(AUDIO_ID.ARCHERATTACK,ArcherlAttackCallback)
    
    local attack = self._specialAttack
    attack.knock = 80
    
    local pos1 = getPosTable(self)
    local pos2 = getPosTable(self)
    local pos3 = getPosTable(self)
    pos1.x = pos1.x
    pos2.x = pos2.x
    pos3.x = pos3.x
    pos1 = cc.pRotateByAngle(pos1, self._myPos, self._curFacing)
    pos2 = cc.pRotateByAngle(pos2, self._myPos, self._curFacing)
    pos3 = cc.pRotateByAngle(pos3, self._myPos, self._curFacing)
    ArcherSpecialAttack.create(pos1, self._curFacing, attack, self)
    local function spike2()
        ArcherSpecialAttack.create(pos2, self._curFacing, attack,self)
        AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false,1)
        ccexp.AudioEngine:setFinishCallback(AUDIO_ID.ARCHERATTACK,ArcherlAttackCallback)
    end
    local function spike3()
        ArcherSpecialAttack.create(pos3, self._curFacing, attack,self)
        AUDIO_ID.ARCHERATTACK = ccexp.AudioEngine:play2d(Archerproperty.attack1, false,1)
        ccexp.AudioEngine:setFinishCallback(AUDIO_ID.ARCHERATTACK,ArcherlAttackCallback)
    end
    delayExecute(self,spike2,0.2)
    delayExecute(self,spike3,0.4)
end

function Archer:init3D()
    self:initShadow()
    self:initPuff()
    self._sprite3d = cc.EffectSprite3D:create(file)
    self._sprite3d:setScale(1.6)
    self._sprite3d:addEffect(cc.V3(0,0,0),CelLine, -1)
    self:addChild(self._sprite3d)
    self._sprite3d:setRotation3D({x = 90, y = 0, z = 0})        
    self._sprite3d:setRotation(-90)
    self:setDefaultEqt()
end


-- init Archer animations=============================
do
    Archer._action = {
        idle = createAnimation(file,208,253,0.7),
        walk = createAnimation(file,110,130,0.7),
        attack1 = createAnimation(file,0,12,0.7),
        attack2 = createAnimation(file,12,24,0.7),
        specialattack1 = createAnimation(file,30,43,1),
        specialattack2 = createAnimation(file,44,56,1),
        defend = createAnimation(file,70,95,0.7),
        knocked = createAnimation(file,135,145,0.7),
        dead = createAnimation(file,150,196,0.7)
    }
end
-- end init Archer animations========================
function Archer:initActions()
    self._action = Archer._action
end

-- set default equipments
function Archer:setDefaultEqt()
    self:updateWeapon()
    self:updateHelmet()
    self:updateArmour()
    self:showOrHideArrow(false, 0)
end

function Archer:updateWeapon()
    if self._useWeaponId == 0 then
        local weapon = self._sprite3d:getMeshByName("gongjianshou_gong01")
        weapon:setVisible(true)
        weapon = self._sprite3d:getMeshByName("gongjianshou_gong02")
        weapon:setVisible(false)
    else
        local weapon = self._sprite3d:getMeshByName("gongjianshou_gong02")
        weapon:setVisible(true)
        weapon = self._sprite3d:getMeshByName("gongjianshou_gong01")
        weapon:setVisible(false)
    end
end

function Archer:updateHelmet()
    if self._useHelmetId == 0 then
        local helmet = self._sprite3d:getMeshByName("gongjianshou_tou01")
        helmet:setVisible(true)
        helmet = self._sprite3d:getMeshByName("gonajingshou_tou02")
        helmet:setVisible(false)
    else
        local helmet = self._sprite3d:getMeshByName("gonajingshou_tou02")
        helmet:setVisible(true)
        helmet = self._sprite3d:getMeshByName("gongjianshou_tou01")
        helmet:setVisible(false)
    end
end

function Archer:updateArmour()
    if self._useArmourId == 0 then
        local armour = self._sprite3d:getMeshByName("gongjianshou_shenti01")
        armour:setVisible(true)
        armour = self._sprite3d:getMeshByName("gonjianshou_shenti02")
        armour:setVisible(false)
    else
        local armour = self._sprite3d:getMeshByName("gonjianshou_shenti02")
        armour:setVisible(true)
        armour = self._sprite3d:getMeshByName("gongjianshou_shenti01")
        armour:setVisible(false)
    end
end

--swicth weapon
function Archer:switchWeapon()
    self._useWeaponId = self._useWeaponId+1
    if self._useWeaponId > 1 then
        self._useWeaponId = 0;
    end
    self:updateWeapon()
end

--switch helmet
function Archer:switchHelmet()
    self._useHelmetId = self._useHelmetId+1
    if self._useHelmetId > 1 then
        self._useHelmetId = 0;
    end
    self:updateHelmet()
end

--switch armour
function Archer:switchArmour()
    self._useArmourId = self._useArmourId+1
    if self._useArmourId > 1 then
        self._useArmourId = 0;
    end
    self:updateArmour()
end

--show/hide arrow
--isShow: true:Show false:Hide
--type: 0:show/hide all 1:show/hide 1 2:show/hide 2
function Archer:showOrHideArrow(isShow, arrowType)
    if arrowType == 0 then
        local arrow = self._sprite3d:getMeshByName("gongjiashou_jian01")
        arrow:setVisible(isShow)
        local arrow = self._sprite3d:getMeshByName("gongjianshou_jian02")
        arrow:setVisible(isShow)
    elseif arrowType == 1 then
        local arrow = self._sprite3d:getMeshByName("gongjiashou_jian01")
        arrow:setVisible(isShow)
    elseif arrowType == 2 then
        local arrow = self._sprite3d:getMeshByName("gongjianshou_jian02")
        arrow:setVisible(isShow)
    end
end

-- get weapon id
function Archer:getWeaponID()
    return self._useWeaponId
end

-- get armour id
function Archer:getArmourID()
    return self._useArmourId
end

-- get helmet id
function Archer:getHelmetID()
    return self._useHelmetId
end
function Archer:hurt(collider, dirKnockMode)
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

return Archer
