#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Cell.h"  
#include "vec2.h"  

struct Grid 
{
    int width, height;
    std::vector<std::shared_ptr<Cell>> cells;

    Grid(int width, int height);

    void initialize(double initial_p, double initial_rho, vec2 velocity);

    void set_neighbors();
    void print_cell_info(int i, int j) const;
    void print_cell_neighbors(int i, int j) const;
};
