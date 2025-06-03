#pragma once

#include <vector>
#include <cmath>
#include "vec2.h"  
#include "../Constants.h"

struct Cell
{
    vec2 pos;
    vec2 u;
    double p;
    double rho;

    vec2 dye;

    vec2 grad_p;
    double div_u;
    double rot_u;

    double magnitude_u;
    void update_magnitude_u() {magnitude_u = std::hypot(u.x, u.y);}

    std::vector<Cell*> neighbors{ 4, this };

    Cell(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0, vec2 grad_p = vec2(), double div_u = 0, double rot_u = 0);
    virtual ~Cell();

    virtual void calc_grad_p() = 0;
    virtual void calc_div_u() = 0;
    virtual void calc_rot_u() = 0;
};

struct Boundary : Cell
{
    Boundary(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0, vec2 grad_p = vec2(), double div_u = 0, double rot_u = 0);

    void calc_grad_p() override
    {
        grad_p.x = (neighbors[2]->p - neighbors[0]->p) / (PHYS_CELL_WIDTH);
        grad_p.y = (neighbors[1]->p - neighbors[3]->p) / (PHYS_CELL_HEIGHT);
    }
    void calc_div_u() override
    {
        div_u = (neighbors[2]->u.x - neighbors[0]->u.x) / (PHYS_CELL_WIDTH) + 
                (neighbors[1]->u.y - neighbors[3]->u.y) / (PHYS_CELL_HEIGHT);
    }
    void calc_rot_u() override
    {
        rot_u = (neighbors[1]->u.y - neighbors[3]->u.y) / (PHYS_CELL_HEIGHT) -
                (neighbors[2]->u.x - neighbors[0]->u.x) / (PHYS_CELL_WIDTH);
    }
};

struct Inner : Cell
{
    Inner(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0, vec2 grad_p = vec2(), double div_u = 0, double rot_u = 0);

    void calc_grad_p() override
    {
        grad_p.x = (neighbors[2]->p - neighbors[0]->p) / (2 * PHYS_CELL_WIDTH);
        grad_p.y = (neighbors[1]->p - neighbors[3]->p) / (2 * PHYS_CELL_HEIGHT);
    }
    void calc_div_u() override
    {
        div_u = (neighbors[2]->u.x - neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH) + 
                (neighbors[1]->u.y - neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT);
    }
    void calc_rot_u() override
    {
        rot_u = (neighbors[1]->u.y - neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT)-
                (neighbors[2]->u.x - neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH);
    }
};

