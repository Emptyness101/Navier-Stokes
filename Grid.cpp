#include "Grid.h"

Grid::Grid(int width, int height) : width(width), height(height) 
{
    cells.resize(height, std::vector<std::shared_ptr<Cell>>(width, nullptr));
}

void Grid::initialize(double initial_p, double initial_rho, vec2 velocity) 
{

    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) 
            {
                cells[i][j] = std::make_shared<Boundary>(vec2(i, j), velocity, initial_p, initial_rho);
            }
            else 
            {
                cells[i][j] = std::make_shared<Inner>(vec2(i, j), velocity, initial_p, initial_rho);
            }
        }
    }
    set_neighbors();
}

void Grid::initialize(vec2 velocity_left, double p_left, double rho_left,
    vec2 velocity_right, double p_right, double rho_right) 
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (j < width / 2) 
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) 
                {
                    cells[i][j] = std::make_shared<Boundary>(vec2(i, j), velocity_left, p_left, rho_left);
                }
                else 
                {
                    cells[i][j] = std::make_shared<Inner>(vec2(i, j), velocity_left, p_left, rho_left);
                }
            }
            else 
            {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) 
                {
                    cells[i][j] = std::make_shared<Boundary>(vec2(i, j), velocity_right, p_right, rho_right);
                }
                else 
                {
                    cells[i][j] = std::make_shared<Inner>(vec2(i, j), velocity_right, p_right, rho_right);
                }
            }
        }
    }
    set_neighbors();
}

void Grid::set_neighbors() 
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            auto& currentCell = cells[i][j];
            // верхний сосед
            if (i > 0) currentCell->neighbors[0] = cells[i - 1][j].get();
            // нижний сосед
            if (i < height - 1) currentCell->neighbors[1] = cells[i + 1][j].get();
            // левый сосед 
            if (j > 0) currentCell->neighbors[2] = cells[i][j - 1].get();
            // правый сосед 
            if (j < width - 1) currentCell->neighbors[3] = cells[i][j + 1].get();
        }
    }
}

void Grid::print_cell_info(int i, int j) const 
{
    std::cout << "Cell " << "(" << cells[i][j]->pos.x << ", " << cells[i][j]->pos.y << ") info { ";
    if (dynamic_cast<Boundary*>(cells[i][j].get())) 
    {
        std::cout << "| Boundary";
    }
    else 
    {
        std::cout << "| Inner";
    }
    std::cout << "| rho: " << cells[i][j]->rho << "| vx: " << cells[i][j]->u.x << "| vy: " << cells[i][j]->u.y << "| }";
    std::cout << std::endl;
}

void Grid::print_cell_neighbors(int i, int j) const 
{
    if (i >= 0 && i < height && j >= 0 && j < width) 
    {
        std::vector<Cell*> neighbors = cells[i][j]->getNeighbors();
        std::cout << "Cell " << "(" << i << ", " << j << ") neighbors { ";
        for (Cell* neighbor : neighbors) 
        {
            if (neighbor) 
            {
                std::cout << "(" << neighbor->pos.x << ", " << neighbor->pos.y << ") ";
            }
            else 
            {
                std::cout << "(null) ";
            }
        }
        std::cout << "}" << std::endl;
    }
}
