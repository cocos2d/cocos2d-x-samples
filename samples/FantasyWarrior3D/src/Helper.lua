--global var
camera =nil


CC_CONTENT_SCALE_FACTOR = function()
    return cc.Director:getInstance():getContentScaleFactor()
end


CC_POINT_PIXELS_TO_POINTS = function(pixels)
    return cc.p(pixels.x/CC_CONTENT_SCALE_FACTOR(), pixels.y/CC_CONTENT_SCALE_FACTOR())
end

CC_POINT_POINTS_TO_PIXELS = function(points)
    return cc.p(points.x*CC_CONTENT_SCALE_FACTOR(), points.y*CC_CONTENT_SCALE_FACTOR())
end

--print table
function printTab(tab)
  for i,v in pairs(tab) do
    if type(v) == "table" then
      print("table",i,"{")
      printTab(v)
      print("}")
    else
     print(v)
    end
  end
end

--radiansNormalizer
function radNormalize(rad)
    local pi2 = 2*math.pi
    rad = rad % pi2
    rad = (rad + pi2)%pi2
    if rad > math.pi then
        rad = rad - math.pi
    end
    return rad
end

-- getpostable
function getPosTable(obj)
	local posX,posY = obj:getPosition()
	return {x= posX,y=posY} 
end

--getnextpos
function getNextStepPos(curPos, targetPos, speed, dt)
	local angel = math.atan2(targetPos.y-curPos.y,targetPos.x-curPos.x)
    return {x = curPos.x+math.cos(angel)*speed*dt, y = curPos.y+math.sin(angel)*speed*dt}
end

--createAnimationStruct
function createAnimationStruct(var1, var2, var3)
    local timerange = {begin = var1, ended = var2, speed=var3}
    return timerange
end
function createAnimation(file, begin, finish, speed)
--TODO: we don't need to create the same Animation3D all the time
    local animation3d = cc.Animation3D:create(file)
    local animate3d = cc.Animate3D:create(animation3d, begin/30,(finish-begin)/30)
    animate3d:setSpeed(speed)
    animate3d:retain()
    return animate3d
end

--createKnockedMessageStruct
function createKnockedMsgStruct(object)
    local msgStruct = {attacker = object, target = object._target}
    return msgStruct
end

-- cclog
cclog = function(...)
    print(string.format(...))
end

-- change table to enum type
function CreateEnumTable(tbl, index)
    local enumTable = {}
    local enumIndex = index or -1
    for i, v in ipairs(tbl) do
        enumTable[v] = enumIndex + i
    end
    return enumTable
end

function removeAll(table)
    while true do
        local k =next(table)
        if not k then break end
        table[k] = nil
    end
end

List = {}
function List.new()
	return {first = 0, last = -1}
end

function List.pushfirst(list, value)
	local first = list.first - 1
	list.first = first
	list[first] = value
end

function List.pushlast(list, value)
	local last = list.last + 1
	list.last = last
	list[last] = value
end

function List.popfirst(list)
	local first = list.first
	if first > list.last then return nil end
	local value = list[first]
	list[first] = nil
	list.first = first + 1
	return value
end

function List.poplast(list)
	local last = list.last
	if list.first > last then return nil end
	local value = list[last]
	list[last] = nil
	list.last = last - 1
	return value	
end

function List.removeAll(list)
    removeAll(list)
    list.first = 0
    list.last = -1
end

function List.getSize(list)
    return list.last - list.first + 1
end

function List.first(list)
    local value = nil
    if list.first <= list.last then
        value = list[first]
    end
    
    return value
end

function List.remove(list, index)
    if index < list.first or index > list.last then return end
    
    while index <= list.last do
        list[index] = nil
        list[index] = list[index+1]
        index = index + 1
    end
    
    list.last = list.last -1
end

function List.removeObj(list, obj)
    if obj == nil or List.getSize(list) == 0 then return end
    
    for index=list.first, List.getSize(list) do
    	if list[index] == obj then
    		List.remove(list,index)
    		break
    	end
    end    
end

function copyTable(t1, t2)
    for key, var in pairs(t1) do
        t2[key] = var
    end
end

function delayExecute(target, func, delay)
    local wait = cc.DelayTime:create(delay)
    target:runAction(cc.Sequence:create(wait, cc.CallFunc:create(func)))
end

function DEGREES_TO_RADIANS(__ANGLE__) 
    return __ANGLE__ * 0.01745329252
end
function RADIANS_TO_DEGREES(__ANGLE__)
    return __ANGLE__ * 57.29577951
end