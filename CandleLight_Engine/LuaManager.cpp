#include "LuaManager.h"

#include "LUA_InputManager.h"

LuaManager* LuaManager::_instance = nullptr;

LuaManager::LuaManager()
{
	_state = luaL_newstate();
	luaL_openlibs(_state);
}


LuaManager::~LuaManager()
{
	delete _state;
}

LuaManager * LuaManager::instance()
{
	if (!_instance) {
		_instance = new LuaManager;

		LUA_InputManager::bind();
	}

	return _instance;
}

void LuaManager::loadScript(const std::string & scriptName, bool execute)
{
	if (validState(_state)) {
		if (execute)
			_status = luaL_dofile(_state, scriptName.c_str());
		else
			_status = luaL_loadfile(_state, scriptName.c_str());
		if (fail()) {
			//post error message
			printf("Failed to load script %s\n", scriptName.c_str());
		}
	}
}

void LuaManager::registerFunction(const std::string & luaFuncName, lua_CFunction localFuncName)
{
	if (validState(_state)) {
		lua_register(_state, luaFuncName.c_str(), localFuncName);
	}
}

void LuaManager::callFunction(const std::string & funcName)
{
	if (validState(_state)) {
		lua_getglobal(_state, funcName.c_str());
		_status = lua_pcall(_state, 0, 0, 0);
		if (fail()) {
			printf("Failed to call function %s\n", funcName.c_str());
		}
	}
}

int LuaManager::getInt(lua_State * state, int stackpos)
{
	return static_cast<int>(lua_tointeger(state, stackpos));
}

int LuaManager::getFloat(lua_State * state, int stackpos)
{
	return static_cast<float>(lua_tonumber(state, stackpos));
}

void LuaManager::pushInt(lua_State* state, int number)
{
	lua_pushnumber(state, number);
}

void LuaManager::pushFloat(lua_State* state, float number)
{
	lua_pushnumber(state, number);
}

void LuaManager::pushBool(lua_State * state, bool value)
{
	lua_pushboolean(state, static_cast<int>(value));
}

int LuaManager::getArgCount(lua_State* state)
{
	return lua_gettop(state);
}

bool LuaManager::validState(lua_State* state)
{
	if (state != nullptr)
		return true;
	else
		return false;
}
