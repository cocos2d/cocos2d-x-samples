#include "lua_cocos2dx_custom.hpp"
#include "ShadowSprite.h"
#include "EffectSprite3D.h"
#include "DrawNode3D.h"
#include "BillboardParticleSystem.h"
#include "JumpBy3D.h"
#include "JumpTo3D.h"
#include "JumpBy3D.h"
#include "Water.h"
#include "EffectSprite.h"
#include "CCSequence3D.h"
#include "GreyShader.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_custom_ShadowSprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ShadowSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ShadowSprite:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ShadowSprite_create'", nullptr);
            return 0;
        }
        cocos2d::ShadowSprite* ret = cocos2d::ShadowSprite::create(arg0);
        object_to_luaval<cocos2d::ShadowSprite>(tolua_S, "cc.ShadowSprite",(cocos2d::ShadowSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ShadowSprite:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ShadowSprite_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ShadowSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ShadowSprite:createWithSpriteFrameName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName'", nullptr);
            return 0;
        }
        cocos2d::ShadowSprite* ret = cocos2d::ShadowSprite::createWithSpriteFrameName(arg0);
        object_to_luaval<cocos2d::ShadowSprite>(tolua_S, "cc.ShadowSprite",(cocos2d::ShadowSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ShadowSprite:createWithSpriteFrameName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ShadowSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::SpriteFrame* arg0;
        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0, "cc.ShadowSprite:createWithSpriteFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrame'", nullptr);
            return 0;
        }
        cocos2d::ShadowSprite* ret = cocos2d::ShadowSprite::createWithSpriteFrame(arg0);
        object_to_luaval<cocos2d::ShadowSprite>(tolua_S, "cc.ShadowSprite",(cocos2d::ShadowSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ShadowSprite:createWithSpriteFrame",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrame'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_ShadowSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ShadowSprite)");
    return 0;
}

int lua_register_cocos2dx_custom_ShadowSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ShadowSprite");
    tolua_cclass(tolua_S,"ShadowSprite","cc.ShadowSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"ShadowSprite");
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_ShadowSprite_create);
        tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrameName);
        tolua_function(tolua_S,"createWithSpriteFrame", lua_cocos2dx_custom_ShadowSprite_createWithSpriteFrame);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ShadowSprite).name();
    g_luaType[typeName] = "cc.ShadowSprite";
    g_typeCast["ShadowSprite"] = "cc.ShadowSprite";
    return 1;
}

int lua_cocos2dx_custom_Effect3D_draw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect3D_draw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Mat4 arg0;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.Effect3D:draw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect3D_draw'", nullptr);
            return 0;
        }
        cobj->draw(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect3D:draw",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect3D_draw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_Effect3D_setTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect3D_setTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Sprite3D* arg0;
        cocos2d::Mesh* arg1;

        ok &= luaval_to_object<cocos2d::Sprite3D>(tolua_S, 2, "cc.Sprite3D",&arg0, "cc.Effect3D:setTarget");

        ok &= luaval_to_object<cocos2d::Mesh>(tolua_S, 3, "cc.Mesh",&arg1, "cc.Effect3D:setTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect3D_setTarget'", nullptr);
            return 0;
        }
        cobj->setTarget(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect3D:setTarget",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect3D_setTarget'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_custom_Effect3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Effect3D)");
    return 0;
}

int lua_register_cocos2dx_custom_Effect3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Effect3D");
    tolua_cclass(tolua_S,"Effect3D","cc.Effect3D","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Effect3D");
        tolua_function(tolua_S,"draw",lua_cocos2dx_custom_Effect3D_draw);
        tolua_function(tolua_S,"setTarget",lua_cocos2dx_custom_Effect3D_setTarget);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Effect3D).name();
    g_luaType[typeName] = "cc.Effect3D";
    g_typeCast["Effect3D"] = "cc.Effect3D";
    return 1;
}

int lua_cocos2dx_custom_Effect3DOutline_setOutlineWidth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect3DOutline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect3DOutline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect3DOutline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect3DOutline_setOutlineWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.Effect3DOutline:setOutlineWidth");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect3DOutline_setOutlineWidth'", nullptr);
            return 0;
        }
        cobj->setOutlineWidth(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect3DOutline:setOutlineWidth",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect3DOutline_setOutlineWidth'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_Effect3DOutline_setOutlineColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect3DOutline* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect3DOutline",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect3DOutline*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect3DOutline_setOutlineColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.Effect3DOutline:setOutlineColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect3DOutline_setOutlineColor'", nullptr);
            return 0;
        }
        cobj->setOutlineColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect3DOutline:setOutlineColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect3DOutline_setOutlineColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_Effect3DOutline_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Effect3DOutline",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect3DOutline_create'", nullptr);
            return 0;
        }
        cocos2d::Effect3DOutline* ret = cocos2d::Effect3DOutline::create();
        object_to_luaval<cocos2d::Effect3DOutline>(tolua_S, "cc.Effect3DOutline",(cocos2d::Effect3DOutline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Effect3DOutline:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect3DOutline_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_Effect3DOutline_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Effect3DOutline)");
    return 0;
}

int lua_register_cocos2dx_custom_Effect3DOutline(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Effect3DOutline");
    tolua_cclass(tolua_S,"Effect3DOutline","cc.Effect3DOutline","cc.Effect3D",nullptr);

    tolua_beginmodule(tolua_S,"Effect3DOutline");
        tolua_function(tolua_S,"setOutlineWidth",lua_cocos2dx_custom_Effect3DOutline_setOutlineWidth);
        tolua_function(tolua_S,"setOutlineColor",lua_cocos2dx_custom_Effect3DOutline_setOutlineColor);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_Effect3DOutline_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Effect3DOutline).name();
    g_luaType[typeName] = "cc.Effect3DOutline";
    g_typeCast["Effect3DOutline"] = "cc.Effect3DOutline";
    return 1;
}

