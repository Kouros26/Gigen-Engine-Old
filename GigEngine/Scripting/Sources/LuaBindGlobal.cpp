#include "LuaBindGlobal.h"
#include "Log.h"
#include "Inputs.h"
#include "Vec2/FVec2.hpp"
#include "GameObjectManager.h"
#include "WorldPhysics.h"
#include "LuaBindComponent.h"
#include "WorldPhysics.h"
void GigScripting::LuaBinderGlobal::BindGlobals(sol::state& pLuaState)
{
    using namespace GigInput;

    auto& luaState = pLuaState;

    luaState.new_usertype<Collision>("Collision",
        "other", &Collision::other,
        "contactPoint", &Collision::contactPoint,
        "collisionStrength", &Collision::collisionStrength

    );

    luaState.new_usertype<HitResult>("HitResult",
        sol::constructors<void()>(),
        "hitObject", &HitResult::hitObject,
        "hitPoint", &HitResult::hitPoint

    );

    luaState.new_enum<RayCastDebug>("RayCastDebug",
        {
            {"None", RayCastDebug::None },
            { "OneFrame", RayCastDebug::OneFrame },
            { "Timer", RayCastDebug::Timer },
            { "Forever", RayCastDebug::Forever}
        }

    );

    luaState.new_usertype<GameObjectManager>("GameObjectManager",
        "GetGameObject", &GameObjectManager::GetGameObject,
        "GetGameObjectByName", &GameObjectManager::FindObjectByName,
        "GetObjectById", &GameObjectManager::FindObjectById,
        "GetAllObjectsByName", &GameObjectManager::FindObjectsByName,
        "Instantiate", sol::overload
        (
            sol::resolve<GameObject * (const std::string&)>(&GameObjectManager::CreateGameObject),
            sol::resolve<GameObject * (const std::string&, const lm::FVec3&, const lm::FVec3&, const lm::FVec3&)>(&GameObjectManager::CreateGameObject),
            sol::resolve<GameObject * (const lm::FVec3&, const lm::FVec3&, const lm::FVec3&)>(&GameObjectManager::CreateGameObject)

        ),
        "Destroy", &GameObjectManager::RemoveGameObject,
        "CreateCamera", &GameObjectManager::CreateCamera
    );

    luaState.new_enum<Keys>("Keys",
        {
            {"Escape", Keys::ESCAPE},
            {"Space", Keys::SPACE},
            {"Up", Keys::UP},
            {"Down", Keys::DOWN},
            {"Left", Keys::LEFT},
            {"Right", Keys::RIGHT},
            {"LeftShift", Keys::LEFT_SHIFT},
            {"RightShift", Keys::RIGHT_SHIFT},
            {"LeftControl", Keys::LEFT_CONTROL},
            {"RightControl", Keys::RIGHT_CONTROL},
            {"LeftAlt", Keys::LEFT_ALT},
            {"RightAlt", Keys::RIGHT_ALT},
            {"Tab", Keys::TAB},
            {"Enter", Keys::ENTER},
            {"Backspace", Keys::BACKSPACE},
            {"F1", Keys::F1},
            {"F2", Keys::F2},
            {"F3", Keys::F3},
            {"F4", Keys::F4},
            {"F5", Keys::F5},
            {"F6", Keys::F6},
            {"F7", Keys::F7},
            {"F8", Keys::F8},
            {"F9", Keys::F9},
            {"F10", Keys::F10},
            {"F11", Keys::F11},
            {"F12", Keys::F12},
            {"Last", Keys::LAST},
            {"A", Keys::A},
            {"B", Keys::B},
            {"C", Keys::C},
            {"D", Keys::D},
            {"E", Keys::E},
            {"F", Keys::F},
            {"G", Keys::G},
            {"H", Keys::H},
            {"I", Keys::I},
            {"J", Keys::J},
            {"K", Keys::K},
            {"L", Keys::L},
            {"M", Keys::M},
            {"N", Keys::N},
            {"O", Keys::O},
            {"P", Keys::P},
            {"Q", Keys::Q},
            {"R", Keys::R},
            {"S", Keys::S},
            {"T", Keys::T},
            {"U", Keys::U},
            {"V", Keys::V},
            {"W", Keys::W},
            {"X", Keys::X},
            {"Y", Keys::Y},
            {"Z", Keys::Z},
        });

    luaState.new_enum<MouseButton>("MouseButtons",
        {
            {"Left", MouseButton::LEFT},
            {"Right", MouseButton::RIGHT},
            {"Middle", MouseButton::MIDDLE}
        });

    luaState.create_named_table("Debug");
    luaState.create_named_table("Inputs");
    luaState.create_named_table("Tools");
    luaState.create_named_table("Physics");

    luaState["Debug"]["Log"] = [](const std::string& pMessage) { GIG_LOG(pMessage); };
    luaState["Debug"]["LogWarning"] = [](const std::string& pMessage) { GIG_WARNING(pMessage); };
    luaState["Debug"]["LogError"] = [](const std::string& pMessage) { GIG_ERROR(pMessage); };

    luaState["Inputs"]["GetKey"] = [](Keys pKey) { return Inputs::GetKey(pKey); };
    luaState["Inputs"]["GetKeyDown"] = [](Keys pKey) { return Inputs::GetKeyDown(pKey); };
    luaState["Inputs"]["GetKeyUp"] = [](Keys pKey) { return Inputs::GetKeyUp(pKey); };
    luaState["Inputs"]["GetMouse"] = []() { return Inputs::GetMouse(); };
    luaState["Inputs"]["GetMousePos"] = []()
    {
        auto mouse = Inputs::GetMouse();
        return lm::FVec2(static_cast<float>(mouse.mouseOffsetX), static_cast<float>(mouse.mouseOffsetY));
    };

    luaState["Tools"]["BoolToInt"] = [](bool pBool) { return (int)(pBool); };
    luaState["Tools"]["IntToBool"] = [](int pInt) { return (bool)(pInt); };
    luaState["Tools"]["FloatToInt"] = [](float pFloat) { return (int)(pFloat); };
    luaState["Tools"]["IntToFloat"] = [](int pInt) { return (float)(pInt); };

    luaState["Physics"]["RayCast"] = sol::overload
    (
        sol::resolve<bool(const lm::FVec3&, const lm::FVec3&, HitResult&,
            const RayCastDebug, float, const std::vector<GameObject*>&, const lm::FVec3&, const lm::FVec3&) >(&WorldPhysics::RayCast),
        sol::resolve<bool(const lm::FVec3&, const lm::FVec3&, HitResult&)>(&WorldPhysics::RayCast),
        sol::resolve<bool(const lm::FVec3&, const lm::FVec3&, HitResult&,
            const RayCastDebug, float)>(&WorldPhysics::RayCast),
        sol::resolve<bool(const lm::FVec3&, const lm::FVec3&, HitResult&,
            const RayCastDebug, float, const lm::FVec3&)>(&WorldPhysics::RayCast),

        sol::resolve<bool(const lm::FVec3&, const lm::FVec3&, HitResult&,
            const RayCastDebug, float, const lm::FVec3&, const lm::FVec3&)>(&WorldPhysics::RayCast)

    );
    luaState["Physics"]["SetGravity"] = &WorldPhysics::SetGravity;
}