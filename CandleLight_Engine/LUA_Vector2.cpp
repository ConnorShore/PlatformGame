#include "LUA_Vector2.h"
#include "Math/Vector.h"

const char LUA_Vector2::className[] = "Vector2";

const Luna<LUA_Vector2>::FunctionType LUA_Vector2::methods[]{
	lunamethod(LUA_Vector2, Add),
	lunamethod(LUA_Vector2, Subtract),
	lunamethod(LUA_Vector2, Multiply),
	lunamethod(LUA_Vector2, Divide),
	lunamethod(LUA_Vector2, Dot),
	lunamethod(LUA_Vector2, Cross),
	{0, 0}
};

const Luna<LUA_Vector2>::PropertyType LUA_Vector2::properties[]{
	{ "x", &LUA_Vector2::GetX, &LUA_Vector2::SetX },
	{ "y", &LUA_Vector2::GetY, &LUA_Vector2::SetY },
	{0}
};

LUA_Vector2::LUA_Vector2(lua_State * state)
{
	int argc = LuaManager::getArgCount(state);
	float x = 0.0f, y = 0.0f;

	if (argc == 2) {
		x = LuaManager::getFloat(state, 1);
		y = LuaManager::getFloat(state, 2);
	}
	else {
		printf("Vector2(float, float) expects 2 arguments\n");
	}

	vector.x = x;
	vector.y = y;
}

LUA_Vector2::LUA_Vector2(Vector2& vec2) : vector(vec2)
{
}


LUA_Vector2::~LUA_Vector2()
{
}

int LUA_Vector2::Add(lua_State * state)
{
	int argc = LuaManager::getArgCount(state);
	if (argc == 2) {
		LUA_Vector2* vec2 = Luna<LUA_Vector2>::lightcheck(state, 2);

		if (vec2) {
			Luna<LUA_Vector2>::push(state, new LUA_Vector2(AddVec2(vector, vec2->vector)));
			return 1;
		}
	}
	else {
		printf("vector:Add(vec2) expects 1 argument\n");
	}
	return 0;
}

int LUA_Vector2::Subtract(lua_State * state)
{
	int argc = LuaManager::getArgCount(state);
	if (argc == 2) {
		LUA_Vector2* vec2 = Luna<LUA_Vector2>::lightcheck(state, 2);

		if (vec2) {
			Luna<LUA_Vector2>::push(state, new LUA_Vector2(SubtractVec2(vector, vec2->vector)));
			return 1;
		}
	}
	else {
		printf("vector:Subtract(vec2) expects 1 argument\n");
	}
	return 0;
}

int LUA_Vector2::Multiply(lua_State * state)
{
	int argc = LuaManager::getArgCount(state);
	if (argc == 2) {
		LUA_Vector2* vec2 = Luna<LUA_Vector2>::lightcheck(state, 2);

		if (vec2) {
			Luna<LUA_Vector2>::push(state, new LUA_Vector2(MultiplyVec2(vector, vec2->vector)));
			return 1;
		}
	}
	else {
		printf("vector:Subtract(vec2) expects 1 argument\n");
	}
	return 0;
}

int LUA_Vector2::Divide(lua_State * state)
{
	int argc = LuaManager::getArgCount(state);
	if (argc == 2) {
		LUA_Vector2* vec2 = Luna<LUA_Vector2>::lightcheck(state, 2);

		if (vec2) {
			Luna<LUA_Vector2>::push(state, new LUA_Vector2(DivideVec2(vector, vec2->vector)));
			return 1;
		}
	}
	else {
		printf("vector:Subtract(vec2) expects 1 argument\n");
	}
	return 0;
}

int LUA_Vector2::Dot(lua_State * state)
{
	return 0;
}

int LUA_Vector2::Cross(lua_State * state)
{
	return 0;
}

void LUA_Vector2::bind()
{
	static bool initalized = false;
	if (!initalized) {
		initalized = true;
		Luna<LUA_Vector2>::Register(LuaManager::instance()->getLuaState());
	}
}