int lua_cocos2dx_custom_EffectSprite3D_setEffect3D(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectSprite3D_setEffect3D'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Effect3D* arg0;

        ok &= luaval_to_object<cocos2d::Effect3D>(tolua_S, 2, "cc.Effect3D",&arg0, "cc.EffectSprite3D:setEffect3D");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite3D_setEffect3D'", nullptr);
            return 0;
        }
        cobj->setEffect3D(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectSprite3D:setEffect3D",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite3D_setEffect3D'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectSprite3D_addEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectSprite3D_addEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec3 arg0;
        double arg1;
        ssize_t arg2;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.EffectSprite3D:addEffect");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.EffectSprite3D:addEffect");

        ok &= luaval_to_ssize(tolua_S, 4, &arg2, "cc.EffectSprite3D:addEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite3D_addEffect'", nullptr);
            return 0;
        }
        cobj->addEffect(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectSprite3D:addEffect",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite3D_addEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectSprite3D_getMesh(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectSprite3D_getMesh'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite3D_getMesh'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::Mesh *>& ret = cobj->getMesh();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectSprite3D:getMesh",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite3D_getMesh'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectSprite3D_getMeshNum(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectSprite3D_getMeshNum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite3D_getMeshNum'", nullptr);
            return 0;
        }
        int ret = cobj->getMeshNum();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectSprite3D:getMeshNum",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite3D_getMeshNum'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectSprite3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EffectSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.EffectSprite3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite3D_create'", nullptr);
            return 0;
        }
        cocos2d::EffectSprite3D* ret = cocos2d::EffectSprite3D::create(arg0);
        object_to_luaval<cocos2d::EffectSprite3D>(tolua_S, "cc.EffectSprite3D",(cocos2d::EffectSprite3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EffectSprite3D:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EffectSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.EffectSprite3D:createFromObjFileAndTexture");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.EffectSprite3D:createFromObjFileAndTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture'", nullptr);
            return 0;
        }
        cocos2d::EffectSprite3D* ret = cocos2d::EffectSprite3D::createFromObjFileAndTexture(arg0, arg1);
        object_to_luaval<cocos2d::EffectSprite3D>(tolua_S, "cc.EffectSprite3D",(cocos2d::EffectSprite3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EffectSprite3D:createFromObjFileAndTexture",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_EffectSprite3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EffectSprite3D)");
    return 0;
}

int lua_register_cocos2dx_custom_EffectSprite3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EffectSprite3D");
    tolua_cclass(tolua_S,"EffectSprite3D","cc.EffectSprite3D","cc.Sprite3D",nullptr);

    tolua_beginmodule(tolua_S,"EffectSprite3D");
        tolua_function(tolua_S,"setEffect3D",lua_cocos2dx_custom_EffectSprite3D_setEffect3D);
        tolua_function(tolua_S,"addEffect",lua_cocos2dx_custom_EffectSprite3D_addEffect);
        tolua_function(tolua_S,"getMesh",lua_cocos2dx_custom_EffectSprite3D_getMesh);
        tolua_function(tolua_S,"getMeshNum",lua_cocos2dx_custom_EffectSprite3D_getMeshNum);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_EffectSprite3D_create);
        tolua_function(tolua_S,"createFromObjFileAndTexture", lua_cocos2dx_custom_EffectSprite3D_createFromObjFileAndTexture);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EffectSprite3D).name();
    g_luaType[typeName] = "cc.EffectSprite3D";
    g_typeCast["EffectSprite3D"] = "cc.EffectSprite3D";
    return 1;
}

int lua_cocos2dx_custom_DrawNode3D_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_getBlendFunc'", nullptr);
            return 0;
        }
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.DrawNode3D:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:setBlendFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_drawLine(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_drawLine'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Color4F arg2;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.DrawNode3D:drawLine");

        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.DrawNode3D:drawLine");

        ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.DrawNode3D:drawLine");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_drawLine'", nullptr);
            return 0;
        }
        cobj->drawLine(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:drawLine",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_drawLine'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_clear(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_onDraw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_onDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Mat4 arg0;
        unsigned int arg1;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.DrawNode3D:onDraw");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.DrawNode3D:onDraw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_onDraw'", nullptr);
            return 0;
        }
        cobj->onDraw(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:onDraw",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_onDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_drawCube(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::DrawNode3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_DrawNode3D_drawCube'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec3* arg0;
        cocos2d::Color4F arg1;

        ok &= luaval_to_object<cocos2d::Vec3>(tolua_S, 2, "cc.Vec3",&arg0, "cc.DrawNode3D:drawCube");

        ok &=luaval_to_color4f(tolua_S, 3, &arg1, "cc.DrawNode3D:drawCube");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_drawCube'", nullptr);
            return 0;
        }
        cobj->drawCube(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:drawCube",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_drawCube'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.DrawNode3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_create'", nullptr);
            return 0;
        }
        cocos2d::DrawNode3D* ret = cocos2d::DrawNode3D::create();
        object_to_luaval<cocos2d::DrawNode3D>(tolua_S, "cc.DrawNode3D",(cocos2d::DrawNode3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.DrawNode3D:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_DrawNode3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::DrawNode3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_DrawNode3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::DrawNode3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.DrawNode3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.DrawNode3D:DrawNode3D",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_DrawNode3D_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_DrawNode3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (DrawNode3D)");
    return 0;
}

int lua_register_cocos2dx_custom_DrawNode3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.DrawNode3D");
    tolua_cclass(tolua_S,"DrawNode3D","cc.DrawNode3D","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"DrawNode3D");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_DrawNode3D_constructor);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_custom_DrawNode3D_getBlendFunc);
        tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_custom_DrawNode3D_setBlendFunc);
        tolua_function(tolua_S,"drawLine",lua_cocos2dx_custom_DrawNode3D_drawLine);
        tolua_function(tolua_S,"clear",lua_cocos2dx_custom_DrawNode3D_clear);
        tolua_function(tolua_S,"onDraw",lua_cocos2dx_custom_DrawNode3D_onDraw);
        tolua_function(tolua_S,"init",lua_cocos2dx_custom_DrawNode3D_init);
        tolua_function(tolua_S,"drawCube",lua_cocos2dx_custom_DrawNode3D_drawCube);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_DrawNode3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::DrawNode3D).name();
    g_luaType[typeName] = "cc.DrawNode3D";
    g_typeCast["DrawNode3D"] = "cc.DrawNode3D";
    return 1;
}

