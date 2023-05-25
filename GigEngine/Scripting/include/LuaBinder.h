#pragma once
#include <sol.hpp>

namespace GigScripting
{
    class LuaBinder
    {
    public:

        static void Bind(sol::state& pLuaState);
    };
}
