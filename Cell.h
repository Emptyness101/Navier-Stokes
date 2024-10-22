#pragma once

#include <vector>
#include "vec2.h"  

struct Cell 
{
    vec2 pos;
    vec2 u;
    double p;
    double rho;

    std::vector<Cell*> neighbors{ nullptr, nullptr ,nullptr ,nullptr };

    Cell(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0);
    virtual ~Cell();

    std::vector<Cell*> getNeighbors() const;
};

struct Boundary : Cell 
{
    Boundary(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0);
};

struct Inner : Cell 
{
    Inner(vec2 pos = vec2(), vec2 u = vec2(), double p = 0.0, double rho = 0.0);
};
