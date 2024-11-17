#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Constants.h"
#include "Cell.h"  
#include "vec2.h" 

struct Grid 
{
    int width, height;
    std::vector<std::shared_ptr<Cell>> cells;

    Grid(int width, int height);

    void initialize(double initial_p, double initial_rho, vec2 velocity);

    void set_neighbors();
    void print_cell_info(int, int) const;
    void print_cell_neighbors(int, int) const;
    void to_file_field(std::string, FieldType) const;
    void file_set_force(std::string, FieldType);
    double& get_field_data(Cell& cell, FieldType layerType);
};
