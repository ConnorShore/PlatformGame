#pragma once

#include "InputManager.h"
#include "LuaManager.h"

#include "luna.h"
#include "lua\lua.hpp"

class LUA_InputManager
{
public:
	static const char className[];
	static const Luna<LUA_InputManager>::FunctionType LUA_InputManager::methods[];
	static const Luna<LUA_InputManager>::PropertyType LUA_InputManager::properties[];

	LUA_InputManager(lua_State* state);
	~LUA_InputManager();

	int KeyDown(lua_State* state);	//1 param (keycode)
	int GetMousePosition(lua_State* state);	//2 params (x,y)

	inline int getProperty(lua_State* state)
	{
		LuaManager::pushFloat(state, random);
		return 1;
	}

	inline int setProperty(lua_State* state)
	{
		random = LuaManager::getFloat(state, -1);
		return 0;
	}

	static void bind();

	float random = 5;
};