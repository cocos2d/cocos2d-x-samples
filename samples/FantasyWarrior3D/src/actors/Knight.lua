require "GlobalVariables"
require "MessageDispatchCenter"
require "Helper"
require "AttackCommand"

local file = "model/knight/knight.c3b"

Knight = class("Knight", function()
    return require "Actor".create()
end)

function Knight:ctor()
    self._useWeaponId = ReSkin.knight.weapon
    self._useArmourId = ReSkin.knight.armour
    self._useHelmetId = ReSkin.knight.helmet
    copyTable(ActorCommonValues, self)
    copyTable(KnightValues,self)

    if uiLayer~=nil then
        self._bloodBar = uiLayer.KnightBlood
        self._bloodBarClone = uiLayer.KnightBloodClone
        self._avatar = uiLayer.KnightPng
    end

    self:init3D()
    self:initActions()
end

function Knight.create()
    local ret = Knight.new()    
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
    end
    MessageDispatchCenter:registerMessage(MessageDispatchCenter.MessageType.SPECIAL_KNIGHT, specialAttack)    
    return ret
end

local function KnightNormalAttackCallback(audioID,filePath)
    ccexp.AudioEngine:play2d(WarriorProperty.normalAttack2, false,1)
end

local function KninghtSpecialAttackCallback(audioID, filePatch)
    ccexp.AudioEngine:play2d(WarriorProperty.specialAttack2, false,1)  
end

function Knight:playDyingEffects()
    ccexp.AudioEngine:play2d(WarriorProperty.dead, false,1)
end

function Knight:hurtSoundEffects()
    ccexp.AudioEngine:play2d(WarriorProperty.wounded, false,0.7)
end

function Knight:normalAttack()
    ccexp.AudioEngine:play2d(WarriorProperty.normalAttackShout, false,0.6)
    KnightNormalAttack.create(getPosTable(self), self._curFacing, self._normalAttack, self)
    --self._sprite:runAction(self._action.attackEffect:clone()) 

    AUDIO_ID.KNIGHTNORMALATTACK = ccexp.AudioEngine:play2d(WarriorProperty.normalAttack1, false,1)
    ccexp.AudioEngine:setFinishCallback(AUDIO_ID.KNIGHTNORMALATTACK,KnightNormalAttackCallback)
end

function Knight:specialAttack()
    self._specialAttackChance = KnightValues._specialAttackChance
    self._angry = ActorCommonValues._angry
    local anaryChange = {_name = self._name, _angry = self._angry, _angryMax = self._angryMax}
    MessageDispatchCenter:dispatchMessage(MessageDispatchCenter.MessageType.ANGRY_CHANGE, anaryChange)      
        
    -- knight will create 2 attacks one by one  
    local attack = self._specialAttack
    attack.knock = 0
    ccexp.AudioEngine:play2d(WarriorProperty.specialAttackShout, false,0.7)
    KnightNormalAttack.create(getPosTable(self), self._curFacing, attack, self)
    self._sprite:runAction(self._action.attackEffect:clone())

    local pos = getPosTable(self)
    pos.x = pos.x+50
    pos = cc.pRotateByAngle(pos, self._myPos, self._curFacing)    

    AUDIO_ID.KNIGHTSPECIALATTACK = ccexp.AudioEngine:play2d(WarriorProperty.specialAttack1, false,1)
    ccexp.AudioEngine:setFinishCallback(AUDIO_ID.KNIGHTSPECIALATTACK,KninghtSpecialAttackCallback)
    
    local function punch()
        KnightNormalAttack.create(pos, self._curFacing, self._specialAttack, self)
        self._sprite:runAction(self._action.attackEffect:clone())                
    end
    delayExecute(self,punch,0.2)
end

function Knight:initAttackEffect()
    local speed = 0.15
    local startRotate = 145
    local rotate = -60
    local scale = 0.01
    local sprite = cc.Sprite:createWithSpriteFrameName("specialAttack.jpg")
    sprite:setVisible(false)
    sprite:setBlendFunc(gl.ONE,gl.ONE)
    sprite:setScaleX(scale)
    sprite:setRotation(startRotate)
    sprite:setOpacity(0)
    sprite:setAnchorPoint(cc.p(0.5, -0.5))    
    sprite:setPosition3D(cc.V3(10, 0, 50))
    self:addChild(sprite)

    local scaleAction = cc.ScaleTo:create(speed, 2.5, 2.5)
    local rotateAction = cc.RotateBy:create(speed, rotate)
    local fadeAction = cc.FadeIn:create(0)
    local attack = cc.Spawn:create(scaleAction, rotateAction, fadeAction)

    
    local fadeAction2 = cc.FadeOut:create(0.5)
    local scaleAction2 = cc.ScaleTo:create(0, scale, 2.5)
    local rotateAction2 = cc.RotateTo:create(0, startRotate)
    local restore = cc.Sequence:create(fadeAction2, scaleAction2, rotateAction2)

    self._sprite = sprite
    self._action.attackEffect = cc.Sequence:create(cc.Show:create(), attack, restore)    
    self._action.attackEffect:retain()