int lua_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar'", nullptr);
            return 0;
        }
        double ret = cobj->getStartSizeVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartSizeVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartColor'", nullptr);
            return 0;
        }
        const cocos2d::Color4F& ret = cobj->getStartColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getPositionType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getPositionType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getPositionType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getPositionType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getPositionType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getPositionType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setPosVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setPosVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setPosVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setPosVar'", nullptr);
            return 0;
        }
        cobj->setPosVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setPosVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setPosVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndSpin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSpin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSpin'", nullptr);
            return 0;
        }
        double ret = cobj->getEndSpin();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndSpin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSpin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setRotatePerSecondVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar'", nullptr);
            return 0;
        }
        cobj->setRotatePerSecondVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setRotatePerSecondVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar'", nullptr);
            return 0;
        }
        double ret = cobj->getStartSpinVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartSpinVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar'", nullptr);
            return 0;
        }
        double ret = cobj->getRadialAccelVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getRadialAccelVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar'", nullptr);
            return 0;
        }
        double ret = cobj->getEndSizeVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndSizeVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setRotation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setRotation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotation'", nullptr);
            return 0;
        }
        cobj->setRotation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setRotation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setTangentialAccel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel'", nullptr);
            return 0;
        }
        cobj->setTangentialAccel(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setTangentialAccel",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setScaleY(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScaleY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setScaleY");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScaleY'", nullptr);
            return 0;
        }
        cobj->setScaleY(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setScaleY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScaleY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setScaleX(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScaleX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setScaleX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScaleX'", nullptr);
            return 0;
        }
        cobj->setScaleX(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setScaleX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScaleX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccel'", nullptr);
            return 0;
        }
        double ret = cobj->getRadialAccel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getRadialAccel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setStartRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartRadius'", nullptr);
            return 0;
        }
        cobj->setStartRadius(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setRotatePerSecond");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond'", nullptr);
            return 0;
        }
        cobj->setRotatePerSecond(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setRotatePerSecond",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEndSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSize'", nullptr);
            return 0;
        }
        cobj->setEndSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getGravity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getGravity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getGravity'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getGravity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getGravity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getGravity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel'", nullptr);
            return 0;
        }
        double ret = cobj->getTangentialAccel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getTangentialAccel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEndRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndRadius'", nullptr);
            return 0;
        }
        cobj->setEndRadius(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSpeed'", nullptr);
            return 0;
        }
        double ret = cobj->getSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAngle'", nullptr);
            return 0;
        }
        double ret = cobj->getAngle();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getAngle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAngle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setEndColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndColor'", nullptr);
            return 0;
        }
        cobj->setEndColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartSpin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSpin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setStartSpin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSpin'", nullptr);
            return 0;
        }
        cobj->setStartSpin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartSpin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSpin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setDuration'", nullptr);
            return 0;
        }
        cobj->setDuration(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setDuration",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.BillboardParticleSystem:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getPosVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getPosVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getPosVar'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getPosVar();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getPosVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getPosVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive'", nullptr);
            return 0;
        }
        bool ret = cobj->isBlendAdditive();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:isBlendAdditive",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getSpeedVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSpeedVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSpeedVar'", nullptr);
            return 0;
        }
        double ret = cobj->getSpeedVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getSpeedVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSpeedVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setPositionType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setPositionType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BillboardParticleSystem::PositionType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillboardParticleSystem:setPositionType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setPositionType'", nullptr);
            return 0;
        }
        cobj->setPositionType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setPositionType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setPositionType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_stopSystem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_stopSystem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_stopSystem'", nullptr);
            return 0;
        }
        cobj->stopSystem();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:stopSystem",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_stopSystem'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getSourcePosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSourcePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSourcePosition'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getSourcePosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getSourcePosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getSourcePosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setLifeVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setLifeVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setLifeVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setLifeVar'", nullptr);
            return 0;
        }
        cobj->setLifeVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setLifeVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setLifeVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillboardParticleSystem:setTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTotalParticles'", nullptr);
            return 0;
        }
        cobj->setTotalParticles(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setTotalParticles",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTotalParticles'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndColorVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setEndColorVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndColorVar'", nullptr);
            return 0;
        }
        cobj->setEndColorVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndColorVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndColorVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex'", nullptr);
            return 0;
        }
        int ret = cobj->getAtlasIndex();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getAtlasIndex",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSize'", nullptr);
            return 0;
        }
        double ret = cobj->getStartSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Texture2D* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.BillboardParticleSystem:setTextureWithRect");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.BillboardParticleSystem:setTextureWithRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect'", nullptr);
            return 0;
        }
        cobj->setTextureWithRect(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setTextureWithRect",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setStartSpinVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar'", nullptr);
            return 0;
        }
        cobj->setStartSpinVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartSpinVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_resetSystem(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_resetSystem'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_resetSystem'", nullptr);
            return 0;
        }
        cobj->resetSystem();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:resetSystem",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_resetSystem'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillboardParticleSystem:setAtlasIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex'", nullptr);
            return 0;
        }
        cobj->setAtlasIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setAtlasIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setTangentialAccelVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar'", nullptr);
            return 0;
        }
        cobj->setTangentialAccelVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setTangentialAccelVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getDuration'", nullptr);
            return 0;
        }
        double ret = cobj->getDuration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getDuration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getEndRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setDepthTestEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled'", nullptr);
            return 0;
        }
        cobj->setDepthTestEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setDepthTestEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setRadialAccelVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar'", nullptr);
            return 0;
        }
        cobj->setRadialAccelVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setRadialAccelVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setStartSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSize'", nullptr);
            return 0;
        }
        cobj->setStartSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setSpeed");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSpeed'", nullptr);
            return 0;
        }
        cobj->setSpeed(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartSpin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSpin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSpin'", nullptr);
            return 0;
        }
        double ret = cobj->getStartSpin();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartSpin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartSpin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond'", nullptr);
            return 0;
        }
        double ret = cobj->getRotatePerSecond();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getRotatePerSecond",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEmitterMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEmitterMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BillboardParticleSystem::Mode arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.BillboardParticleSystem:setEmitterMode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEmitterMode'", nullptr);
            return 0;
        }
        cobj->setEmitterMode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEmitterMode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEmitterMode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEndRadiusVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar'", nullptr);
            return 0;
        }
        cobj->setEndRadiusVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndRadiusVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB'", nullptr);
            return 0;
        }
        bool ret = cobj->isOpacityModifyRGB();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:isOpacityModifyRGB",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setSourcePosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSourcePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setSourcePosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSourcePosition'", nullptr);
            return 0;
        }
        cobj->setSourcePosition(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setSourcePosition",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSourcePosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar'", nullptr);
            return 0;
        }
        double ret = cobj->getEndSpinVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndSpinVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setBlendAdditive");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive'", nullptr);
            return 0;
        }
        cobj->setBlendAdditive(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setBlendAdditive",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setLife(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setLife'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setLife");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setLife'", nullptr);
            return 0;
        }
        cobj->setLife(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setLife",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setLife'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setAngleVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAngleVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setAngleVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAngleVar'", nullptr);
            return 0;
        }
        cobj->setAngleVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setAngleVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAngleVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setRotationIsDir");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir'", nullptr);
            return 0;
        }
        cobj->setRotationIsDir(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setRotationIsDir",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEndSizeVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar'", nullptr);
            return 0;
        }
        cobj->setEndSizeVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndSizeVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setAngle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAngle'", nullptr);
            return 0;
        }
        cobj->setAngle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setAngle",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setAngle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar'", nullptr);
            return 0;
        }
        double ret = cobj->getTangentialAccelVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getTangentialAccelVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEmitterMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEmitterMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEmitterMode'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getEmitterMode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEmitterMode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEmitterMode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEndSpinVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar'", nullptr);
            return 0;
        }
        cobj->setEndSpinVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndSpinVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getAngleVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAngleVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAngleVar'", nullptr);
            return 0;
        }
        double ret = cobj->getAngleVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getAngleVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getAngleVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setStartColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartColor'", nullptr);
            return 0;
        }
        cobj->setStartColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar'", nullptr);
            return 0;
        }
        double ret = cobj->getRotatePerSecondVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getRotatePerSecondVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSize'", nullptr);
            return 0;
        }
        double ret = cobj->getEndSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getLife(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getLife'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getLife'", nullptr);
            return 0;
        }
        double ret = cobj->getLife();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getLife",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getLife'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setSpeedVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSpeedVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setSpeedVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSpeedVar'", nullptr);
            return 0;
        }
        cobj->setSpeedVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setSpeedVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setSpeedVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setGravity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setGravity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setGravity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setGravity'", nullptr);
            return 0;
        }
        cobj->setGravity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setGravity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setGravity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEmissionRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEmissionRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEmissionRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEmissionRate'", nullptr);
            return 0;
        }
        cobj->setEmissionRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEmissionRate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEmissionRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndColorVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndColorVar'", nullptr);
            return 0;
        }
        const cocos2d::Color4F& ret = cobj->getEndColorVar();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndColorVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndColorVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir'", nullptr);
            return 0;
        }
        bool ret = cobj->getRotationIsDir();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getRotationIsDir",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScale'", nullptr);
            return 0;
        }
        cobj->setScale(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEmissionRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEmissionRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEmissionRate'", nullptr);
            return 0;
        }
        double ret = cobj->getEmissionRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEmissionRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEmissionRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndColor'", nullptr);
            return 0;
        }
        const cocos2d::Color4F& ret = cobj->getEndColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getLifeVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getLifeVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getLifeVar'", nullptr);
            return 0;
        }
        double ret = cobj->getLifeVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getLifeVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getLifeVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setCamera(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setCamera'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Camera* arg0;

        ok &= luaval_to_object<cocos2d::Camera>(tolua_S, 2, "cc.Camera",&arg0, "cc.BillboardParticleSystem:setCamera");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setCamera'", nullptr);
            return 0;
        }
        cobj->setCamera(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setCamera",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setCamera'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setStartSizeVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar'", nullptr);
            return 0;
        }
        cobj->setStartSizeVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartSizeVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setOpacityModifyRGB");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB'", nullptr);
            return 0;
        }
        cobj->setOpacityModifyRGB(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setOpacityModifyRGB",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getStartRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getParticleCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getParticleCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getParticleCount'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getParticleCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getParticleCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getParticleCount'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar'", nullptr);
            return 0;
        }
        double ret = cobj->getStartRadiusVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartRadiusVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartColorVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:setStartColorVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartColorVar'", nullptr);
            return 0;
        }
        cobj->setStartColorVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartColorVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartColorVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setEndSpin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSpin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setEndSpin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSpin'", nullptr);
            return 0;
        }
        cobj->setEndSpin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setEndSpin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setEndSpin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setRadialAccel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccel'", nullptr);
            return 0;
        }
        cobj->setRadialAccel(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setRadialAccel",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:setStartRadiusVar");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar'", nullptr);
            return 0;
        }
        cobj->setStartRadiusVar(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:setStartRadiusVar",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar'", nullptr);
            return 0;
        }
        double ret = cobj->getEndRadiusVar();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getEndRadiusVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_getStartColorVar(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::BillboardParticleSystem*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartColorVar'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartColorVar'", nullptr);
            return 0;
        }
        const cocos2d::Color4F& ret = cobj->getStartColorVar();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:getStartColorVar",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_getStartColorVar'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.BillboardParticleSystem",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::ValueMap arg0;
            ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.BillboardParticleSystem:create");
            if (!ok) { break; }
            cocos2d::BillboardParticleSystem* ret = cocos2d::BillboardParticleSystem::create(arg0);
            object_to_luaval<cocos2d::BillboardParticleSystem>(tolua_S, "cc.BillboardParticleSystem",(cocos2d::BillboardParticleSystem*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.BillboardParticleSystem:create");
            if (!ok) { break; }
            cocos2d::BillboardParticleSystem* ret = cocos2d::BillboardParticleSystem::create(arg0);
            object_to_luaval<cocos2d::BillboardParticleSystem>(tolua_S, "cc.BillboardParticleSystem",(cocos2d::BillboardParticleSystem*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.BillboardParticleSystem:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_BillboardParticleSystem_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::BillboardParticleSystem* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_BillboardParticleSystem_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::BillboardParticleSystem();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.BillboardParticleSystem");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.BillboardParticleSystem:BillboardParticleSystem",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_BillboardParticleSystem_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_BillboardParticleSystem_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BillboardParticleSystem)");
    return 0;
}

int lua_register_cocos2dx_custom_BillboardParticleSystem(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.BillboardParticleSystem");
    tolua_cclass(tolua_S,"BillboardParticleSystem","cc.BillboardParticleSystem","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"BillboardParticleSystem");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_BillboardParticleSystem_constructor);
        tolua_function(tolua_S,"getStartSizeVar",lua_cocos2dx_custom_BillboardParticleSystem_getStartSizeVar);
        tolua_function(tolua_S,"getStartColor",lua_cocos2dx_custom_BillboardParticleSystem_getStartColor);
        tolua_function(tolua_S,"getPositionType",lua_cocos2dx_custom_BillboardParticleSystem_getPositionType);
        tolua_function(tolua_S,"setPosVar",lua_cocos2dx_custom_BillboardParticleSystem_setPosVar);
        tolua_function(tolua_S,"getEndSpin",lua_cocos2dx_custom_BillboardParticleSystem_getEndSpin);
        tolua_function(tolua_S,"setRotatePerSecondVar",lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecondVar);
        tolua_function(tolua_S,"getStartSpinVar",lua_cocos2dx_custom_BillboardParticleSystem_getStartSpinVar);
        tolua_function(tolua_S,"getRadialAccelVar",lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccelVar);
        tolua_function(tolua_S,"getEndSizeVar",lua_cocos2dx_custom_BillboardParticleSystem_getEndSizeVar);
        tolua_function(tolua_S,"setRotation",lua_cocos2dx_custom_BillboardParticleSystem_setRotation);
        tolua_function(tolua_S,"setTangentialAccel",lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccel);
        tolua_function(tolua_S,"setScaleY",lua_cocos2dx_custom_BillboardParticleSystem_setScaleY);
        tolua_function(tolua_S,"setScaleX",lua_cocos2dx_custom_BillboardParticleSystem_setScaleX);
        tolua_function(tolua_S,"getRadialAccel",lua_cocos2dx_custom_BillboardParticleSystem_getRadialAccel);
        tolua_function(tolua_S,"setStartRadius",lua_cocos2dx_custom_BillboardParticleSystem_setStartRadius);
        tolua_function(tolua_S,"setRotatePerSecond",lua_cocos2dx_custom_BillboardParticleSystem_setRotatePerSecond);
        tolua_function(tolua_S,"setEndSize",lua_cocos2dx_custom_BillboardParticleSystem_setEndSize);
        tolua_function(tolua_S,"getGravity",lua_cocos2dx_custom_BillboardParticleSystem_getGravity);
        tolua_function(tolua_S,"getTangentialAccel",lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccel);
        tolua_function(tolua_S,"setEndRadius",lua_cocos2dx_custom_BillboardParticleSystem_setEndRadius);
        tolua_function(tolua_S,"getSpeed",lua_cocos2dx_custom_BillboardParticleSystem_getSpeed);
        tolua_function(tolua_S,"getAngle",lua_cocos2dx_custom_BillboardParticleSystem_getAngle);
        tolua_function(tolua_S,"setEndColor",lua_cocos2dx_custom_BillboardParticleSystem_setEndColor);
        tolua_function(tolua_S,"setStartSpin",lua_cocos2dx_custom_BillboardParticleSystem_setStartSpin);
        tolua_function(tolua_S,"setDuration",lua_cocos2dx_custom_BillboardParticleSystem_setDuration);
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_custom_BillboardParticleSystem_setTexture);
        tolua_function(tolua_S,"getPosVar",lua_cocos2dx_custom_BillboardParticleSystem_getPosVar);
        tolua_function(tolua_S,"isBlendAdditive",lua_cocos2dx_custom_BillboardParticleSystem_isBlendAdditive);
        tolua_function(tolua_S,"getSpeedVar",lua_cocos2dx_custom_BillboardParticleSystem_getSpeedVar);
        tolua_function(tolua_S,"setPositionType",lua_cocos2dx_custom_BillboardParticleSystem_setPositionType);
        tolua_function(tolua_S,"stopSystem",lua_cocos2dx_custom_BillboardParticleSystem_stopSystem);
        tolua_function(tolua_S,"getSourcePosition",lua_cocos2dx_custom_BillboardParticleSystem_getSourcePosition);
        tolua_function(tolua_S,"setLifeVar",lua_cocos2dx_custom_BillboardParticleSystem_setLifeVar);
        tolua_function(tolua_S,"setTotalParticles",lua_cocos2dx_custom_BillboardParticleSystem_setTotalParticles);
        tolua_function(tolua_S,"setEndColorVar",lua_cocos2dx_custom_BillboardParticleSystem_setEndColorVar);
        tolua_function(tolua_S,"getAtlasIndex",lua_cocos2dx_custom_BillboardParticleSystem_getAtlasIndex);
        tolua_function(tolua_S,"getStartSize",lua_cocos2dx_custom_BillboardParticleSystem_getStartSize);
        tolua_function(tolua_S,"setTextureWithRect",lua_cocos2dx_custom_BillboardParticleSystem_setTextureWithRect);
        tolua_function(tolua_S,"setStartSpinVar",lua_cocos2dx_custom_BillboardParticleSystem_setStartSpinVar);
        tolua_function(tolua_S,"resetSystem",lua_cocos2dx_custom_BillboardParticleSystem_resetSystem);
        tolua_function(tolua_S,"setAtlasIndex",lua_cocos2dx_custom_BillboardParticleSystem_setAtlasIndex);
        tolua_function(tolua_S,"setTangentialAccelVar",lua_cocos2dx_custom_BillboardParticleSystem_setTangentialAccelVar);
        tolua_function(tolua_S,"getDuration",lua_cocos2dx_custom_BillboardParticleSystem_getDuration);
        tolua_function(tolua_S,"getEndRadius",lua_cocos2dx_custom_BillboardParticleSystem_getEndRadius);
        tolua_function(tolua_S,"setDepthTestEnabled",lua_cocos2dx_custom_BillboardParticleSystem_setDepthTestEnabled);
        tolua_function(tolua_S,"setRadialAccelVar",lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccelVar);
        tolua_function(tolua_S,"setStartSize",lua_cocos2dx_custom_BillboardParticleSystem_setStartSize);
        tolua_function(tolua_S,"setSpeed",lua_cocos2dx_custom_BillboardParticleSystem_setSpeed);
        tolua_function(tolua_S,"getStartSpin",lua_cocos2dx_custom_BillboardParticleSystem_getStartSpin);
        tolua_function(tolua_S,"getRotatePerSecond",lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecond);
        tolua_function(tolua_S,"setEmitterMode",lua_cocos2dx_custom_BillboardParticleSystem_setEmitterMode);
        tolua_function(tolua_S,"setEndRadiusVar",lua_cocos2dx_custom_BillboardParticleSystem_setEndRadiusVar);
        tolua_function(tolua_S,"isOpacityModifyRGB",lua_cocos2dx_custom_BillboardParticleSystem_isOpacityModifyRGB);
        tolua_function(tolua_S,"setSourcePosition",lua_cocos2dx_custom_BillboardParticleSystem_setSourcePosition);
        tolua_function(tolua_S,"getEndSpinVar",lua_cocos2dx_custom_BillboardParticleSystem_getEndSpinVar);
        tolua_function(tolua_S,"setBlendAdditive",lua_cocos2dx_custom_BillboardParticleSystem_setBlendAdditive);
        tolua_function(tolua_S,"setLife",lua_cocos2dx_custom_BillboardParticleSystem_setLife);
        tolua_function(tolua_S,"setAngleVar",lua_cocos2dx_custom_BillboardParticleSystem_setAngleVar);
        tolua_function(tolua_S,"setRotationIsDir",lua_cocos2dx_custom_BillboardParticleSystem_setRotationIsDir);
        tolua_function(tolua_S,"setEndSizeVar",lua_cocos2dx_custom_BillboardParticleSystem_setEndSizeVar);
        tolua_function(tolua_S,"setAngle",lua_cocos2dx_custom_BillboardParticleSystem_setAngle);
        tolua_function(tolua_S,"getTangentialAccelVar",lua_cocos2dx_custom_BillboardParticleSystem_getTangentialAccelVar);
        tolua_function(tolua_S,"getEmitterMode",lua_cocos2dx_custom_BillboardParticleSystem_getEmitterMode);
        tolua_function(tolua_S,"setEndSpinVar",lua_cocos2dx_custom_BillboardParticleSystem_setEndSpinVar);
        tolua_function(tolua_S,"getAngleVar",lua_cocos2dx_custom_BillboardParticleSystem_getAngleVar);
        tolua_function(tolua_S,"setStartColor",lua_cocos2dx_custom_BillboardParticleSystem_setStartColor);
        tolua_function(tolua_S,"getRotatePerSecondVar",lua_cocos2dx_custom_BillboardParticleSystem_getRotatePerSecondVar);
        tolua_function(tolua_S,"getEndSize",lua_cocos2dx_custom_BillboardParticleSystem_getEndSize);
        tolua_function(tolua_S,"getLife",lua_cocos2dx_custom_BillboardParticleSystem_getLife);
        tolua_function(tolua_S,"setSpeedVar",lua_cocos2dx_custom_BillboardParticleSystem_setSpeedVar);
        tolua_function(tolua_S,"setGravity",lua_cocos2dx_custom_BillboardParticleSystem_setGravity);
        tolua_function(tolua_S,"setEmissionRate",lua_cocos2dx_custom_BillboardParticleSystem_setEmissionRate);
        tolua_function(tolua_S,"getEndColorVar",lua_cocos2dx_custom_BillboardParticleSystem_getEndColorVar);
        tolua_function(tolua_S,"getRotationIsDir",lua_cocos2dx_custom_BillboardParticleSystem_getRotationIsDir);
        tolua_function(tolua_S,"setScale",lua_cocos2dx_custom_BillboardParticleSystem_setScale);
        tolua_function(tolua_S,"getEmissionRate",lua_cocos2dx_custom_BillboardParticleSystem_getEmissionRate);
        tolua_function(tolua_S,"getEndColor",lua_cocos2dx_custom_BillboardParticleSystem_getEndColor);
        tolua_function(tolua_S,"getLifeVar",lua_cocos2dx_custom_BillboardParticleSystem_getLifeVar);
        tolua_function(tolua_S,"setCamera",lua_cocos2dx_custom_BillboardParticleSystem_setCamera);
        tolua_function(tolua_S,"setStartSizeVar",lua_cocos2dx_custom_BillboardParticleSystem_setStartSizeVar);
        tolua_function(tolua_S,"setOpacityModifyRGB",lua_cocos2dx_custom_BillboardParticleSystem_setOpacityModifyRGB);
        tolua_function(tolua_S,"getStartRadius",lua_cocos2dx_custom_BillboardParticleSystem_getStartRadius);
        tolua_function(tolua_S,"getParticleCount",lua_cocos2dx_custom_BillboardParticleSystem_getParticleCount);
        tolua_function(tolua_S,"getStartRadiusVar",lua_cocos2dx_custom_BillboardParticleSystem_getStartRadiusVar);
        tolua_function(tolua_S,"setStartColorVar",lua_cocos2dx_custom_BillboardParticleSystem_setStartColorVar);
        tolua_function(tolua_S,"setEndSpin",lua_cocos2dx_custom_BillboardParticleSystem_setEndSpin);
        tolua_function(tolua_S,"setRadialAccel",lua_cocos2dx_custom_BillboardParticleSystem_setRadialAccel);
        tolua_function(tolua_S,"setStartRadiusVar",lua_cocos2dx_custom_BillboardParticleSystem_setStartRadiusVar);
        tolua_function(tolua_S,"getEndRadiusVar",lua_cocos2dx_custom_BillboardParticleSystem_getEndRadiusVar);
        tolua_function(tolua_S,"getStartColorVar",lua_cocos2dx_custom_BillboardParticleSystem_getStartColorVar);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_BillboardParticleSystem_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::BillboardParticleSystem).name();
    g_luaType[typeName] = "cc.BillboardParticleSystem";
    g_typeCast["BillboardParticleSystem"] = "cc.BillboardParticleSystem";
    return 1;
}

int lua_cocos2dx_custom_JumpBy3D_initWithDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpBy3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.JumpBy3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::JumpBy3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_JumpBy3D_initWithDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        double arg0;
        cocos2d::Vec3 arg1;
        double arg2;
        int arg3;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpBy3D:initWithDuration");

        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.JumpBy3D:initWithDuration");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpBy3D:initWithDuration");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpBy3D:initWithDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_JumpBy3D_initWithDuration'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithDuration(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpBy3D:initWithDuration",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_JumpBy3D_initWithDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_JumpBy3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.JumpBy3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec3 arg1;
        double arg2;
        int arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpBy3D:create");
        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.JumpBy3D:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpBy3D:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpBy3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_JumpBy3D_create'", nullptr);
            return 0;
        }
        cocos2d::JumpBy3D* ret = cocos2d::JumpBy3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::JumpBy3D>(tolua_S, "cc.JumpBy3D",(cocos2d::JumpBy3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.JumpBy3D:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_JumpBy3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_JumpBy3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpBy3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_JumpBy3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::JumpBy3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.JumpBy3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpBy3D:JumpBy3D",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_JumpBy3D_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_JumpBy3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (JumpBy3D)");
    return 0;
}

