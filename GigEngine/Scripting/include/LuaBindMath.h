#pragma once
#include <sol.hpp>

namespace GigScripting
{
    class LuaBindMath
    {
    public:
        static void BindMath(sol::state& pLua);
    };
}