end


function Knight:init3D()
    self:initShadow()
    self:initPuff()
    self._sprite3d = cc.EffectSprite3D:create(file)
    self._sprite3d:setScale(25)
    self._sprite3d:addEffect(cc.V3(0,0,0),CelLine, -1)
    self:addChild(self._sprite3d)
    self._sprite3d:setRotation3D({x = 90, y = 0, z = 0})        
    self._sprite3d:setRotation(-90)
    self:setDefaultEqt()
end



-- init knight animations=============================
do
    Knight._action = {
        idle = createAnimation(file,267,283,0.7),
        walk = createAnimation(file,227,246,0.7),
        attack1 = createAnimation(file,103,129,0.7),
        attack2 = createAnimation(file,130,154,0.7),
        specialattack1 = createAnimation(file,160,190,1),
        specialattack2 = createAnimation(file,191,220,1),
        defend = createAnimation(file,92,96,0.7),
        knocked = createAnimation(file,254,260,0.7),
        dead = createAnimation(file,0,77,1)
    }
end
-- end init knight animations========================
function Knight:initActions()
    self._action = Knight._action
    self._action.effect = self:initAttackEffect()    
end

-- set default equipments
function Knight:setDefaultEqt()
    self:updateWeapon()
    self:updateHelmet()
    self:updateArmour()
end

function Knight:updateWeapon()
    if self._useWeaponId == 0 then
        local weapon = self._sprite3d:getMeshByName("zhanshi_wuqi01")
        weapon:setVisible(true)
        weapon = self._sprite3d:getMeshByName("zhanshi_wuqi02")
        weapon:setVisible(false)
    else
        local weapon = self._sprite3d:getMeshByName("zhanshi_wuqi02")
        weapon:setVisible(true)
        weapon = self._sprite3d:getMeshByName("zhanshi_wuqi01")
        weapon:setVisible(false)
    end
end

function Knight:updateHelmet()
    if self._useHelmetId == 0 then
        local helmet = self._sprite3d:getMeshByName("zhanshi_tou01")
        helmet:setVisible(true)
        helmet = self._sprite3d:getMeshByName("zhanshi_tou02")
        helmet:setVisible(false)
    else
        local helmet = self._sprite3d:getMeshByName("zhanshi_tou02")
        helmet:setVisible(true)
        helmet = self._sprite3d:getMeshByName("zhanshi_tou01")
        helmet:setVisible(false)
    end
end

function Knight:updateArmour()
    if self._useArmourId == 0 then
        local armour = self._sprite3d:getMeshByName("zhanshi_shenti01")
        armour:setVisible(true)
        armour = self._sprite3d:getMeshByName("zhanshi_shenti02")
        armour:setVisible(false)
    else
        local armour = self._sprite3d:getMeshByName("zhanshi_shenti02")
        armour:setVisible(true)
        armour = self._sprite3d:getMeshByName("zhanshi_shenti01")
        armour:setVisible(false)
    end
end

--swicth weapon
function Knight:switchWeapon()
    self._useWeaponId = self._useWeaponId+1
    if self._useWeaponId > 1 then
        self._useWeaponId = 0;
    end
    self:updateWeapon()
end

--switch helmet
function Knight:switchHelmet()
    self._useHelmetId = self._useHelmetId+1
    if self._useHelmetId > 1 then
        self._useHelmetId = 0;
    end
    self:updateHelmet()
end

--switch armour
function Knight:switchArmour()
    self._useArmourId = self._useArmourId+1
    if self._useArmourId > 1 then
        self._useArmourId = 0;
    end
    self:updateArmour()
end


-- get weapon id
function Knight:getWeaponID()
    return self._useWeaponId
end

-- get armour id
function Knight:getArmourID()
    return self._useArmourId
end

-- get helmet id
function Knight:getHelmetID()
    return self._useHelmetId
end
function Knight:hurt(collider, dirKnockMode)
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
return Knight
