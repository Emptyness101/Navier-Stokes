#pragma once
struct vec2
{
	double x, y;
	vec2(double, double);
	vec2();
	vec2 operator-(vec2);
	vec2 operator+(vec2);
	vec2 operator*(double);
	vec2& operator+=(vec2);
};
