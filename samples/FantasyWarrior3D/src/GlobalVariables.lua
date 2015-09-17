require "Helper"
--[[
Monster Actors Values：
]]--

---hurtEffect
cc.SpriteFrameCache:getInstance():addSpriteFrames("FX/FX.plist")
RECTS = {
    iceBolt = cc.SpriteFrameCache:getInstance():getSpriteFrame("icebolt.png"):getRect(),
    iceSpike =cc.SpriteFrameCache:getInstance():getSpriteFrame("iceSpike1.png"):getRect(),
    fireBall = cc.SpriteFrameCache:getInstance():getSpriteFrame("fireball1.png"):getRect(),
    thunderBall = cc.SpriteFrameCache:getInstance():getSpriteFrame("thunderball.png"):getRect(),
}
cc.SpriteFrameCache:getInstance():addSpriteFrames("battlefieldUI/battleFieldUI.plist")

animationCache = cc.AnimationCache:getInstance()
local hurtAnimation = cc.Animation:create()
for i=1,5 do
    name = "hit"..i..".png"
    hurtAnimation:addSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame(name))
end
hurtAnimation:setDelayPerUnit(0.1)
animationCache:addAnimation(hurtAnimation,"hurtAnimation")
local fireBallAnim = cc.Animation:create()
for i=2,5 do
    name = "fireball"..i..".png"
    fireBallAnim:addSpriteFrame(cc.SpriteFrameCache:getInstance():getSpriteFrame(name))
end
fireBallAnim:setDelayPerUnit(0.1)
animationCache:addAnimation(fireBallAnim,"fireBallAnim")

UIZorder = 2000
FXZorder = 1999
CelLine = 0.009
UserCameraFlagMask = 2

BossTaunt = "How dare you???"

--G values
G =
{
    winSize = cc.Director:getInstance():getWinSize(),
    bloodPercentDropSpeed = 2,
    activearea = {left = -2800, right = 1000, bottom = 100, top = 700},
}


--Audios
BGM_RES = 
{
    MAINMENUBGM = "audios/01 Beast Hunt.mp3",
    MAINMENUSTART= "audios/effects/magical_3.mp3",
    BATTLEFIELDBGM = "audios/The_Last_Encounter_Short_Loop.mp3",
    CHOOSEROLESCENEBGM = "audios/Imminent Threat Beat B FULL Loop.mp3"
}

--play2d id
AUDIO_ID = 
{
    MAINMENUBGM,
    BATTLEFIELDBGM,
    CHOOSEROLECHAPTERBGM,
    KNIGHTNORMALATTACK,
    KNIGHTSPECIALATTACK,
    ARCHERATTACK
}
EnumRaceType = 
    { 
        "HERO",  --only this
        "MONSTER", --and this
    }
EnumRaceType = CreateEnumTable(EnumRaceType) 

EnumStateType =
    {
        "IDLE",
        "WALKING",
        "ATTACKING",
        "DEFENDING",
        "KNOCKING",
        "DYING",
        "DEAD"
    }
