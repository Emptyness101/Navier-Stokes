#include "Cell.h"

Cell::Cell(vec2 pos, vec2 u, double p, double rho, vec2 grad)
    : pos(pos), u(u), p(p), rho(rho), grad(grad) {}

Cell::~Cell() = default;

Boundary::Boundary(vec2 pos, vec2 u, double p, double rho, vec2 grad)
    : Cell(pos, u, p, rho, grad) {}

Inner::Inner(vec2 pos, vec2 u, double p, double rho, vec2 grad)
    : Cell(pos, u, p, rho, grad) {}
