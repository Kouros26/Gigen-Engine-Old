#include "ScriptInterpreter.h"

#include "LuaBinder.h"
#include "Behaviour.h"

GigScripting::ScriptInterpreter::~ScriptInterpreter()
{
	DestroyLuaContext();
}

void GigScripting::ScriptInterpreter::CreateLuaContextAndBindGlobal()
{
	if (!luaState)
	{
		luaState = std::make_unique<sol::state>();
		luaState->open_libraries(sol::lib::base, sol::lib::math);

		GigScripting::LuaBinder::Bind(*luaState);
		isOk = true;

		for (const auto& behaviour : behaviours)
		{
			if (!behaviour->RegisterToLuaContext(scriptFolderRoot, *luaState))
			{
				isOk = false;
			}
		}
		if (!isOk)
		{
			GIG_ERROR("Script interpreter failed to register scripts.Check your lua scripts");
		}
	}
}

void GigScripting::ScriptInterpreter::DestroyLuaContext()
{
	if (luaState)
	{
		for (const auto& behaviour : behaviours)
		{
			behaviour->UnregisterFromLuaContext();
		}
		luaState->collect_garbage();
		luaState.reset();
		isOk = false;
	}
}

void GigScripting::ScriptInterpreter::RegisterBehaviour(Behaviour* pBehaviour)
{
	if (!luaState)
	{
		return;
	}

	behaviours.push_back(pBehaviour);
	if (!pBehaviour->RegisterToLuaContext(scriptFolderRoot, *luaState))
	{
		isOk = false;
	}
}

void GigScripting::ScriptInterpreter::UnregisterBehaviour(Behaviour* pBehaviour)
{
	if (!luaState)
	{
		return;
	}

	pBehaviour->UnregisterFromLuaContext();
	behaviours.erase(std::remove_if(behaviours.begin(), behaviours.end(), [pBehaviour](const auto& behaviour) { return pBehaviour == behaviour; }), behaviours.end());
	RefreshBehaviours();
}

void GigScripting::ScriptInterpreter::RefreshBehaviours()
{
	DestroyLuaContext();
	CreateLuaContextAndBindGlobal();
}

bool GigScripting::ScriptInterpreter::IsOk() const
{
	return isOk;
}

GigScripting::ScriptInterpreter& GigScripting::ScriptInterpreter::GetInstance()
{
	static ScriptInterpreter instance;
	return instance;
}

GigScripting::ScriptInterpreter::ScriptInterpreter(const std::string& pScriptFolderRoot)
{
	scriptFolderRoot = pScriptFolderRoot;
	CreateLuaContextAndBindGlobal();
}

GigScripting::ScriptInterpreter::ScriptInterpreter()
{
	scriptFolderRoot = "../../../Resources/Editor/Scripts/";

	CreateLuaContextAndBindGlobal();
}