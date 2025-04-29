#include "Brush.h"

Brush::Brush(int brush_radius, float brush_power) : radius(brush_radius), power(brush_power) {};

vec2 Brush::gauss_brush(float current_mouse_cell_x, float current_mouse_cell_y,
                        float start_mouse_cell_x, float start_mouse_cell_y)
{
    float dx = current_mouse_cell_x - start_mouse_cell_x;
    float dy = current_mouse_cell_y - start_mouse_cell_y;
    float distance = dx * dx + dy * dy;
    float sigma = radius / 2.0;
    vec2 force = vec2(0, 0);

    vec2 impulse = vec2(dx, dy);

    std::cout << impulse.x << " " << impulse.y << std::endl;

    //float weight = 1 / (sigma * sqrt(2 * M_PI)) * std::exp(-distance / (2 * sigma * sigma));

    force = impulse * power;

    power = 100;//std::max(0.f, power - BRUSH_ATTENUATION_RATE);

    return force;
}