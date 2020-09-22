#pragma once

template <typename T>
struct vec2
{
	T x;
	T y;
	vec2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	bool is_inside(T x_min, T y_min, T x_max, T y_max)
	{
		return x >= x_min and x < x_max  // Ç°±Õºó¿ª
			and y >= x_min and y < y_max;
	}

	vec2<T> operator+(vec2<T> another)
	{
		return vec2<T>(this->x + another.x, this->y + another.y);
	}

	vec2<T> operator+=(vec2<T> another)
	{
		this->x += another.x;
		this->y += another.y;
		return *this;
	}
};