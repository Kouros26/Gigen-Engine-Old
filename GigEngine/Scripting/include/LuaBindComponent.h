#pragma once
#include <sol.hpp>
#include "GameObject.h"
namespace GigScripting
{
    struct LuaCollisionDelegateFunc
    {
        std::function<void(GameObject*)> OnCollisionEnter;
        std::function<void(GameObject*)> OnCollisionExit;
        std::function<void(GameObject*)> OnTriggerEnter;
        std::function<void(GameObject*)> OnTriggerExit;
        std::function<void(GameObject*)> defaultReturn;
    };

    class LuaBindComponent
    {
    public:

        static void BindComponent(sol::state& pLuaState);

        static void DelegatePhysics(sol::state& pLuaState, std::string DelegateString);
        static bool DelegateFromString(sol::state& pLuaState, std::string DelegateString);
        static std::function<void(GameObject*)>& getFunctionFromString(std::string pInput);

        static inline LuaCollisionDelegateFunc delegateFunctions;
    };
}