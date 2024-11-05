#include "Brush.h"

Brush::Brush(int brush_radius, float brush_power) : radius(brush_radius), power(brush_power) {};

void Brush::gauss_brush(Grid& grid_data, FieldType current_layer, float mouse_cell_x, float mouse_cell_y)
{
    float sigma = radius / 2.0;

    for (int dy = -radius; dy <= radius; dy++)
    {
        for (int dx = -radius; dx <= radius; dx++)
        {
            int y = mouse_cell_y + dy;
            int x = mouse_cell_x + dx;
            float distance = dx * dx + dy * dy;

            if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) continue;

            if (distance <= radius * radius)
            {
                float weight = 1 / (sigma * sqrt(2 * M_PI)) * std::exp(-distance / (2 * sigma * sigma));
                int cell_index = (FIELD_HEIGHT - 1 - y) * FIELD_WIDTH + x;
                grid_data.get_field_data(*grid_data.cells[cell_index], current_layer) += power * weight;
            }
        }
    }
    power = std::max(0.f, power - BRUSH_ATTENUATION_RATE);
}