int lua_register_cocos2dx_custom_JumpBy3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.JumpBy3D");
    tolua_cclass(tolua_S,"JumpBy3D","cc.JumpBy3D","cc.ActionInterval",nullptr);

    tolua_beginmodule(tolua_S,"JumpBy3D");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_JumpBy3D_constructor);
        tolua_function(tolua_S,"initWithDuration",lua_cocos2dx_custom_JumpBy3D_initWithDuration);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_JumpBy3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::JumpBy3D).name();
    g_luaType[typeName] = "cc.JumpBy3D";
    g_typeCast["JumpBy3D"] = "cc.JumpBy3D";
    return 1;
}

int lua_cocos2dx_custom_JumpTo3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.JumpTo3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        double arg0;
        cocos2d::Vec3 arg1;
        double arg2;
        int arg3;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.JumpTo3D:create");
        ok &= luaval_to_vec3(tolua_S, 3, &arg1, "cc.JumpTo3D:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.JumpTo3D:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.JumpTo3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_JumpTo3D_create'", nullptr);
            return 0;
        }
        cocos2d::JumpTo3D* ret = cocos2d::JumpTo3D::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::JumpTo3D>(tolua_S, "cc.JumpTo3D",(cocos2d::JumpTo3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.JumpTo3D:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_JumpTo3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_JumpTo3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::JumpTo3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_JumpTo3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::JumpTo3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.JumpTo3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.JumpTo3D:JumpTo3D",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_JumpTo3D_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_JumpTo3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (JumpTo3D)");
    return 0;
}

