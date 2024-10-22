#include "Cell.h"

Cell::Cell(vec2 pos, vec2 u, double p, double rho)
    : pos(pos), u(u), p(p), rho(rho) {}

Cell::~Cell() = default;

std::vector<Cell*> Cell::getNeighbors() const 
{
    return neighbors;
}

Boundary::Boundary(vec2 pos, vec2 u, double p, double rho)
    : Cell(pos, u, p, rho) {}

Inner::Inner(vec2 pos, vec2 u, double p, double rho)
    : Cell(pos, u, p, rho) {}
