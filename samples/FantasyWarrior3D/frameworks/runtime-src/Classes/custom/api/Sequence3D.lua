
--------------------------------
-- @module Sequence3D
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  initializes the action 
-- @function [parent=#Sequence3D] initWithActions 
-- @param self
-- @param #array_table arrayOfActions
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  helper constructor to create an array of sequenceable actions given an array<br>
-- code<br>
-- When this funtion bound to the js or lua,the input params changed<br>
-- in js  :var   create(var   object1,var   object2, ...)<br>
-- in lua :local create(local object1,local object2, ...)<br>
-- endcode
-- @function [parent=#Sequence3D] create 
-- @param self
-- @param #array_table arrayOfActions
-- @return Sequence3D#Sequence3D ret (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Sequence3D#Sequence3D self (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] reverse 
-- @param self
-- @return Sequence3D#Sequence3D ret (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] clone 
-- @param self
-- @return Sequence3D#Sequence3D ret (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] stop 
-- @param self
-- @return Sequence3D#Sequence3D self (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] update 
-- @param self
-- @param #float t
-- @return Sequence3D#Sequence3D self (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] step 
-- @param self
-- @param #float dt
-- @return Sequence3D#Sequence3D self (return value: cc.Sequence3D)
        
--------------------------------
-- 
-- @function [parent=#Sequence3D] Sequence3D 
-- @param self
-- @return Sequence3D#Sequence3D self (return value: cc.Sequence3D)
        
return nil