int lua_register_cocos2dx_custom_JumpTo3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.JumpTo3D");
    tolua_cclass(tolua_S,"JumpTo3D","cc.JumpTo3D","cc.JumpBy3D",nullptr);

    tolua_beginmodule(tolua_S,"JumpTo3D");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_JumpTo3D_constructor);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_JumpTo3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::JumpTo3D).name();
    g_luaType[typeName] = "cc.JumpTo3D";
    g_typeCast["JumpTo3D"] = "cc.JumpTo3D";
    return 1;
}

int lua_cocos2dx_custom_Water_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Water",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 7)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::Size arg3;
        double arg4;
        double arg5;
        double arg6;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.Water:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.Water:create");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "cc.Water:create");
        ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.Water:create");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.Water:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.Water:create");
        ok &= luaval_to_number(tolua_S, 8,&arg6, "cc.Water:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Water_create'", nullptr);
            return 0;
        }
        cocos2d::Water* ret = cocos2d::Water::create(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        object_to_luaval<cocos2d::Water>(tolua_S, "cc.Water",(cocos2d::Water*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Water:create",argc, 7);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Water_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_Water_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Water)");
    return 0;
}

int lua_register_cocos2dx_custom_Water(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Water");
    tolua_cclass(tolua_S,"Water","cc.Water","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"Water");
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_Water_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Water).name();
    g_luaType[typeName] = "cc.Water";
    g_typeCast["Water"] = "cc.Water";
    return 1;
}

int lua_cocos2dx_custom_Effect_setTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect_setTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::EffectSprite* arg0;

        ok &= luaval_to_object<cocos2d::EffectSprite>(tolua_S, 2, "cc.EffectSprite",&arg0, "cc.Effect:setTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect_setTarget'", nullptr);
            return 0;
        }
        cobj->setTarget(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect:setTarget",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect_setTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_Effect_updateUniforms(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect_updateUniforms'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect_updateUniforms'", nullptr);
            return 0;
        }
        cobj->updateUniforms();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect:updateUniforms",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect_updateUniforms'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_Effect_getGLProgramState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Effect* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Effect",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Effect*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Effect_getGLProgramState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Effect_getGLProgramState'", nullptr);
            return 0;
        }
        cocos2d::GLProgramState* ret = cobj->getGLProgramState();
        object_to_luaval<cocos2d::GLProgramState>(tolua_S, "cc.GLProgramState",(cocos2d::GLProgramState*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Effect:getGLProgramState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Effect_getGLProgramState'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_custom_Effect_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Effect)");
    return 0;
}

int lua_register_cocos2dx_custom_Effect(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Effect");
    tolua_cclass(tolua_S,"Effect","cc.Effect","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"Effect");
        tolua_function(tolua_S,"setTarget",lua_cocos2dx_custom_Effect_setTarget);
        tolua_function(tolua_S,"updateUniforms",lua_cocos2dx_custom_Effect_updateUniforms);
        tolua_function(tolua_S,"getGLProgramState",lua_cocos2dx_custom_Effect_getGLProgramState);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Effect).name();
    g_luaType[typeName] = "cc.Effect";
    g_typeCast["Effect"] = "cc.Effect";
    return 1;
}

int lua_cocos2dx_custom_EffectNormalMapped_setKBump(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectNormalMapped* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectNormalMapped",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectNormalMapped*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectNormalMapped_setKBump'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.EffectNormalMapped:setKBump");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectNormalMapped_setKBump'", nullptr);
            return 0;
        }
        cobj->setKBump(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectNormalMapped:setKBump",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectNormalMapped_setKBump'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectNormalMapped_setPointLight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectNormalMapped* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectNormalMapped",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectNormalMapped*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectNormalMapped_setPointLight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::PointLight* arg0;

        ok &= luaval_to_object<cocos2d::PointLight>(tolua_S, 2, "cc.PointLight",&arg0, "cc.EffectNormalMapped:setPointLight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectNormalMapped_setPointLight'", nullptr);
            return 0;
        }
        cobj->setPointLight(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectNormalMapped:setPointLight",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectNormalMapped_setPointLight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectNormalMapped_getKBump(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectNormalMapped* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectNormalMapped",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectNormalMapped*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectNormalMapped_getKBump'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectNormalMapped_getKBump'", nullptr);
            return 0;
        }
        double ret = cobj->getKBump();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectNormalMapped:getKBump",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectNormalMapped_getKBump'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectNormalMapped_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EffectNormalMapped",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.EffectNormalMapped:create");
            if (!ok) { break; }
            cocos2d::EffectNormalMapped* ret = cocos2d::EffectNormalMapped::create(arg0);
            object_to_luaval<cocos2d::EffectNormalMapped>(tolua_S, "cc.EffectNormalMapped",(cocos2d::EffectNormalMapped*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::EffectNormalMapped* ret = cocos2d::EffectNormalMapped::create();
            object_to_luaval<cocos2d::EffectNormalMapped>(tolua_S, "cc.EffectNormalMapped",(cocos2d::EffectNormalMapped*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.EffectNormalMapped:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectNormalMapped_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_EffectNormalMapped_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EffectNormalMapped)");
    return 0;
}

int lua_register_cocos2dx_custom_EffectNormalMapped(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EffectNormalMapped");
    tolua_cclass(tolua_S,"EffectNormalMapped","cc.EffectNormalMapped","cc.Effect",nullptr);

    tolua_beginmodule(tolua_S,"EffectNormalMapped");
        tolua_function(tolua_S,"setKBump",lua_cocos2dx_custom_EffectNormalMapped_setKBump);
        tolua_function(tolua_S,"setPointLight",lua_cocos2dx_custom_EffectNormalMapped_setPointLight);
        tolua_function(tolua_S,"getKBump",lua_cocos2dx_custom_EffectNormalMapped_getKBump);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_EffectNormalMapped_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EffectNormalMapped).name();
    g_luaType[typeName] = "cc.EffectNormalMapped";
    g_typeCast["EffectNormalMapped"] = "cc.EffectNormalMapped";
    return 1;
}

int lua_cocos2dx_custom_EffectSprite_setEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectSprite_setEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Effect* arg0;

        ok &= luaval_to_object<cocos2d::Effect>(tolua_S, 2, "cc.Effect",&arg0, "cc.EffectSprite:setEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite_setEffect'", nullptr);
            return 0;
        }
        cobj->setEffect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectSprite:setEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite_setEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectSprite_addEffect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EffectSprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EffectSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EffectSprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_EffectSprite_addEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Effect* arg0;
        ssize_t arg1;

        ok &= luaval_to_object<cocos2d::Effect>(tolua_S, 2, "cc.Effect",&arg0, "cc.EffectSprite:addEffect");

        ok &= luaval_to_ssize(tolua_S, 3, &arg1, "cc.EffectSprite:addEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite_addEffect'", nullptr);
            return 0;
        }
        cobj->addEffect(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EffectSprite:addEffect",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite_addEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_EffectSprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EffectSprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.EffectSprite:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_EffectSprite_create'", nullptr);
            return 0;
        }
        cocos2d::EffectSprite* ret = cocos2d::EffectSprite::create(arg0);
        object_to_luaval<cocos2d::EffectSprite>(tolua_S, "cc.EffectSprite",(cocos2d::EffectSprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EffectSprite:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_EffectSprite_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_EffectSprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EffectSprite)");
    return 0;
}

