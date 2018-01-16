#pragma once

#include "Type_Vector2.h"

//Vector 2 definitions
typedef Type_Vector2<int> iVector2;
typedef Type_Vector2<long> lVector2;
typedef Type_Vector2<float> Vector2;
typedef Type_Vector2<double> dVector2;



static inline Vector2 AddVec2(Vector2& v1, Vector2& v2)
{
	Vector2 vec;
	vec.x = v1.x + v2.x;
	vec.y += v1.y + v2.y;
	return vec;
}

static inline Vector2 SubtractVec2(Vector2& v1, Vector2& v2)
{
	Vector2 vec;
	vec.x = v1.x - v2.x;
	vec.y += v1.y - v2.y;
	return vec;
}

static inline Vector2 MultiplyVec2(Vector2& v1, Vector2& v2)
{
	Vector2 vec;
	vec.x = v1.x * v2.x;
	vec.y += v1.y * v2.y;
	return vec;
}

static inline Vector2 DivideVec2(Vector2& v1, Vector2& v2)
{
	Vector2 vec;
	vec.x = v1.x / v2.x;
	vec.y += v1.y / v2.y;
	return vec;
}