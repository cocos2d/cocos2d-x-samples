#include "jsb_cocos2dx_pluginx_auto.hpp"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "jsb_pluginx_basic_conversions.h"
using namespace pluginx;
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		T* cobj = new T();
		js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
		JS_AddObjectRoot(cx, &pp->obj);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return true;
	}

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;	
}
JSClass  *jsb_cocos2d_plugin_PluginProtocol_class;
JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

bool js_pluginx_protocols_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginProtocol_getPluginName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getPluginName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_PluginProtocol_getPluginName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginProtocol_getPluginVersion : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginVersion();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_PluginProtocol_getPluginVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginProtocol_getSDKVersion : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getSDKVersion();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_PluginProtocol_getSDKVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginProtocol* cobj = (cocos2d::plugin::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginProtocol_setDebugMode : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_PluginProtocol_setDebugMode : Error processing arguments");
		cobj->setDebugMode(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_PluginProtocol_setDebugMode : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}


void js_cocos2d_plugin_PluginProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::PluginProtocol *nobj = static_cast<cocos2d::plugin::PluginProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_PluginProtocol(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_PluginProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_PluginProtocol_class->name = "PluginProtocol";
	jsb_cocos2d_plugin_PluginProtocol_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_PluginProtocol_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_PluginProtocol_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_PluginProtocol_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_PluginProtocol_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_PluginProtocol_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_PluginProtocol_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_PluginProtocol_class->finalize = js_cocos2d_plugin_PluginProtocol_finalize;
	jsb_cocos2d_plugin_PluginProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getPluginName", js_pluginx_protocols_PluginProtocol_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginVersion", js_pluginx_protocols_PluginProtocol_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSDKVersion", js_pluginx_protocols_PluginProtocol_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", js_pluginx_protocols_PluginProtocol_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_PluginProtocol_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_plugin_PluginProtocol_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::PluginProtocol> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_PluginProtocol_class;
		p->proto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_PluginManager_class;
JSObject *jsb_cocos2d_plugin_PluginManager_prototype;

bool js_pluginx_protocols_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginManager* cobj = (cocos2d::plugin::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginManager_unloadPlugin : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_PluginManager_unloadPlugin : Error processing arguments");
		cobj->unloadPlugin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_PluginManager_unloadPlugin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::PluginManager* cobj = (cocos2d::plugin::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_PluginManager_loadPlugin : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_PluginManager_loadPlugin : Error processing arguments");
		cocos2d::plugin::PluginProtocol* ret = cobj->loadPlugin(arg0);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::plugin::PluginProtocol>(cx, (cocos2d::plugin::PluginProtocol*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_PluginManager_loadPlugin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::plugin::PluginManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_pluginx_protocols_PluginManager_end : wrong number of arguments");
	return false;
}

bool js_pluginx_protocols_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		cocos2d::plugin::PluginManager* ret = cocos2d::plugin::PluginManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::plugin::PluginManager>(cx, (cocos2d::plugin::PluginManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_pluginx_protocols_PluginManager_getInstance : wrong number of arguments");
	return false;
}



void js_cocos2d_plugin_PluginManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginManager)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::PluginManager *nobj = static_cast<cocos2d::plugin::PluginManager *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_PluginManager(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_PluginManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_PluginManager_class->name = "PluginManager";
	jsb_cocos2d_plugin_PluginManager_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_PluginManager_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_PluginManager_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_PluginManager_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_PluginManager_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_PluginManager_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_PluginManager_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_PluginManager_class->finalize = js_cocos2d_plugin_PluginManager_finalize;
	jsb_cocos2d_plugin_PluginManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("unloadPlugin", js_pluginx_protocols_PluginManager_unloadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadPlugin", js_pluginx_protocols_PluginManager_loadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_pluginx_protocols_PluginManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_pluginx_protocols_PluginManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_cocos2d_plugin_PluginManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_cocos2d_plugin_PluginManager_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::PluginManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_PluginManager_class;
		p->proto = jsb_cocos2d_plugin_PluginManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_ProtocolAnalytics_class;
JSObject *jsb_cocos2d_plugin_ProtocolAnalytics_prototype;

bool js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin : Error processing arguments");
		cobj->logTimedEventBegin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logError : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		const char* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logError : Error processing arguments");
		cobj->logError(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_logError : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException : Error processing arguments");
		cobj->setCaptureUncaughtException(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis : Invalid Native Object");
	if (argc == 1) {
		long arg0;
		ok &= jsval_to_long(cx, argv[0], (long *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis : Error processing arguments");
		cobj->setSessionContinueMillis(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_logEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logEvent : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logEvent : Error processing arguments");
		cobj->logEvent(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 2) {
		const char* arg0;
		cocos2d::plugin::LogEventParamMap* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		cocos2d::plugin::LogEventParamMap arg1_tmp;
		do {
			ok &= pluginx::jsval_to_LogEventParamMap(cx, argv[1], &arg1);
			if (ok) { arg1_tmp = *arg1; delete arg1; arg1 = &arg1_tmp; } else { arg1 = NULL; }
		} while(0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logEvent : Error processing arguments");
		cobj->logEvent(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_logEvent : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_startSession : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_startSession : Error processing arguments");
		cobj->startSession(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_startSession : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_stopSession : Invalid Native Object");
	if (argc == 0) {
		cobj->stopSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_stopSession : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAnalytics* cobj = (cocos2d::plugin::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd : Error processing arguments");
		cobj->logTimedEventEnd(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

void js_cocos2d_plugin_ProtocolAnalytics_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAnalytics)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::ProtocolAnalytics *nobj = static_cast<cocos2d::plugin::ProtocolAnalytics *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolAnalytics(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_ProtocolAnalytics_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_ProtocolAnalytics_class->name = "ProtocolAnalytics";
	jsb_cocos2d_plugin_ProtocolAnalytics_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->finalize = js_cocos2d_plugin_ProtocolAnalytics_finalize;
	jsb_cocos2d_plugin_ProtocolAnalytics_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("logTimedEventBegin", js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logError", js_pluginx_protocols_ProtocolAnalytics_logError, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCaptureUncaughtException", js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSessionContinueMillis", js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logEvent", js_pluginx_protocols_ProtocolAnalytics_logEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("startSession", js_pluginx_protocols_ProtocolAnalytics_startSession, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopSession", js_pluginx_protocols_ProtocolAnalytics_stopSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logTimedEventEnd", js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_ProtocolAnalytics_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_plugin_PluginProtocol_prototype,
		jsb_cocos2d_plugin_ProtocolAnalytics_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolAnalytics", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolAnalytics> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_ProtocolAnalytics_class;
		p->proto = jsb_cocos2d_plugin_ProtocolAnalytics_prototype;
		p->parentProto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_ProtocolIAP_class;
JSObject *jsb_cocos2d_plugin_ProtocolIAP_prototype;

bool js_pluginx_protocols_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolIAP_payForProduct : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TProductInfo arg0;
		ok &= pluginx::jsval_to_TProductInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolIAP_payForProduct : Error processing arguments");
		cobj->payForProduct(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolIAP_payForProduct : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolIAP_onPayResult(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolIAP_onPayResult : Invalid Native Object");
	if (argc == 2) {
		cocos2d::plugin::PayResultCode arg0;
		const char* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolIAP_onPayResult : Error processing arguments");
		cobj->onPayResult(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolIAP_onPayResult : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_pluginx_protocols_ProtocolIAP_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolIAP_configDeveloperInfo : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TIAPDeveloperInfo arg0;
		ok &= pluginx::jsval_to_TIAPDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolIAP_configDeveloperInfo : Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolIAP_configDeveloperInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

void js_cocos2d_plugin_ProtocolIAP_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolIAP)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::ProtocolIAP *nobj = static_cast<cocos2d::plugin::ProtocolIAP *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolIAP(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_ProtocolIAP_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_ProtocolIAP_class->name = "ProtocolIAP";
	jsb_cocos2d_plugin_ProtocolIAP_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_ProtocolIAP_class->finalize = js_cocos2d_plugin_ProtocolIAP_finalize;
	jsb_cocos2d_plugin_ProtocolIAP_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("payForProduct", js_pluginx_protocols_ProtocolIAP_payForProduct, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("onPayResult", js_pluginx_protocols_ProtocolIAP_onPayResult, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolIAP_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_ProtocolIAP_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_plugin_PluginProtocol_prototype,
		jsb_cocos2d_plugin_ProtocolIAP_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolIAP", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolIAP> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_ProtocolIAP_class;
		p->proto = jsb_cocos2d_plugin_ProtocolIAP_prototype;
		p->parentProto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_ProtocolAds_class;
JSObject *jsb_cocos2d_plugin_ProtocolAds_prototype;

bool js_pluginx_protocols_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAds_showAds : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TAdsInfo arg0;
		ok &= pluginx::jsval_to_TAdsInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAds_showAds : Error processing arguments");
		cobj->showAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 2) {
		cocos2d::plugin::TAdsInfo arg0;
		cocos2d::plugin::ProtocolAds::AdsPos arg1;
		ok &= pluginx::jsval_to_TAdsInfo(cx, argv[0], &arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAds_showAds : Error processing arguments");
		cobj->showAds(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAds_showAds : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAds_hideAds : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TAdsInfo arg0;
		ok &= pluginx::jsval_to_TAdsInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAds_hideAds : Error processing arguments");
		cobj->hideAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAds_hideAds : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAds_queryPoints : Invalid Native Object");
	if (argc == 0) {
		cobj->queryPoints();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAds_queryPoints : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAds_spendPoints : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAds_spendPoints : Error processing arguments");
		cobj->spendPoints(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAds_spendPoints : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAds_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAds_configDeveloperInfo : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TAdsDeveloperInfo arg0;
		ok &= pluginx::jsval_to_TAdsDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolAds_configDeveloperInfo : Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAds_configDeveloperInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolAds_getAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolAds_getAdsListener : Invalid Native Object");
	if (argc == 0) {
		cocos2d::plugin::AdsListener* ret = cobj->getAdsListener();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::plugin::AdsListener>(cx, (cocos2d::plugin::AdsListener*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolAds_getAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

void js_cocos2d_plugin_ProtocolAds_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAds)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::ProtocolAds *nobj = static_cast<cocos2d::plugin::ProtocolAds *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolAds(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_ProtocolAds_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_ProtocolAds_class->name = "ProtocolAds";
	jsb_cocos2d_plugin_ProtocolAds_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolAds_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_ProtocolAds_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolAds_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_ProtocolAds_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_ProtocolAds_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_ProtocolAds_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_ProtocolAds_class->finalize = js_cocos2d_plugin_ProtocolAds_finalize;
	jsb_cocos2d_plugin_ProtocolAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("showAds", js_pluginx_protocols_ProtocolAds_showAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hideAds", js_pluginx_protocols_ProtocolAds_hideAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("queryPoints", js_pluginx_protocols_ProtocolAds_queryPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("spendPoints", js_pluginx_protocols_ProtocolAds_spendPoints, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolAds_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAdsListener", js_pluginx_protocols_ProtocolAds_getAdsListener, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_ProtocolAds_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_plugin_PluginProtocol_prototype,
		jsb_cocos2d_plugin_ProtocolAds_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolAds> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_ProtocolAds_class;
		p->proto = jsb_cocos2d_plugin_ProtocolAds_prototype;
		p->parentProto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_ProtocolShare_class;
JSObject *jsb_cocos2d_plugin_ProtocolShare_prototype;

bool js_pluginx_protocols_ProtocolShare_onShareResult(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolShare_onShareResult : Invalid Native Object");
	if (argc == 2) {
		cocos2d::plugin::ShareResultCode arg0;
		const char* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolShare_onShareResult : Error processing arguments");
		cobj->onShareResult(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolShare_onShareResult : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_pluginx_protocols_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolShare_share : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TShareInfo arg0;
		ok &= pluginx::jsval_to_TShareInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolShare_share : Error processing arguments");
		cobj->share(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolShare_share : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolShare_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolShare_configDeveloperInfo : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TShareDeveloperInfo arg0;
		ok &= pluginx::jsval_to_TShareDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolShare_configDeveloperInfo : Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolShare_configDeveloperInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

void js_cocos2d_plugin_ProtocolShare_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolShare)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::ProtocolShare *nobj = static_cast<cocos2d::plugin::ProtocolShare *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolShare(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_ProtocolShare_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_ProtocolShare_class->name = "ProtocolShare";
	jsb_cocos2d_plugin_ProtocolShare_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolShare_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_ProtocolShare_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolShare_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_ProtocolShare_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_ProtocolShare_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_ProtocolShare_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_ProtocolShare_class->finalize = js_cocos2d_plugin_ProtocolShare_finalize;
	jsb_cocos2d_plugin_ProtocolShare_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("onShareResult", js_pluginx_protocols_ProtocolShare_onShareResult, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("share", js_pluginx_protocols_ProtocolShare_share, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolShare_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_ProtocolShare_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_plugin_PluginProtocol_prototype,
		jsb_cocos2d_plugin_ProtocolShare_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolShare", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolShare> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_ProtocolShare_class;
		p->proto = jsb_cocos2d_plugin_ProtocolShare_prototype;
		p->parentProto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_ProtocolSocial_class;
JSObject *jsb_cocos2d_plugin_ProtocolSocial_prototype;

bool js_pluginx_protocols_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_showLeaderboard : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_showLeaderboard : Error processing arguments");
		cobj->showLeaderboard(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_showLeaderboard : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_showAchievements : Invalid Native Object");
	if (argc == 0) {
		cobj->showAchievements();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_showAchievements : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_submitScore : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		long arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_long(cx, argv[1], (long *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_submitScore : Error processing arguments");
		cobj->submitScore(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_submitScore : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_pluginx_protocols_ProtocolSocial_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_configDeveloperInfo : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TSocialDeveloperInfo arg0;
		ok &= pluginx::jsval_to_TSocialDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_configDeveloperInfo : Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_configDeveloperInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TAchievementInfo arg0;
		ok &= pluginx::jsval_to_TAchievementInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : Error processing arguments");
		cobj->unlockAchievement(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

void js_cocos2d_plugin_ProtocolSocial_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolSocial)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::ProtocolSocial *nobj = static_cast<cocos2d::plugin::ProtocolSocial *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolSocial(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_ProtocolSocial_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_ProtocolSocial_class->name = "ProtocolSocial";
	jsb_cocos2d_plugin_ProtocolSocial_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_ProtocolSocial_class->finalize = js_cocos2d_plugin_ProtocolSocial_finalize;
	jsb_cocos2d_plugin_ProtocolSocial_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("showLeaderboard", js_pluginx_protocols_ProtocolSocial_showLeaderboard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("showAchievements", js_pluginx_protocols_ProtocolSocial_showAchievements, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("submitScore", js_pluginx_protocols_ProtocolSocial_submitScore, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolSocial_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("unlockAchievement", js_pluginx_protocols_ProtocolSocial_unlockAchievement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_ProtocolSocial_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_plugin_PluginProtocol_prototype,
		jsb_cocos2d_plugin_ProtocolSocial_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolSocial", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolSocial> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_ProtocolSocial_class;
		p->proto = jsb_cocos2d_plugin_ProtocolSocial_prototype;
		p->parentProto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_cocos2d_plugin_ProtocolUser_class;
JSObject *jsb_cocos2d_plugin_ProtocolUser_prototype;

bool js_pluginx_protocols_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_isLogined : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isLogined();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_isLogined : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_ProtocolUser_logout(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_logout : Invalid Native Object");
	if (argc == 0) {
		cobj->logout();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_logout : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_ProtocolUser_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_configDeveloperInfo : Invalid Native Object");
	if (argc == 1) {
		cocos2d::plugin::TUserDeveloperInfo arg0;
		ok &= pluginx::jsval_to_TUserDeveloperInfo(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolUser_configDeveloperInfo : Error processing arguments");
		cobj->configDeveloperInfo(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_configDeveloperInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_pluginx_protocols_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_login : Invalid Native Object");
	if (argc == 0) {
		cobj->login();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_login : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_pluginx_protocols_ProtocolUser_getSessionID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_getSessionID : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getSessionID();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_getSessionID : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;

void js_cocos2d_plugin_ProtocolUser_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolUser)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        cocos2d::plugin::ProtocolUser *nobj = static_cast<cocos2d::plugin::ProtocolUser *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_pluginx_protocols_ProtocolUser(JSContext *cx, JSObject *global) {
	jsb_cocos2d_plugin_ProtocolUser_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_cocos2d_plugin_ProtocolUser_class->name = "ProtocolUser";
	jsb_cocos2d_plugin_ProtocolUser_class->addProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolUser_class->delProperty = JS_DeletePropertyStub;
	jsb_cocos2d_plugin_ProtocolUser_class->getProperty = JS_PropertyStub;
	jsb_cocos2d_plugin_ProtocolUser_class->setProperty = JS_StrictPropertyStub;
	jsb_cocos2d_plugin_ProtocolUser_class->enumerate = JS_EnumerateStub;
	jsb_cocos2d_plugin_ProtocolUser_class->resolve = JS_ResolveStub;
	jsb_cocos2d_plugin_ProtocolUser_class->convert = JS_ConvertStub;
	jsb_cocos2d_plugin_ProtocolUser_class->finalize = js_cocos2d_plugin_ProtocolUser_finalize;
	jsb_cocos2d_plugin_ProtocolUser_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("isLogined", js_pluginx_protocols_ProtocolUser_isLogined, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logout", js_pluginx_protocols_ProtocolUser_logout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("configDeveloperInfo", js_pluginx_protocols_ProtocolUser_configDeveloperInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("login", js_pluginx_protocols_ProtocolUser_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSessionID", js_pluginx_protocols_ProtocolUser_getSessionID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_cocos2d_plugin_ProtocolUser_prototype = JS_InitClass(
		cx, global,
		jsb_cocos2d_plugin_PluginProtocol_prototype,
		jsb_cocos2d_plugin_ProtocolUser_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolUser", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<cocos2d::plugin::ProtocolUser> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_cocos2d_plugin_ProtocolUser_class;
		p->proto = jsb_cocos2d_plugin_ProtocolUser_prototype;
		p->parentProto = jsb_cocos2d_plugin_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_pluginx_protocols(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "plugin", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "plugin", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_pluginx_protocols_PluginProtocol(cx, obj);
	js_register_pluginx_protocols_ProtocolUser(cx, obj);
	js_register_pluginx_protocols_ProtocolShare(cx, obj);
	js_register_pluginx_protocols_ProtocolIAP(cx, obj);
	js_register_pluginx_protocols_ProtocolSocial(cx, obj);
	js_register_pluginx_protocols_ProtocolAnalytics(cx, obj);
	js_register_pluginx_protocols_ProtocolAds(cx, obj);
	js_register_pluginx_protocols_PluginManager(cx, obj);
}