EnumStateType = CreateEnumTable(EnumStateType) 
--common value is used to reset an actor
ActorCommonValues =
{
    _aliveTime      = 0, --time the actor is alive in seconds
    _curSpeed       = 0, --current speed the actor is traveling in units/seconds
    _curAnimation   = nil,
    _curAnimation3d = nil,
    
    --runtime modified values
    _curFacing      = 0, -- current direction the actor is facing, in radians, 0 is to the right
    _isalive        = true,
    _AITimer        = 0, -- accumulated timer before AI will execute, in seconds
    _AIEnabled      = false, --if false, AI will not run
    _attackTimer    = 0, --accumulated timer to decide when to attack, in seconds
    _timeKnocked    = 0, --accumulated timer to recover from knock, in seconds
    _cooldown       = false, --if its true, then you are currently playing attacking animation,
    _hp             = 1000, --current hit point
    _goRight        = true,
    
    --target variables
    _targetFacing   = 0, --direction the actor Wants to turn to
    
    _target         = nil, --the enemy actor 

    _myPos = cc.p(0, 0),
    
    _angry          = 0,
    _angryMax       = 500,
}
ActorDefaultValues =
{
    _racetype       = EnumRaceType.HERO, --type of the actor
    _statetype      = nil, -- AI state machine
    _sprite3d       = nil, --place to hold 3d model
    
    _radius         = 50, --actor collider size
    _mass           = 100, --weight of the role, it affects collision
    _shadowSize     = 70, --the size of the shadow under the actor

    --character strength
    _maxhp          = 1000,
    _defense        = 100,
    _specialAttackChance = 0, 
    _recoverTime    = 0.8,--time takes to recover from knock, in seconds
    
    _speed          = 500, --actor maximum movement speed in units/seconds
    _turnSpeed      = DEGREES_TO_RADIANS(225), --actor turning speed in radians/seconds
    _acceleration   = 750, --actor movement acceleration, in units/seconds
    _decceleration  = 750*1.7, --actor movement decceleration, in units/seconds
    
    _AIFrequency    = 1.0, --how often AI executes in seconds
    _attackFrequency = 0.01, --an attack move every few seconds
    _searchDistance = 5000, --distance which enemy can be found

    _attackRange    = 100, --distance the actor will stop and commence attack
    
    --attack collider info, it can be customized
    _normalAttack   = {--data for normal attack
        minRange = 0, -- collider inner radius
        maxRange = 130, --collider outer radius
        angle    = DEGREES_TO_RADIANS(30), -- collider angle, 360 for full circle, other wise, a fan shape is created
        knock    = 50, --attack knock back distance
        damage   = 800, -- attack damage
        mask     = EnumRaceType.HERO, -- who created this attack collider
        duration = 0, -- 0 duration means it will be removed upon calculation
        speed    = 0, -- speed the collider is traveling
        criticalChance=0
    }, 
}
KnightValues = {
    _racetype       = EnumRaceType.HERO,
    _name           = "Knight",
    _radius         = 50,
    _mass           = 1000,
    _shadowSize     = 70,
    
    _hp             = 1850,
    _maxhp          = 1850,
    _defense        = 180,
    _attackFrequency = 2.2,
    _recoverTime    = 0.4,
    _AIFrequency    = 1.1,
    _attackRange    = 140,
    _specialAttackChance = 0,
    _specialSlowTime = 1, 

    _normalAttack   = {
        minRange = 0,
        maxRange = 130,
        angle    = DEGREES_TO_RADIANS(70),
        knock    = 60,
        damage   = 250,
        mask     = EnumRaceType.HERO,
        duration = 0,
        speed    = 0,
        criticalChance = 0.15
    }, 
    _specialAttack   = {
        minRange = 0,
        maxRange = 250,
        angle    = DEGREES_TO_RADIANS(160),
        knock    = 150,
        damage   = 350,
        mask     = EnumRaceType.HERO,
        duration = 0,
        speed    = 0,
        criticalChance = 0.35
    }, 
}
MageValues = {
    _racetype       = EnumRaceType.HERO,
    _name           = "Mage",
    _radius         = 50,
    _mass           = 800,
    _shadowSize     = 70,

    _hp             = 1100,
    _maxhp          = 1100,
    _defense        = 120,
    _attackFrequency = 2.67,
    _recoverTime    = 0.8,
    _AIFrequency    = 1.33,
    _attackRange    = 400,
    _specialAttackChance = 0,
    _specialSlowTime = 0.67,

    _normalAttack   = {
        minRange = 0,
        maxRange = 50,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 10,
        damage   = 280,
        mask     = EnumRaceType.HERO,
        duration = 2,
        speed    = 400,
        criticalChance = 0.05
    }, 
    _specialAttack   = {
        minRange = 0,
        maxRange = 140,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 75,
        damage   = 250,
        mask     = EnumRaceType.HERO,
        duration = 4.5,
        speed    = 0,
        criticalChance = 0.05,
        DOTTimer = 0.75, --it will be able to hurt every 0.5 seconds
        curDOTTime = 0.75,
        DOTApplied = false
    }, 
}
ArcherValues = {
    _racetype       = EnumRaceType.HERO,
    _name           = "Archer",
    _radius         = 50,
    _mass           = 800,
    _shadowSize     = 70,

    _hp             = 1200,
    _maxhp          = 1200,
    _defense        = 130,
    _attackFrequency = 2.5,
    _recoverTime    = 0.4,
    _AIFrequency    = 1.3,
    _attackRange    = 450,
    _specialAttackChance = 0,
    _turnSpeed      = DEGREES_TO_RADIANS(360), --actor turning speed in radians/seconds
    _specialSlowTime = 0.5, 

    _normalAttack   = {
        minRange = 0,
        maxRange = 30,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 100,
        damage   = 200,
        mask     = EnumRaceType.HERO,
        duration = 1.3,
        speed    = 900,
        criticalChance = 0.33
    }, 
    _specialAttack   = {
        minRange = 0,
        maxRange = 75,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 100,
        damage   = 200,
        mask     = EnumRaceType.HERO,
        duration = 1.5,
        speed    = 850,
        criticalChance = 0.5,
        DOTTimer = 0.3,
        curDOTTime = 0.3,
        DOTApplied = false
    }, 
}
DragonValues = {
    _racetype       = EnumRaceType.MONSTER,
    _name           = "Dragon",
    _radius         = 50,
    _mass           = 100,
    _shadowSize     = 70,

    _hp             = 600,
    _maxhp          = 600,
    _defense        = 130,
    _attackFrequency = 5.2,
    _recoverTime    = 0.8,
    _AIFrequency    = 1.337,
    _attackRange    = 350,
    
    _speed          = 300,
    _turnSpeed      = DEGREES_TO_RADIANS(180),
    _acceleration   = 250,
    _decceleration  = 750*1.7,

    _normalAttack   = {
        minRange = 0,
        maxRange = 40,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 50,
        damage   = 400,
        mask     = EnumRaceType.MONSTER,
        duration = 1,
        speed    = 350,
        criticalChance = 0.15
    }, 
}
SlimeValues = {
    _racetype       = EnumRaceType.MONSTER,
    _name           = "Slime",
    _radius         = 35,
    _mass           = 20,
    _shadowSize     = 45,

    _hp             = 300,
    _maxhp          = 300,
    _defense        = 65,
    _attackFrequency = 1.5,
    _recoverTime    = 0.7,
    _AIFrequency    = 3.3,
    _AITimer        = 2.0,
    _attackRange    = 50,
    
    _speed          = 150,
    _turnSpeed      = DEGREES_TO_RADIANS(270),
    _acceleration   = 9999,
    _decceleration  = 9999,

    _normalAttack   = {
        minRange = 0,
        maxRange = 50,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 0,
        damage   = 135,
        mask     = EnumRaceType.MONSTER,
        duration = 0,
        speed    = 0,
        criticalChance = 0.13
    }, 
}
PigletValues = {
    _racetype       = EnumRaceType.MONSTER,
    _name           = "Piglet",
    _radius         = 50,
    _mass           = 69,
    _shadowSize     = 60,

    _hp             = 400,
    _maxhp          = 400,
    _defense        = 65,
    _attackFrequency = 4.73,
    _recoverTime    = 0.9,
    _AIFrequency    = 2.3,
    _attackRange    = 120,

    _speed          = 350,
    _turnSpeed      = DEGREES_TO_RADIANS(270),

    _normalAttack   = {
        minRange = 0,
        maxRange = 120,
        angle    = DEGREES_TO_RADIANS(50),
        knock    = 0,
        damage   = 150,
        mask     = EnumRaceType.MONSTER,
        duration = 0,
        speed    = 0,
        criticalChance = 0.15
    }, 
}
RatValues = {
    _racetype       = EnumRaceType.MONSTER,
    _name           = "Rat",
    _radius         = 70,
    _mass           = 990,
    _shadowSize     = 90,

    _hp             = 2800,
    _maxhp          = 2800,
    _defense        = 200,
    _attackFrequency = 3.0,
    _recoverTime    = 0.4,
    _AIFrequency    = 5.3,
    _AITimer        = 5.0,
    _attackRange    = 150,

    _speed          = 400,
    _turnSpeed      = DEGREES_TO_RADIANS(180),
    _acceleration   = 200,
    _decceleration  = 750*1.7,

    _normalAttack   = {
        minRange = 0,
        maxRange = 150,
        angle    = DEGREES_TO_RADIANS(100),
        knock    = 250,
        damage   = 210,
        mask     = EnumRaceType.MONSTER,
        duration = 0,
        speed    = 0,
        criticalChance =1
    }, 
}
BossValues = {
    _racetype       = EnumRaceType.MONSTER,
    _name           = "Boss",
    _radius         = 50,
    _mass           = 100,
    _shadowSize     = 65,

    _hp             = 400,
    _maxhp          = 450,
    _defense        = 170,
    _attackFrequency = 3.7,
    _recoverTime    = 0.4,
    _AIFrequency    = 5.3,
    _AITimer        = 5.0,
    _attackRange    = 110,

    _speed          = 300,
    _turnSpeed      = DEGREES_TO_RADIANS(225),
    _acceleration   = 450,
    _decceleration  = 750*1.7,

    _normalAttack   = {
        minRange = 0,
        maxRange = 110,
        angle    = DEGREES_TO_RADIANS(100),
        knock    = 50,
        damage   = 200,
        mask     = EnumRaceType.MONSTER,
        duration = 0,
        speed    = 0,
        criticalChance = 0.15
    }, 
    nova   = {
        minRange = 0,
        maxRange = 250,
        angle    = DEGREES_TO_RADIANS(360),
        knock    = 120,
        damage   = 250,
        mask     = EnumRaceType.MONSTER,
        duration = 0.5,
        speed    = 0,
        criticalChance = 0.15,
        DOTTimer = 0.3,
        curDOTTime = 0.3,
        DOTApplied = false
    }, 
}

