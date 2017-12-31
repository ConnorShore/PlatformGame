#include <iostream>
#include "Game.h"

#include <CandleLight_Engine\lua\lua.hpp>


int lua_square(lua_State* S) {
	float x = lua_tonumber(S, 1);
	lua_pushnumber(S, x*x);
	return 1;
}

int main(int argc, char** argv)
{
	Game game;
	game.run();

	//lua_State* S = luaL_newstate();
	//luaL_openlibs(S);

	////lua_register(S, "square", lua_square);

	//luaL_dofile(S, "Scripts/main.lua");

	//lua_getglobal(S, "update");

	//int stat = lua_pcall(S, 0, 0, 0);
	//if (stat != 0) {
	//	printf("Failed to call function update");
	//}
	//std::cin.get();

	return 0;
}

//TODO: Make Lua Manager class to hold registration of functions, loading scripts, main lua state, etc
//TODO: Add error class and logging