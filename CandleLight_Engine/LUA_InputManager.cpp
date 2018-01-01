#include "LUA_InputManager.h"

#include "LuaManager.h"

#include <iostream>

const char LUA_InputManager::className[] = "InputManager";

const Luna<LUA_InputManager>::RegType LUA_InputManager::Register[] = {
	{ "KeyDown", &LUA_InputManager::KeyDown },
	{ "SetMousePosition", &LUA_InputManager::SetMousePosition },
	{0}
};


LUA_InputManager::LUA_InputManager(lua_State * state)
{

}

LUA_InputManager::~LUA_InputManager()
{
}

int LUA_InputManager::KeyDown(lua_State * state)
{
	int argc = LuaManager::getArgCount(state);
	if (argc > 1) {
		int code = LuaManager::getInt(state, 2);

		LuaManager::pushBool(state, InputManager::instance()->isKeyDown(code));
		return 1;
	}
	else {
		printf("KeyDown(int code) expects 1 argument\n");
	}
	return 0;
}

int LUA_InputManager::SetMousePosition(lua_State * state)
{
	return 0;
}

void LUA_InputManager::bind()
{
	static bool initalized = false;
	if (!initalized) {
		initalized = true;
		Luna<LUA_InputManager>::Register(LuaManager::instance()->getLuaState());

		LuaManager::instance()->loadScript("../CandleLight_Engine/Scripts/input_init.lua");
	}
}
