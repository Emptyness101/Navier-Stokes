#pragma once

#include "Constants.h"
#include "grid.h"

struct Solver
{
    void velocity_attenuation(Grid& grid);
    void set_force(Grid& grid, int cell_index, vec2 force, int radius);

    void advect(Grid& grid, float dt, float diffusion);
    vec2 interpolate_velocity(const vec2& phys_pos, Grid& grid);

    vec2 jacobiVelocity(const Grid& grid, size_t x, size_t y, vec2 B, float alpha, float beta);
    void diffuse(Grid& newGrid, const Grid& oldGrid, float vDiffusion, float dt);
    void computeDiffusion(Grid& grid, float dt);

    float jacobiPressure(const Grid& grid, size_t x, size_t y, float B, float alpha, float beta);
    float divergency(const Grid& grid, size_t x, size_t y);
    void computePressure(Grid& grid, float pressure, float dt);
    vec2 gradient(const Grid& grid, size_t x, size_t y);
    void project(Grid& grid);

    float curl(const Grid& grid, size_t x, size_t y);
    vec2 absGradient(const std::vector<float>& vorticityField, size_t xSize, size_t ySize, size_t x, size_t y);
    void computeVorticity(Grid& grid, std::vector<float>& vorticityField);
    void applyVorticity(Grid& grid, const std::vector<float>& vorticityField, float vorticityStrength, float dt);

};