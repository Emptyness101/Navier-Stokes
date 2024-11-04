#pragma once
#define _USE_MATH_DEFINES

#include <cmath>

#include "SFML/Graphics.hpp"

#include "Constants.h"
#include "Grid.h"

struct Brush
{
	int brush_radius;
	float brush_power;

	Brush(int brush_radius, float brush_power);
	void gauss_brush(Grid& grid_data, FieldType current_layer, float mouse_cell_x, float mouse_cell_y);
};

