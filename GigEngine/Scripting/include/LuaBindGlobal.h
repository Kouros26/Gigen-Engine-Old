#pragma once

#include <sol.hpp>

namespace GigScripting
{
    class LuaBinderGlobal
    {
    public:

        static void BindGlobals(sol::state& pLuaState);
    };
}
