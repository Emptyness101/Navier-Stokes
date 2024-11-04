#include "Grid.h"

Grid::Grid(int width, int height)
    : width(width), height(height), cells(width * height, nullptr) {}

void Grid::initialize(double initial_p, double initial_rho, vec2 velocity) 
{
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (i == 0 || j == 0 || j == (width - 1) || i == (height - 1)) 
            {
                cells[j + i * width] = std::make_shared<Boundary>(vec2(j, i), velocity, initial_p, initial_rho);
            }
            else 
            {
                cells[j + i * width] = std::make_shared<Inner>(vec2(j, i), velocity, initial_p, initial_rho);
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
            auto& currentCell = cells[j + i * width];
            // left neighbor
            if (j > 0) currentCell->neighbors[0] = cells[j - 1 + i * width].get();
            // upper neighbor
            if (i < height - 1) currentCell->neighbors[1] = cells[j + (i+1) * width].get();
            // right neighbor 
            if (j < width - 1) currentCell->neighbors[2] = cells[j + 1 + i * width].get();
            // lower neighbor
            if (i > 0) currentCell->neighbors[3] = cells[j + (i - 1) * width].get();
        }
    }
}

void Grid::print_cell_info(int i, int j) const
{
    std::cout << "Cell " << "(" << cells[i + j * width]->pos.x << ", " << cells[i + j * width]->pos.y << ") info { ";
    if (dynamic_cast<Boundary*>(cells[i + j * width].get()))
    {
        std::cout << "| Boundary";
    }
    else 
    {
        std::cout << "| Inner";
    }
    std::cout << "| rho: " << cells[i + j * width]->rho << "| vx: " << cells[i + j * width]->u.x << "| vy: " << cells[i + j * width]->u.y << "| }";
    std::cout << std::endl;
}

void Grid::print_cell_neighbors(int i, int j) const 
{
    if (i >= 0 && i < height && j >= 0 && j < width) 
    {
        std::vector<Cell*> neighbors = cells[i + j * width]->neighbors;
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

void Grid::to_file_field(std::string outputpath , FieldType type) const
{
    std::ofstream output;          
    output.open(outputpath);
    if (output.is_open())
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int pixelIndex = ((height - 1 - i) * width + j);

                switch (type) {
                case Velocity:
                    output << "{" << cells[pixelIndex]->u.x << "," << cells[pixelIndex]->u.y << "} ";
                    break;
                case XVelocity:
                    output << cells[pixelIndex]->u.x << " ";
                    break;
                case YVelocity:
                    output << cells[pixelIndex]->u.y << " ";
                    break;
                case Pressure:
                    output << cells[pixelIndex]->p << " ";
                    break;
                case Density:
                    output << cells[pixelIndex]->rho << " ";
                    break;
                default:
                    break;
                }
            }
            output << std::endl;
        }
    }
}



