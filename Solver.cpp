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

void Solver::advect(Grid& grid, float dt, float diffusion)
{
    auto new_cells = grid.cells;

    for (int y = 0; y < grid.height; ++y)
    {
        for (int x = 0; x < grid.width; ++x)
        {
            auto& cell = grid.cells[x + y * grid.width];
            if (dynamic_cast<Boundary*>(cell.get())) continue;

            vec2 phys_pos(
                cell->pos.x * PHYS_CELL_WIDTH,
                cell->pos.y * PHYS_CELL_HEIGHT
            );

            vec2 traced_pos = phys_pos - cell->u * dt;
            vec2 new_u = interpolate_velocity(traced_pos, grid);

            float decay = 1.0f / (1.0f + diffusion * dt);
            new_u = new_u * decay;

            auto new_cell = std::make_shared<Inner>(*std::static_pointer_cast<Inner>(cell));
            new_cell->u = new_u;
            new_cells[x + y * grid.width] = new_cell;
        }
    }

    grid.cells = std::move(new_cells);
    grid.set_neighbors();
}

vec2 Solver::interpolate_velocity(const vec2& phys_pos, Grid& grid)
{
    float x = phys_pos.x / PHYS_CELL_WIDTH;
    float y = phys_pos.y / PHYS_CELL_HEIGHT;

    float x1 = std::floor(x);
    float y1 = std::floor(y);
    float x2 = x1 + 1;
    float y2 = y1 + 1;

    auto clamp = [](float val, float minv, float maxv)
        {
            return std::max(minv, std::min(maxv, val));
        };

    auto get_cell = [&](float x, float y) -> Cell*
        {
            int ix = static_cast<int>(clamp(x, 0, grid.width - 1));
            int iy = static_cast<int>(clamp(y, 0, grid.height - 1));
            return grid.cells[ix + iy * grid.width].get();
        };

    Cell* q11 = get_cell(x1, y1);
    Cell* q12 = get_cell(x1, y2);
    Cell* q21 = get_cell(x2, y1);
    Cell* q22 = get_cell(x2, y2);

    float tx = (x - x1);
    float ty = (y - y1);

    vec2 f1 = q11->u * (1 - tx) + q21->u * tx;
    vec2 f2 = q12->u * (1 - tx) + q22->u * tx;

    return f1 * (1 - ty) + f2 * ty;
}

vec2 Solver::jacobiVelocity(const Grid& grid, size_t x, size_t y, vec2 B, float alpha, float beta)
{
    vec2 vU = B * -1.0, vD = B * -1.0, vR = B * -1.0, vL = B * -1.0;

    // Ïðîâåðÿåì ãðàíèöû è èçâëåêàåì ñêîðîñòü èç Cell
    auto get_velocity = [&](size_t x, size_t y) -> vec2
        {
            return grid.cells[y * grid.width + x]->u;
        };

    if (y > 0) vU = get_velocity(x, y - 1);
    if (y < grid.height - 1) vD = get_velocity(x, y + 1);
    if (x > 0) vL = get_velocity(x - 1, y);
    if (x < grid.width - 1) vR = get_velocity(x + 1, y);

    return (vU + vD + vL + vR + B * alpha) * (1.0 / beta);
}


void Solver::diffuse(Grid& newGrid, const Grid& oldGrid, float vDiffusion, float dt)
{
    float alpha = vDiffusion * vDiffusion / dt;
    float beta = 4.0 + alpha;

    for (size_t y = 0; y < oldGrid.height; ++y)
    {
        for (size_t x = 0; x < oldGrid.width; ++x)
        {
            vec2 B = oldGrid.cells[y * oldGrid.width + x]->u;
            newGrid.cells[y * newGrid.width + x]->u = jacobiVelocity(oldGrid, x, y, B, alpha, beta);
        }
    }
}


void Solver::computeDiffusion(Grid& grid, float dt)
{
    Grid tempGrid = grid;
    for (int i = 0; i < velocityIterations; i++)
    {
        diffuse(tempGrid, grid, velocityDiffusion, dt);
        std::swap(grid, tempGrid);
    }
}

float Solver::jacobiPressure(const Grid& grid, size_t x, size_t y, float B, float alpha, float beta) 
{
    float C = grid.cells[y * grid.width + x]->p;
    float xU = C, xD = C, xL = C, xR = C;

    auto get_pressure = [&](size_t x, size_t y) -> float {
        return grid.cells[y * grid.width + x]->p;
        };

    if (y > 0) xU = get_pressure(x, y - 1);
    if (y < grid.height - 1) xD = get_pressure(x, y + 1);
    if (x > 0) xL = get_pressure(x - 1, y);
    if (x < grid.width - 1) xR = get_pressure(x + 1, y);

    return (xU + xD + xL + xR + alpha * B) * (1.0f / beta);
}