--Some common audios
CommonAudios =
{
    hit = "audios/effects/hit20.mp3"
}

--Monster Slime
MonsterSlimeValues =
{
    fileNameNormal = "model/slime/slimeAnger.c3b",
    fileNameAnger = "model/slime/slimeAnger.c3b"
}

--Monster Dragon
MonsterDragonValues = 
{
    fileName = "model/dragon/dragon.c3b",
    attack = "audios/effects/dragon/Fire.mp3",
    fireHit = "audios/effects/dragon/fireHit.mp3",
    wounded="audios/effects/dragon/hurt.mp3",
    dead="audios/effects/dragon/dead.mp3"
}

--Monster Rat
MonsterRatValues = 
    {
        fileName = "model/rat/rat.c3b",
        attack = "audios/effects/rat/attack.mp3",
        dead ="aduios/effects/rat/dead.mp3",
        wounded="audios/effects/rat/ratHurt.mp3"
    }

--Monster Piglet
MonsterPigletValues = 
{
    fileName = "model/piglet/piglet.c3b",
    attack1 = "audios/effects/piglet/piglet1.mp3",
    attack2 = "audios/effects/piglet/piglet2.mp3",
    attack3 = "audios/effects/piglet/piglet3.mp3",
    dead = "audios/effects/piglet/dead.mp3",
    hurt = "audios/effects/piglet/hurt.mp3",
}
    
