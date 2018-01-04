#pragma once

#include "glm\glm.hpp"

template<typename T>
struct Type_Vector2
{
	//Data
	union {T x, r, u; };
	union {T y, g, v; };

	//Constructors//
	inline Type_Vector2()
	{
		this->x = static_cast<T>(0);
		this->y = static_cast<T>(0);
	}

	inline Type_Vector2(T const& v)
	{
		this->x = v;
		this->y = v;
	}

	template<typename U>
	inline explicit Type_Vector2(U const& v)
	{
		this->x = static_cast<T>(v);
		this->y = static_cast<T>(v);
	}

	template<typename U, typename V>
	inline Type_Vector2(U const& x, V const& y)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
	}

	template<typename U>
	inline Type_Vector2(Type_Vector2<U>& vec2)
	{
		this->x = static_cast<T>(vec2.x);
		this->y = static_cast<T>(vec2.y);
	}

	inline Type_Vector2(glm::vec2& vec2)
	{
		this->x = static_cast<T>(vec2.x);
		this->y = static_cast<T>(vec2.y);
	}

	//Operators//
	inline Type_Vector2<T>& operator = (Type_Vector2<T> vec2)
	{
		this->x = vec2.x;
		this->y = vec2.y;
		return *this;
	}
	template<typename U>
	inline Type_Vector2<T>& operator = (Type_Vector2<U> vec2)
	{
		this->x = static_cast<vec2.x>;
		this->y = static_cast<vec2.y>;
		return *this;
	}
	inline Type_Vector2<T>& operator += (Type_Vector2<T> vec2)
	{
		this->x *= vec2.x;
		this->y *= vec2.y;
		return *this;
	}
	template<typename U>
	inline Type_Vector2<T>& operator += (Type_Vector2<U> vec2)
	{
		this->x *= static_cast<vec2.x>;
		this->y *= static_cast<vec2.y>;
		return *this;
	}
	inline Type_Vector2<T>& operator -= (Type_Vector2<T> vec2)
	{
		this->x -= vec2.x;
		this->y -= vec2.y;
		return *this;
	}
	template<typename U>
	inline Type_Vector2<T>& operator -= (Type_Vector2<U> vec2)
	{
		this->x -= static_cast<vec2.x>;
		this->y -= static_cast<vec2.y>;
		return *this;
	}
	inline Type_Vector2<T>& operator *= (Type_Vector2<T> vec2)
	{
		this->x *= vec2.x;
		this->y *= vec2.y;
		return *this;
	}
	template<typename U>
	inline Type_Vector2<T>& operator *= (Type_Vector2<U> vec2)
	{
		this->x *= static_cast<vec2.x>;
		this->y *= static_cast<vec2.y>;
		return *this;
	}
	inline Type_Vector2<T>& operator /= (Type_Vector2<T> vec2)
	{
		this->x /= vec2.x;
		this->y /= vec2.y;
		return *this;
	}
	template<typename U>
	inline Type_Vector2<T>& operator /= (Type_Vector2<U> vec2)
	{
		this->x /= static_cast<vec2.x>;
		this->y /= static_cast<vec2.y>;
		return *this;
	}

	inline operator glm::vec2()
	{
		return glm::vec2(this->x, this->y);
	}
};