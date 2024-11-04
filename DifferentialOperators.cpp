#include "DifferentialOperators.h"

vec2 DifferentialOperators::grad(Cell& cell, FieldType data_type)
{
	vec2 result;
	switch (data_type)
	{
	case XVelocity:
		result.x = (cell.neighbors[2]->rho - cell.neighbors[2]->rho) / (2 * PHYS_CELL_WIDTH);
		result.y = (cell.neighbors[1]->rho - cell.neighbors[3]->rho) / (2 * PHYS_CELL_HEIGHT);
		break;
	case YVelocity:
		break;
	case Pressure:
		break;
	case Density:
		break;
	default:
		break;
	}
	return result;
}
double DifferentialOperators::div(Cell& cell, FieldType data_type)
{

}
double DifferentialOperators::rot(Cell& cell, FieldType data_type)
{

}
double DifferentialOperators::lap(Cell& cell, FieldType data_type)
{

}