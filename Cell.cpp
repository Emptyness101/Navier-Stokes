#include "Cell.h"

Cell::Cell(vec2 pos, vec2 u, double p, double rho, vec2 grad_p, double div_u, double rot_u)
    : pos(pos), u(u), p(p), rho(rho), grad_p(grad_p), div_u(div_u), rot_u(rot_u) {}

Cell::~Cell() = default;

Boundary::Boundary(vec2 pos, vec2 u, double p, double rho, vec2 grad_p, double div_u, double rot_u)
    : Cell(pos, u, p, rho, grad_p, div_u, rot_u) {}

Inner::Inner(vec2 pos, vec2 u, double p, double rho, vec2 grad_p, double div_u, double rot_u)
    : Cell(pos, u, p, rho, grad_p, div_u, rot_u) {}
