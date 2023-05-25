#pragma once
#include <string>
#include "Log.h"

namespace GigScripting
{
	template<typename ...Args>
	void Behaviour::CallLuaFunction(const std::string& pFunctionName, Args&&... pArgs)
	{
		if (scriptTable.valid())
		{
			if (scriptTable[pFunctionName].valid())
			{
				sol::protected_function pfr = scriptTable[pFunctionName];
				auto pfrResult = pfr.call(scriptTable, std::forward<Args>(pArgs)...);
				if (!pfrResult.valid())
				{
					sol::error err = pfrResult;
					GIG_ERROR(err.what());
				}
			}
		}
	}
}