int lua_register_cocos2dx_custom_EffectSprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EffectSprite");
    tolua_cclass(tolua_S,"EffectSprite","cc.EffectSprite","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"EffectSprite");
        tolua_function(tolua_S,"setEffect",lua_cocos2dx_custom_EffectSprite_setEffect);
        tolua_function(tolua_S,"addEffect",lua_cocos2dx_custom_EffectSprite_addEffect);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_EffectSprite_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EffectSprite).name();
    g_luaType[typeName] = "cc.EffectSprite";
    g_typeCast["EffectSprite"] = "cc.EffectSprite";
    return 1;
}

int lua_cocos2dx_custom_Sequence3D_initWithActions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sequence3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sequence3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::Sequence3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_custom_Sequence3D_initWithActions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::Animate3D *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Sequence3D:initWithActions");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Sequence3D_initWithActions'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithActions(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sequence3D:initWithActions",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Sequence3D_initWithActions'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_custom_Sequence3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Sequence3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Vector<cocos2d::Animate3D *> arg0;
        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "cc.Sequence3D:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Sequence3D_create'", nullptr);
            return 0;
        }
        cocos2d::Sequence3D* ret = cocos2d::Sequence3D::create(arg0);
        object_to_luaval<cocos2d::Sequence3D>(tolua_S, "cc.Sequence3D",(cocos2d::Sequence3D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Sequence3D:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Sequence3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_custom_Sequence3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sequence3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_Sequence3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::Sequence3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.Sequence3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sequence3D:Sequence3D",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_Sequence3D_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_custom_Sequence3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Sequence3D)");
    return 0;
}