--Warroir property
WarriorProperty =
{
    normalAttack1 = "audios/effects/knight/swish-1.mp3",
    normalAttack2 = "audios/effects/knight/swish-2.mp3",
    specialAttack1 = "audios/effects/knight/swish-3.mp3",
    specialAttack2 = "audios/effects/knight/swish-4.mp3",
    kickit = "audios/effects/knight/kickit.mp3",
    normalAttackShout = "audios/effects/knight/normalAttackShout.mp3",
    specialAttackShout = "audios/effects/knight/specialAttackShout.mp3",
    wounded = "audios/effects/knight/wounded.mp3",
    dead = "audios/effects/knight/dead.mp3"
}

--Archer property
Archerproperty =
{
    attack1 = "audios/effects/archer/swish-3.mp3",
    attack2 = "audios/effects/archer/swish-4.mp3",
    iwillfight = "audios/effects/archer/iwillfight.mp3",
    wounded = "audios/effects/archer/hurt.mp3",
    normalAttackShout = "audios/effects/archer/normalAttackShout.mp3",
    specialAttackShout = "audios/effects/archer/specialAttackShout.mp3",
    wounded = "audios/effects/archer/hurt.mp3",
    dead = "audios/effects/archer/dead.mp3"
}

--Mage property
MageProperty =
{
    blood = 1000,
    attack = 100,
    defense = 100,
    speed = 50,
    special_attack_chance = 0.33,
        letstrade = "audios/effects/mage/letstrade.mp3",
    ice_normal = "audios/effects/mage/ice_1.mp3",
    ice_special = "audios/effects/mage/ice_2.mp3",
    ice_normalAttackHit = "audios/effects/mage/ice_3.mp3",
    ice_specialAttackHit = "audios/effects/mage/ice_4.mp3",
    specialAttackShout = "audios/effects/mage/specialAttack.mp3",
    normalAttackShout = "audios/effects/mage/normalAttack.mp3",
    wounded = "audios/effects/mage/hurt.mp3",
    dead = "audios/effects/mage/dead.mp3"
}

ReSkin = 
{
    knight = {weapon = 0, armour = 0, helmet = 0},
    archer = {weapon = 0, armour = 0, helmet = 0},
    mage = {weapon = 0, armour = 0, helmet = 0}
}