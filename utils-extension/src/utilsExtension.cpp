#define EXTENSION_NAME utilsExt
#define LIB_NAME "utilsExt"
#define MODULE_NAME LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include "utils_private.h"

namespace dmUtils {

static int Lua_ShowIntent(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    const char* mailUri_lua = luaL_checkstring(L, 1);
    showMailIntent(mailUri_lua);
    return 0;
}

static int Lua_ShowKeyboard(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    showKeyboard();
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"show_mail_intent", Lua_ShowIntent},
    {"show_ext_keyboard" , Lua_ShowKeyboard},
    {0, 0}
};

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
    InitializeExtension();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeUtils(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeUtils(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateUtils(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

static void OnEventUtils(dmExtension::Params* params, const dmExtension::Event* event)
 {
    switch(event->m_Event)
    {
        case dmExtension::EVENT_ID_ACTIVATEAPP:
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
