#pragma once

#include "lua\lua.hpp"

#include <string>

class LuaManager
{
public:
	static LuaManager* instance();

	void loadScript(const std::string& scriptName);
	void registerFunction(const std::string& luaFuncName, lua_CFunction localFuncName);
	void callFunction(const std::string& funcName);

	inline lua_State* getLuaState() { return _state; }
	inline bool success() { return _status == 0; }
	inline bool fail() { return _status != 0; }

	static int getInt(lua_State* state, int stackpos);
	static int getFloat(lua_State* state, int stackpos);

	static void pushInt(lua_State* state, int number);
	static void pushFloat(lua_State* state, float number);
	static void pushBool(lua_State* state, bool value);

	static int getArgCount(lua_State* state);

	static bool validState(lua_State* state);

private:
	lua_State * _state = nullptr;

	static LuaManager* _instance;

	int _status = 0;

	LuaManager();
	~LuaManager();
};

