#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sol.hpp>

namespace GigScripting
{
    class Behaviour;
    class ScriptInterpreter

    {
    public:

        static ScriptInterpreter& GetInstance();

        ScriptInterpreter();

        ScriptInterpreter(const std::string& pScriptFolderRoot);

        ScriptInterpreter(const ScriptInterpreter&) = delete;
        ScriptInterpreter(ScriptInterpreter&&) = delete;
        ScriptInterpreter& operator=(const ScriptInterpreter&) = delete;
        ScriptInterpreter& operator=(ScriptInterpreter&&) = delete;

        ~ScriptInterpreter();

        void CreateLuaContextAndBindGlobal();

        void DestroyLuaContext();

        void RegisterBehaviour(Behaviour* pBehaviour);

        void UnregisterBehaviour(Behaviour* pBehaviour);

        void RefreshBehaviours();

        bool IsOk() const;

    private:
        std::unique_ptr<sol::state> luaState;
        std::string scriptFolderRoot;
        std::vector<Behaviour*> behaviours;
        bool isOk;
    };
}

#define SCRIPT_INTERPRETER GigScripting::ScriptInterpreter::GetInstance()