#include "Behaviour.h"
#include <ScriptInterpreter.h>

#include "ScriptInterpreter.h"

GigScripting::Behaviour::Behaviour(GameObject* obj) : Component(obj)
{
    scriptTable = sol::nil;
}

GigScripting::Behaviour::~Behaviour()
{
    SCRIPT_INTERPRETER.UnregisterBehaviour(this);
}

void GigScripting::Behaviour::Awake()
{
    CallLuaFunction("Awake");
}

void GigScripting::Behaviour::Start()
{
    CallLuaFunction("Start");
}

void GigScripting::Behaviour::Update(float pDeltaTime)
{
    CallLuaFunction("Update", pDeltaTime);
}

void GigScripting::Behaviour::LateUpdate(float pDeltaTime)
{
    CallLuaFunction("LateUpdate", pDeltaTime);
}

GigScripting::Behaviour::Behaviour(GameObject* obj, const std::string& scriptName) : Component(obj), scriptName(scriptName)
{
    scriptTable = sol::nil;
}

Component* GigScripting::Behaviour::Clone(GameObject* newGameObject)
{
    return new Behaviour(newGameObject);
}

std::string GigScripting::Behaviour::GetType()
{
    const std::string type(typeid(this).name());
    return type.substr(6, type.size() - 16);
}

const std::string& GigScripting::Behaviour::GetScriptName() const
{
    return scriptName;
}

sol::table& GigScripting::Behaviour::GetScriptTable()
{
    return scriptTable;
}

bool GigScripting::Behaviour::RegisterToLuaContext(const std::string& pScriptFolder, sol::state& pState)
{
    auto result = pState.safe_script_file(pScriptFolder + scriptName + ".lua", &sol::script_pass_on_error);

    if (!result.valid())
    {
        sol::error err = result;
        std::string what = err.what();
        GIG_ERROR(what);
        return false;
    }
    else
    {
        if (result.return_count() == 1 && result[0].is<sol::table>())
        {
            scriptTable = result[0];
            scriptTable["owner"] = gameObject;
            return true;
        }
        else
        {
            GIG_ERROR("Script file " + scriptName + " does not return a table");
            return false;
        }
    }
}

void GigScripting::Behaviour::UnregisterFromLuaContext()
{
    scriptTable = sol::nil;
}