#pragma once

#include "Constants.h"
#include "cell.h" 
#include "vec2.h" 
#include "grid.h" 

struct DifferentialOperators
{
	void grad_v(Cell& cell);
	vec2 grad_p(Cell& cell);
	vec2 grad_d(Cell& cell);
	double div_v(Cell& cell);
	double rot_v(Cell& cell);
	double lap_v(Cell& cell);
	double lap_p(Cell& cell);
};

