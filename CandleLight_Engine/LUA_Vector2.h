#pragma once

#include "luna.h"
#include "lua/lua.hpp"
#include "Math/Vector.h"
#include "LuaManager.h"

class LUA_Vector2
{
public:
	static const char className[];
	static const Luna<LUA_Vector2>::FunctionType LUA_Vector2::methods[];
	static const Luna<LUA_Vector2>::PropertyType LUA_Vector2::properties[];

	LUA_Vector2(lua_State* state);
	LUA_Vector2(Vector2& vec2);
	~LUA_Vector2();

	int Add(lua_State* state);
	int Subtract(lua_State* state);
	int Multiply(lua_State* state);
	int Divide(lua_State* state);
	int Dot(lua_State* state);
	int Cross(lua_State* state);

	static void bind();

	//Property getters/setters//
	inline int LUA_Vector2::GetX(lua_State * state)
	{
		LuaManager::pushFloat(state, vector.x);
		return 1;
	}

	inline int LUA_Vector2::GetY(lua_State * state)
	{
		LuaManager::pushFloat(state, vector.y);
		return 1;
	}

	inline int LUA_Vector2::SetX(lua_State * state)
	{
		vector.x = LuaManager::getFloat(state, -1);
		return 0;
	}

	inline int LUA_Vector2::SetY(lua_State * state)
	{
		vector.y = LuaManager::getFloat(state, -1);
		return 0;
	}

	Vector2 vector;
};

