#define EXTENSION_NAME UtilsExt
#define LIB_NAME "UtilsExt"
#define MODULE_NAME "utilsExt"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#include "utils_private.h"

namespace dmUtils {

static int Lua_Initialize(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    Initialize();
    return 0;
}

static int Lua_SetCallback(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static int Lua_ShowIntent(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    const char* mailUri_lua = luaL_checkstring(L, 1);
    showMailIntent(mailUri_lua);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"show_mail_intent", Lua_ShowIntent},
    {0, 0}
}

static void LuaInit(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
}

static dmExtension::Result AppInitializeUtils(dmExtension::AppParams* params)
{
    dmLogInfo("AppInitializeUtils");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeUtils(dmExtension::Params* params)
{
    dmLogInfo("InitializeUtils");
    LuaInit(params->m_L);
    Initialize_Ext(params, DEFOLD_USERAGENT);
    InitializeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeUtils(dmExtension::AppParams* params)
{
    Finalize_Ext();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeUtils(dmExtension::Params* params)
{
    FinalizeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateUtils(dmExtension::Params* params)
{
    UpdateCallback();
    return dmExtension::RESULT_OK;
}

static void OnEventUtils(dmExtension::Params* params, const dmExtension::Event* event)
 {
    switch(event->m_Event)
    {
        case dmExtension::EVENT_ID_ACTIVATEAPP:
            ActivateApp();
            break;
    }
 }

} //namespace dmUtils

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmUtils::AppInitializeUtils, dmUtils::AppFinalizeUtils, dmUtils::InitializeUtils, dmUtils::UpdateUtils, dmUtils::OnEventUtils, dmUtils::FinalizeUtils)

#else

static  dmExtension::Result InitializeUtils(dmExtension::Params* params)
{
    dmLogInfo("Registered extension Utils (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeUtils(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeUtils , 0, 0, FinalizeUtils)

#endif // IOS/Android
