#pragma once
#include <sol.hpp>
#include "Component.h"

namespace GigScripting
{
    class Behaviour : public Component
    {
    public:
        Behaviour(GameObject* obj);
        Behaviour(GameObject* obj, const std::string& scriptName);

        virtual ~Behaviour() override;

        virtual void Awake() override;
        virtual void Start() override;
        virtual void Update(float pDeltaTime) override;
        virtual void LateUpdate(float pDeltaTime) override;

        //virtual void OnCollisionEnter(Collision collision) override {};
        //virtual void OnCollisionStay(Collision collision) override {};

        virtual Component* Clone(GameObject* newGameObject) override;

        virtual std::string GetType() override;

        [[nodiscard]] const std::string& GetScriptName() const;

        sol::table& GetScriptTable();

        template<typename... Args>
        void CallLuaFunction(const std::string& functionName, Args&&... args);

        bool RegisterToLuaContext(const std::string& pScriptFolder, sol::state& pState);

        void UnregisterFromLuaContext();

    public:
        const std::string scriptName;

    private:
        sol::table scriptTable;
    };
}

#include "Behaviour.inl"