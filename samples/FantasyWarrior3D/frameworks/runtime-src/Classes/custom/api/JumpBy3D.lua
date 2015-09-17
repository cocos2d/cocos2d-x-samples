
--------------------------------
-- @module JumpBy3D
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  initializes the action 
-- @function [parent=#JumpBy3D] initWithDuration 
-- @param self
-- @param #float duration
-- @param #vec3_table position
-- @param #float height
-- @param #int jumps
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  creates the action 
-- @function [parent=#JumpBy3D] create 
-- @param self
-- @param #float duration
-- @param #vec3_table position
-- @param #float height
-- @param #int jumps
-- @return JumpBy3D#JumpBy3D ret (return value: cc.JumpBy3D)
        
--------------------------------
-- 
-- @function [parent=#JumpBy3D] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return JumpBy3D#JumpBy3D self (return value: cc.JumpBy3D)
        
--------------------------------
-- 
-- @function [parent=#JumpBy3D] clone 
-- @param self
-- @return JumpBy3D#JumpBy3D ret (return value: cc.JumpBy3D)
        
--------------------------------
-- 
-- @function [parent=#JumpBy3D] reverse 
-- @param self
-- @return JumpBy3D#JumpBy3D ret (return value: cc.JumpBy3D)
        
--------------------------------
-- 
-- @function [parent=#JumpBy3D] update 
-- @param self
-- @param #float time
-- @return JumpBy3D#JumpBy3D self (return value: cc.JumpBy3D)
        
--------------------------------
-- 
-- @function [parent=#JumpBy3D] JumpBy3D 
-- @param self
-- @return JumpBy3D#JumpBy3D self (return value: cc.JumpBy3D)
        
return nil
