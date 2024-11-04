#include "Brush.h"

Brush::Brush(int brush_radius, float brush_power) : brush_radius(brush_radius), brush_power(brush_power) {};

void Brush::gauss_brush(Grid& grid_data, FieldType current_layer, float mouse_cell_x, float mouse_cell_y)
{
    float sigma = brush_radius / 2.0;

    for (int dy = -brush_radius; dy <= brush_radius; dy++)
    {
        for (int dx = -brush_radius; dx <= brush_radius; dx++)
        {
            int y = mouse_cell_y + dy;
            int x = mouse_cell_x + dx;
            float distance = dx * dx + dy * dy;

            if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) continue;

            if (distance <= brush_radius * brush_radius)
            {
                float weight = 1 / (sigma * sqrt(2 * M_PI)) * std::exp(-distance / (2 * sigma * sigma));
                int cell_index = (FIELD_HEIGHT - 1 - y) * FIELD_WIDTH + x;
                grid_data.get_field_data(*grid_data.cells[cell_index], current_layer) += brush_power * weight;
            }
        }
    }
    brush_power = std::max(0.f, brush_power - BRUSH_ATTENUATION_RATE);
}