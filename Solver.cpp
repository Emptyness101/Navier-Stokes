#include "Solver.h"

void Solver::velocity_attenuation(Grid& grid)
{
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        for (int j = 0; j < FIELD_WIDTH; j++)
        {
            int pixelIndex = ((FIELD_HEIGHT - 1 - i) * FIELD_WIDTH + j);

            grid.cells[pixelIndex]->u *= ATTENUATION_COEFFICIENT;

            if (std::abs(grid.cells[pixelIndex]->u.x) < THRESHOLD_ALIGNMENT)
            {
                grid.cells[pixelIndex]->u.x = 0.0;
            }
            if (std::abs(grid.cells[pixelIndex]->u.y) < THRESHOLD_ALIGNMENT)
            {
                grid.cells[pixelIndex]->u.y = 0.0;
            }
        }
    }
}

void Solver::set_force(Grid& grid, int cell_index, vec2 force, int radius)
{
    int center_x = cell_index % grid.width;
    int center_y = cell_index / grid.width;

    float radius_squared = radius * radius;

    for (int y = std::max(0, center_y - radius);
        y <= std::min(grid.height - 1, center_y + radius); y++)
    {
        for (int x = std::max(0, center_x - radius);
            x <= std::min(grid.width - 1, center_x + radius); x++)
        {
            float dx = x - center_x;
            float dy = y - center_y;
            float distance_squared = dx * dx + dy * dy;

            if (distance_squared <= radius_squared)
            {
                int index = y * grid.width + x;
                grid.cells[index]->u += force * DELTA_TIME;
            }
        }
    }
}
