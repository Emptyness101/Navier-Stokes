#pragma once
#define _USE_MATH_DEFINES

#include <cmath>

#include "SFML/Graphics.hpp"

#include "../Constants.h"
#include "Grid.h"

struct Brush
{
	int radius;
	float power;

	Brush(int radius, float power);
	vec2 gauss_brush(float current_mouse_cell_x, float current_mouse_cell_y,
		float start_mouse_cell_x, float start_mouse_cell_y);
};