int lua_register_cocos2dx_custom_Sequence3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Sequence3D");
    tolua_cclass(tolua_S,"Sequence3D","cc.Sequence3D","cc.ActionInterval",nullptr);

    tolua_beginmodule(tolua_S,"Sequence3D");
        tolua_function(tolua_S,"new",lua_cocos2dx_custom_Sequence3D_constructor);
        tolua_function(tolua_S,"initWithActions",lua_cocos2dx_custom_Sequence3D_initWithActions);
        tolua_function(tolua_S,"create", lua_cocos2dx_custom_Sequence3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::Sequence3D).name();
    g_luaType[typeName] = "cc.Sequence3D";
    g_typeCast["Sequence3D"] = "cc.Sequence3D";
    return 1;
}

int lua_cocos2dx_custom_GreyShader_setGreyShader(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.GreyShader",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Sprite* arg0;
        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "cc.GreyShader:setGreyShader");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_custom_GreyShader_setGreyShader'", nullptr);
            return 0;
        }
        cocos2d::GreyShader::setGreyShader(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.GreyShader:setGreyShader",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_custom_GreyShader_setGreyShader'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_custom_GreyShader_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GreyShader)");
    return 0;
}

int lua_register_cocos2dx_custom_GreyShader(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.GreyShader");
    tolua_cclass(tolua_S,"GreyShader","cc.GreyShader","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"GreyShader");
        tolua_function(tolua_S,"setGreyShader", lua_cocos2dx_custom_GreyShader_setGreyShader);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::GreyShader).name();
    g_luaType[typeName] = "cc.GreyShader";
    g_typeCast["GreyShader"] = "cc.GreyShader";
    return 1;
}
TOLUA_API int register_all_cocos2dx_custom(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_custom_JumpBy3D(tolua_S);
	lua_register_cocos2dx_custom_JumpTo3D(tolua_S);
	lua_register_cocos2dx_custom_Effect3D(tolua_S);
	lua_register_cocos2dx_custom_EffectSprite(tolua_S);
	lua_register_cocos2dx_custom_Effect(tolua_S);
	lua_register_cocos2dx_custom_Water(tolua_S);
	lua_register_cocos2dx_custom_GreyShader(tolua_S);
	lua_register_cocos2dx_custom_EffectNormalMapped(tolua_S);
	lua_register_cocos2dx_custom_BillboardParticleSystem(tolua_S);
	lua_register_cocos2dx_custom_Effect3DOutline(tolua_S);
	lua_register_cocos2dx_custom_DrawNode3D(tolua_S);
	lua_register_cocos2dx_custom_ShadowSprite(tolua_S);
	lua_register_cocos2dx_custom_EffectSprite3D(tolua_S);
	lua_register_cocos2dx_custom_Sequence3D(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

