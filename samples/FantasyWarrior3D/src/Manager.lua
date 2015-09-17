require "Helper"
local size = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

HeroPool = List.new()
DragonPool = List.new()
SlimePool = List.new()
PigletPool = List.new()
RatPool = List.new()
BossPool = List.new()

--getPoolByName
function getPoolByName(name)
    if name == "Piglet" then
        return PigletPool
    elseif name == "Slime" then
        return SlimePool
    elseif name == "Rat" then
        return RatPool
    elseif name == "Dragon" then
        return DragonPool
    elseif name == "Boss" then
        return BossPool
    else
        return HeroPool
    end
end


HeroManager = List.new()
MonsterManager = List.new()

local function solveCollision(object1, object2)
    local miniDistance = object1._radius + object2._radius
    local obj1Pos = cc.p(object1:getPosition())
    local obj2Pos = cc.p(object2:getPosition())
    local tempDistance = cc.pGetDistance(obj1Pos, obj2Pos)
    
    if tempDistance < miniDistance then
        local angle = cc.pToAngleSelf(cc.pSub(obj1Pos, obj2Pos))
        local distance = miniDistance - tempDistance + 1 -- Add extra 1 to avoid 'tempDistance < miniDistance' is always true
        local distance1 = (1 - object1._mass / (object1._mass + object2._mass) ) * distance
        local distance2 = distance - distance1

        object1:setPosition(cc.pRotateByAngle(cc.pAdd(cc.p(distance1,0),obj1Pos), obj1Pos, angle))
        object2:setPosition(cc.pRotateByAngle(cc.pAdd(cc.p(-distance2,0),obj2Pos), obj2Pos, angle))
    end  
end

local function collision(object)
    for val = HeroManager.first, HeroManager.last do
        local sprite = HeroManager[val]
        if sprite._isalive and sprite ~= object then
            solveCollision(sprite, object)
        end
    end

    for val = MonsterManager.first, MonsterManager.last do
        local sprite = MonsterManager[val]
        if sprite._isalive == true and sprite ~= object then
            solveCollision(sprite, object)
        end                  
    end      
end

local function isOutOfBound(object)
    local currentPos = cc.p(object:getPosition());

    if currentPos.x < G.activearea.left then
        currentPos.x = G.activearea.left
    end    

    if currentPos.x > G.activearea.right then
        currentPos.x = G.activearea.right
    end

    if currentPos.y < G.activearea.bottom then
        currentPos.y = G.activearea.bottom
    end

    if currentPos.y > G.activearea.top then
        currentPos.y = G.activearea.top
    end

    object:setPosition(currentPos)
end

function collisionDetect(dt)
    --cclog("collisionDetect")
    for val = HeroManager.last, HeroManager.first, -1 do
        local sprite = HeroManager[val]
        if sprite._isalive == true then
            collision(sprite)
            isOutOfBound(sprite)
            sprite._effectNode:setPosition(sprite._myPos)
        else
            List.remove(HeroManager, val)
        end
    end

    for val = MonsterManager.last, MonsterManager.first, -1 do
        local sprite = MonsterManager[val]
        if sprite._isalive == true then
            collision(sprite)
            isOutOfBound(sprite)          
        else
            List.remove(MonsterManager, val)
        end
    end           
end

function getFocusPointOfHeros()
    local ptFocus ={x=0, y=0}
    for var = HeroManager.last, HeroManager.first, -1 do
        ptFocus.x=ptFocus.x+HeroManager[var]:getPositionX()
        ptFocus.y=ptFocus.y+HeroManager[var]:getPositionY()
    end
    ptFocus.x = ptFocus.x/List.getSize(HeroManager)
    ptFocus.y = ptFocus.y/List.getSize(HeroManager)
    return ptFocus
end
