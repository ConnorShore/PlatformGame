#pragma once

#include "InputManager.h"

#include "luna.h"
#include "lua\lua.hpp"

class LUA_InputManager
{
public:
	static const char className[];
	static const Luna<LUA_InputManager>::RegType Register[];

	LUA_InputManager(lua_State* state);
	~LUA_InputManager();

	int KeyDown(lua_State* state);	//1 param (keycode)
	int SetMousePosition(lua_State* state);	//2 params (x,y)

	static void bind();
};