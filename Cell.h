#pragma once

#include <vector>
#include "vec2.h"  
#include "Constants.h"

struct Cell
{
    vec2 pos;
    vec2 u;
    double p;
    double rho;
    vec2 grad;
    std::vector<Cell*> neighbors{ 4, nullptr };

    Cell(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0, vec2 grad = vec2());
    virtual ~Cell();

    virtual void calcgrad() = 0; 
};

struct Boundary : Cell
{
    Boundary(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0, vec2 grad = vec2());

    void calcgrad() override
    {
        if (neighbors[0] == nullptr && neighbors[1] != nullptr)
        {
            grad.x = (u.x - neighbors[2]->u.x) / (2 * PHYS_CELL_WIDTH);
            grad.y = (u.y - neighbors[1]->u.y) / (2 * PHYS_CELL_HEIGHT);
            return;
        }
        if (neighbors[1] == nullptr && neighbors[2] != nullptr)
        {
            grad.x = (u.x - neighbors[2]->u.x) / (2 * PHYS_CELL_WIDTH);
            grad.y = (u.y - neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT);
            return;
        }
        if (neighbors[2] == nullptr && neighbors[3] != nullptr)
        {
            grad.x = (u.x - neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH);
            grad.y = (u.y - neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT);
            return;
        }
        if (neighbors[3] == nullptr && neighbors[0] != nullptr)
        {
            grad.x = (u.x - neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH);
            grad.y = (u.y - neighbors[1]->u.y) / (2 * PHYS_CELL_HEIGHT);
            return;
        }
    }
};

struct Inner : Cell
{
    Inner(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0, vec2 grad = vec2());

    void calcgrad() override
    {
        grad.x = (neighbors[2]->u.x - neighbors[0]->u.x) / (2 * PHYS_CELL_WIDTH);
        grad.y = (neighbors[1]->u.y - neighbors[3]->u.y) / (2 * PHYS_CELL_HEIGHT);
    }
};

