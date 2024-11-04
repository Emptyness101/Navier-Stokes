#pragma once

#include "Constants.h"
#include "cell.h" 
#include "vec2.h" 
#include "grid.h" 

struct DifferentialOperators
{
	vec2 grad(Cell& cell, FieldType);
	double div(Cell& cell, FieldType);
	double rot(Cell& cell, FieldType);
	double lap(Cell& cell, FieldType);
};

