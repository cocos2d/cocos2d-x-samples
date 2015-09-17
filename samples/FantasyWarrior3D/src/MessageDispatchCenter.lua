MessageDispatchCenter = {}

MessageDispatchCenter.MessageType = {
    BLOOD_MINUS = "BLOOD_MINUS",
    REDUCE_SCORE = "REDUCE_SCORE",
    KNOCKED = "KNOCKED",
    KNOCKEDAOE = "KNOCKEDAOE",
    SPECIAL_PERSPECTIVE = "SPECIAL_PERSPECTIVE",
    SPECIAL_KNIGHT = "SPECIAL_KNIGHT",
    SPECIAL_ARCHER = "SPECIAL_ARCHER",
    SPECIAL_MAGE = "SPECIAL_MAGE",
    ANGRY_CHANGE = "ANGRY_CHANGE",
}

MessageDispatchCenter.MessageQue = {}

--function MessageDispatchCenter:new(o)  
--    o = o or {}  
--    setmetatable(o,self)  
--    self.__index = self  
--    return o  
--end  
--
--function MessageDispatchCenter:getInstance()  
--    if self.instance == nil then  
--        self.instance = self:new()  
--    end  
--    return self.instance  
--end  

--need param messageType and callback function
function MessageDispatchCenter:registerMessage(messageType,callback)
    --if param is valid
    if self.MessageType[messageType] == nil or type(callback) ~= "function" then
        print("param is invalid")
        return
    end
    
    --add message to messageQue
    if self.MessageQue[messageType] == nil then
        self.MessageQue[messageType] = {}
    end
    local index = table.getn(self.MessageQue[messageType])
    self.MessageQue[messageType][index+1] = callback
    
--    for i,v in pairs(self.MessageQue) do
--        print(table.getn(v))
--        for ii,vv in pairs(v) do
--            print(ii,vv)
--        end
--    end
--    print("----------------------------")
end

function MessageDispatchCenter:dispatchMessage(messageType,param)
    --if param is valid
    if self.MessageType[messageType] == nil then
        print("param is invalid")
        return
    end
    
    --callback
    if self.MessageQue[messageType] == nil then
        return
    end
    for i,v in pairs(self.MessageQue[messageType]) do
        v(param)
    end
end

function MessageDispatchCenter:removeMessage(messageType,callback)
    --if param is valid
    if self.MessageType[messageType] == nil or type(callback) ~= "function" then
        print("param is invalid")
        return
    end
    
    --remove callback
    for i,v in pairs(self.MessageQue[messageType]) do
        if callback == v then
            table.remove(self.MessageQue[messageType],i)
            return
        end
    end
end

return MessageDispatchCenter
