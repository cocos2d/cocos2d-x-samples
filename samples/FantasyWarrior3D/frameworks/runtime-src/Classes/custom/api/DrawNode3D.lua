
--------------------------------
-- @module DrawNode3D
-- @extend Node
-- @parent_module cc

--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#DrawNode3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- endcode<br>
-- lua NA
-- @function [parent=#DrawNode3D] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
--------------------------------
-- Draw 3D Line
-- @function [parent=#DrawNode3D] drawLine 
-- @param self
-- @param #vec3_table from
-- @param #vec3_table to
-- @param #color4f_table color
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
--------------------------------
--  Clear the geometry in the node's buffer. 
-- @function [parent=#DrawNode3D] clear 
-- @param self
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
--------------------------------
-- 
-- @function [parent=#DrawNode3D] onDraw 
-- @param self
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
--------------------------------
-- 
-- @function [parent=#DrawNode3D] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Draw 3D cube<br>
-- param point to a vertex array who has 8 element.<br>
-- vertices[0]:Left-top-front,<br>
-- vertices[1]:Left-bottom-front,<br>
-- vertices[2]:Right-bottom-front,<br>
-- vertices[3]:Right-top-front,<br>
-- vertices[4]:Right-top-back,<br>
-- vertices[5]:Right-bottom-back,<br>
-- vertices[6]:Left-bottom-back,<br>
-- vertices[7]:Left-top-back.<br>
-- param color
-- @function [parent=#DrawNode3D] drawCube 
-- @param self
-- @param #vec3_table vertices
-- @param #color4f_table color
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
--------------------------------
--  creates and initialize a DrawNode3D node 
-- @function [parent=#DrawNode3D] create 
-- @param self
-- @return DrawNode3D#DrawNode3D ret (return value: cc.DrawNode3D)
        
--------------------------------
-- 
-- @function [parent=#DrawNode3D] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
--------------------------------
-- 
-- @function [parent=#DrawNode3D] DrawNode3D 
-- @param self
-- @return DrawNode3D#DrawNode3D self (return value: cc.DrawNode3D)
        
return nil
