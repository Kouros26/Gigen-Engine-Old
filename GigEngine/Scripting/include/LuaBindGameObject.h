#pragma once
#include "sol.hpp"

namespace GigScripting
{
	class LuaBindGameObject
	{
	public:
		static void BindGameObject(sol::state& pLuaState);
	};
}