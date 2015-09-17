require "GlobalVariables"
require "MessageDispatchCenter"
require "Helper"
require "AttackCommand"

local file = "model/slime/slime.c3b"

Slime = class("Slime", function()
    return require "Actor".create()
end)

function Slime:ctor()
    copyTable(ActorCommonValues, self)
    copyTable(SlimeValues,self)
    self._angryFace = false
    self:init3D()
    self:initActions()
end

function Slime.create()
    local ret = Slime.new()
    ret._AIEnabled = true

    --this update function do not do AI
    function update(dt)
        ret:baseUpdate(dt)
        ret:stateMachineUpdate(dt)
        ret:movementUpdate(dt)
    end
    ret:scheduleUpdateWithPriorityLua(update, 0.5) 
    ret:play3DAnim()
    return ret
end

function Slime:reset()
    copyTable(ActorCommonValues, self)
    copyTable(SlimeValues,self)
    self:_findEnemy(self._racetype)
    self:walkMode()
    self:setPositionZ(0)
end

function Slime:play3DAnim()
    self._sprite3d:runAction(cc.RepeatForever:create(createAnimation(file,0,22,0.7)))
    
end
function Slime:playAnimation(name, loop)
    if self._curAnimation ~= name then --using name to check which animation is playing
        self._sprite3d:stopAction(self._curAnimation3d)
        if loop then
            self._curAnimation3d = cc.RepeatForever:create(self._action[name]:clone())
        else
            self._curAnimation3d = self._action[name]:clone()
        end
        self._sprite3d:setPosition3D(cc.V3(0,0,0))
        self._sprite3d:setRotation3D(cc.V3(90,0,-90))
        self._sprite3d:runAction(self._curAnimation3d)
        self._curAnimation = name
    end
end
function Slime:init3D()
    self:initShadow()
    self._sprite3d = cc.EffectSprite3D:create(file)
    self._sprite3d:setTexture("model/slime/baozi.jpg")
    self._sprite3d:setScale(17)
    self._sprite3d:addEffect(cc.V3(0,0,0),CelLine, -1)
    self:addChild(self._sprite3d)
    self._sprite3d:setRotation3D({x = 90, y = 0, z = 0})        
    self._sprite3d:setRotation(-90)
end
--
function Slime:walkMode()
    self:angryFace(false)
    Actor.walkMode(self)
end
function Slime:attackMode()
    self:angryFace(true)
    Actor.attackMode(self)
end
function Slime:idleMode()
    self:angryFace(false)
    Actor.idleMode(self)
end
function Slime:knockMode(collider, dirKnockMode)
    self:angryFace(false)
    Actor.knockMode(self,collider,dirKnockMode)
end
function Slime:angryFace(trueFalse)
    if self._angryFace ~= trueFalse then
        self._angryFace = trueFalse
        if trueFalse then
            self._sprite3d:setTexture("model/slime/baozi2.jpg")
        else
            self._sprite3d:setTexture("model/slime/baozi.jpg")
        end
    end   
end

-- init Slime animations=============================
do
    local dur = 0.6
    local bsc = 17
    local walk = cc.Spawn:create(
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
    walk:retain()
    local idle = cc.Sequence:create(
        cc.ScaleTo:create(dur/2, bsc*1.1, bsc*1.1, bsc*0.8),
        cc.ScaleTo:create(dur/2, bsc,bsc,bsc)
    )
    idle:retain()
    local attack1 = cc.Spawn:create(
            cc.MoveBy:create(dur/2, cc.V3(0,0,20)),
            cc.RotateBy:create(dur/2, cc.V3(70,0,0)),
            cc.EaseBounceOut:create(cc.MoveTo:create(dur/2, cc.p(40, 0)))
        )
    local attack2 = cc.Spawn:create(
            cc.MoveTo:create(dur, cc.V3(0,0,0)),
                cc.RotateBy:create(dur*3/4, cc.V3(-70,0,0)),
                cc.EaseBackOut:create(cc.MoveTo:create(dur, cc.p(0,0)))
        )
    attack1:retain()
    attack2:retain()
    local die =         cc.Spawn:create(
        cc.Sequence:create(
            cc.JumpBy3D:create(dur/2, cc.V3(0,0,0), 30, 1),
            cc.ScaleBy:create(dur, 2, 2, 0.1)
        ),
        cc.RotateBy:create(dur, cc.V3(-90,0,0))
    )
    die:retain()
    local knock = cc.Sequence:create(
        cc.EaseBackInOut:create(cc.RotateBy:create(dur/3, cc.V3(-60,0,0))),
        cc.RotateBy:create(dur/2, cc.V3(60,0,0))
    )
    knock:retain()
    Slime._action = {
        idle = idle,
        walk = walk,
        attack1 = attack1,
        attack2 = attack2,
        dead = die,
        knocked = knock
    }
end
-- end init Slime animations========================
function Slime:initActions()
    self._action = Slime._action
end