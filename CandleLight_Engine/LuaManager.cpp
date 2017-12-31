#include "LuaManager.h"

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
	}

	return _instance;
}

void LuaManager::loadScript(const std::string & scriptName)
{
	if (validState()) {
		_status = luaL_dofile(_state, scriptName.c_str());
		if (fail()) {
			//post error message
			printf("Failed to load script %s\n", scriptName.c_str());
		}
	}
}

void LuaManager::registerFunction(const std::string & luaFuncName, lua_CFunction localFuncName)
{
	if (validState()) {
		lua_register(_state, luaFuncName.c_str(), localFuncName);
	}
}

void LuaManager::callFunction(const std::string & funcName)
{
	if (validState()) {
		lua_getglobal(_state, funcName.c_str());
		_status = lua_pcall(_state, 0, 0, 0);
		if (fail()) {
			printf("Failed to call function %s\n", funcName.c_str());
		}
	}
}

bool LuaManager::validState()
{
	if (_state != nullptr)
		return true;
	else
		return false;
}
