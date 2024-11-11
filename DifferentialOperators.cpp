#include "DifferentialOperators.h"

void DifferentialOperators::grad_v(Cell& cell)
{
	cell.grad.x = (cell.neighbors[2]->u.x - cell.neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH);
	cell.grad.y = (cell.neighbors[1]->u.y - cell.neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT);
}

vec2 DifferentialOperators::grad_p(Cell& cell)
{
	vec2 result;
	result.x = (cell.neighbors[2]->p - cell.neighbors[0]->p) / (2 * PHYS_CELL_WIDTH);
	result.y = (cell.neighbors[1]->p - cell.neighbors[3]->p) / (2 * PHYS_CELL_HEIGHT);
	return result;
}

vec2 DifferentialOperators::grad_d(Cell& cell)
{
	vec2 result;
	result.x = (cell.neighbors[2]->rho - cell.neighbors[0]->rho) / (2 * PHYS_CELL_WIDTH);
	result.y = (cell.neighbors[1]->rho - cell.neighbors[3]->rho) / (2 * PHYS_CELL_HEIGHT);
	return result;
}

double DifferentialOperators::div_v(Cell& cell)
{
	return (cell.neighbors[2]->u.x - cell.neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH) +
		   (cell.neighbors[1]->u.y - cell.neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT);
}

double DifferentialOperators::rot_v(Cell& cell)
{
	return (cell.neighbors[1]->u.y - cell.neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT) -
		   (cell.neighbors[2]->u.x - cell.neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH);
}

double DifferentialOperators::lap_v(Cell& cell)
{
	return (cell.neighbors[2]->u.x - 2 * cell.u.x + cell.neighbors[0]->u.x) / (PHYS_CELL_WIDTH * PHYS_CELL_WIDTH) +
		   (cell.neighbors[1]->u.y - 2 * cell.u.y + cell.neighbors[3]->u.y) / (PHYS_CELL_HEIGHT * PHYS_CELL_HEIGHT);
}

double DifferentialOperators::lap_p(Cell& cell)
{
	return (cell.neighbors[2]->p - 2 * cell.p + cell.neighbors[0]->p) / (PHYS_CELL_WIDTH * PHYS_CELL_WIDTH) +
		   (cell.neighbors[1]->p - 2 * cell.p + cell.neighbors[3]->p) / (PHYS_CELL_HEIGHT * PHYS_CELL_HEIGHT);
}