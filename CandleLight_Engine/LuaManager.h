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

	bool validState();

	inline bool success() { return _status == 0; }
	inline bool fail() { return _status != 0; }

private:
	lua_State * _state = nullptr;

	int _status = 0;

	static LuaManager* _instance;
	LuaManager();
	~LuaManager();
};

