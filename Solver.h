#pragma once

#include "Constants.h"
#include "grid.h"

struct Solver
{
    void velocity_attenuation(Grid& grid);
    void set_force(Grid& grid, int cell_index, vec2 force, int radius);
};
