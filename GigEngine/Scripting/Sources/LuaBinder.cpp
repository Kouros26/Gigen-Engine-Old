#include "LuaBinder.h"
#include "LuaBindGlobal.h"
#include "LuaBindMath.h"
#include "LuaBindGameObject.h"
#include "LuaBindComponent.h"
void GigScripting::LuaBinder::Bind(sol::state& pLuaState)
{
    auto& luaState = pLuaState;
    GigScripting::LuaBinderGlobal::BindGlobals(luaState);
    GigScripting::LuaBindMath::BindMath(luaState);
    GigScripting::LuaBindGameObject::BindGameObject(luaState);
    GigScripting::LuaBindComponent::BindComponent(luaState);
}