float Solver::divergency(const Grid& grid, size_t x, size_t y) 
{
    vec2 uC = grid.cells[y * grid.width + x]->u;
    float x1 = -uC.x, x2 = -uC.x, y1 = -uC.y, y2 = -uC.y;

    auto get_velocity = [&](size_t x, size_t y) -> vec2 {
        return grid.cells[y * grid.width + x]->u;
        };

    if (x < grid.width - 1) x1 = get_velocity(x + 1, y).x;
    if (x > 0) x2 = get_velocity(x - 1, y).x;
    if (y < grid.height - 1) y1 = get_velocity(x, y + 1).y;
    if (y > 0) y2 = get_velocity(x, y - 1).y;

    return (x1 - x2 + y1 - y2) * 0.5f;
}

void Solver::computePressure(Grid& grid, float pressure, float dt) {
    Grid tempGrid = grid; // Копия для итераций

    for (int i = 0; i < pressureIterations; i++) {
        for (size_t y = 0; y < grid.height; ++y) {
            for (size_t x = 0; x < grid.width; ++x) {
                float div = divergency(grid, x, y);
                float alpha = -pressure * pressure;
                float beta = 4.0f;
                tempGrid.cells[y * grid.width + x]->p = jacobiPressure(grid, x, y, div, alpha, beta);
            }
        }
        std::swap(grid, tempGrid);
    }
}

vec2 Solver::gradient(const Grid& grid, size_t x, size_t y) {
    float C = grid.cells[y * grid.width + x]->p;
    float x1 = C, x2 = C, y1 = C, y2 = C;

    auto get_pressure = [&](size_t x, size_t y) -> float {
        return grid.cells[y * grid.width + x]->p;
        };

    if (x < grid.width - 1) x1 = get_pressure(x + 1, y);
    if (x > 0) x2 = get_pressure(x - 1, y);
    if (y < grid.height - 1) y1 = get_pressure(x, y + 1);
    if (y > 0) y2 = get_pressure(x, y - 1);

    return vec2((x1 - x2) * 0.5f, (y1 - y2) * 0.5f);
}

void Solver::project(Grid& grid) {
    for (size_t y = 0; y < grid.height; ++y) {
        for (size_t x = 0; x < grid.width; ++x) {
            vec2& u = grid.cells[y * grid.width + x]->u;
            u = u - gradient(grid, x, y);
        }
    }
}

float Solver::curl(const Grid& grid, size_t x, size_t y) {
    vec2 C = grid.cells[y * grid.width + x]->u;
    float x1 = -C.x, x2 = -C.x, y1 = -C.y, y2 = -C.y;

    auto get_velocity = [&](size_t x, size_t y) -> vec2 {
        return grid.cells[y * grid.width + x]->u;
        };

    if (x < grid.width - 1) x1 = get_velocity(x + 1, y).x;
    if (x > 0) x2 = get_velocity(x - 1, y).x;
    if (y < grid.height - 1) y1 = get_velocity(x, y + 1).y;
    if (y > 0) y2 = get_velocity(x, y - 1).y;

    return ((y1 - y2) - (x1 - x2)) * 0.5f;
}

vec2 Solver::absGradient(const std::vector<float>& vorticityField, size_t xSize, size_t ySize, size_t x, size_t y) {
    float C = vorticityField[y * xSize + x];
    float x1 = C, x2 = C, y1 = C, y2 = C;

    auto get_value = [&](size_t x, size_t y) -> float {
        return vorticityField[y * xSize + x];
        };

    if (x < xSize - 1) x1 = get_value(x + 1, y);
    if (x > 0) x2 = get_value(x - 1, y);
    if (y < ySize - 1) y1 = get_value(x, y + 1);
    if (y > 0) y2 = get_value(x, y - 1);

    return vec2((std::abs(x1) - std::abs(x2)) * 0.5f, (std::abs(y1) - std::abs(y2)) * 0.5f);
}

void Solver::computeVorticity(Grid& grid, std::vector<float>& vorticityField) {
    vorticityField.resize(grid.width * grid.height);

    for (size_t y = 0; y < grid.height; ++y) {
        for (size_t x = 0; x < grid.width; ++x) {
            vorticityField[y * grid.width + x] = curl(grid, x, y);
        }
    }
}

void Solver::applyVorticity(Grid& grid, const std::vector<float>& vorticityField, float vorticityStrength, float dt) {
    for (size_t y = 0; y < grid.height; ++y) {
        for (size_t x = 0; x < grid.width; ++x) {
            vec2 vGrad = absGradient(vorticityField, grid.width, grid.height, x, y);
            vGrad.y *= -1.0f;  

            float length = std::sqrt(vGrad.x * vGrad.x + vGrad.y * vGrad.y) + 1e-5f;
            vec2 vNorm = vGrad * (1.0f / length);

            vec2 vF = vNorm * vorticityField[y * grid.width + x] * vorticityStrength;
            grid.cells[y * grid.width + x]->u += vF * dt;
        }
    }
}








