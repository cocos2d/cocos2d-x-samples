ParticleManager = {}  

function ParticleManager:new(o)  
    o = o or {}  
    setmetatable(o,self)  
    self.__index = self  
    self._plistMap = {}
    return o  
end  
  
function ParticleManager:getInstance()
    if self.instance == nil then  
        self.instance = self:new()
    end  
    return self.instance  
end 

function ParticleManager:AddPlistData(fileName, keyName)
	if fileName == "" or keyName == "" then return end
	for k in pairs(self._plistMap) do
		if keyName == k then
			cclog("the keyName is exist already.")
			return
		end
	end
	local plistData = cc.FileUtils:getInstance():getValueMapFromFile(fileName)
	self._plistMap[keyName]=plistData
end
	
function ParticleManager:getPlistData(keyName)
	if keyName == "" then return end
	for k in pairs(self._plistMap) do
		if keyName == k then
			return self._plistMap[keyName]
		end
	end
	cclog("can't find plistData by the specified keyName.")
end