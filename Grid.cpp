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
                cells[j + i * width] = std::make_shared<Boundary>(vec2(j, i), velocity, initial_p, initial_rho, vec2(0,0), 0, 0);
            }
            else 
            {
                cells[j + i * width] = std::make_shared<Inner>(vec2(j, i), velocity, initial_p, initial_rho, vec2(0, 0), 0, 0);
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
            // Left neighbor
            if (j > 0) currentCell->neighbors[0] = cells[j - 1 + i * width].get();
            // Upper neighbor
            if (i < height - 1) currentCell->neighbors[1] = cells[j + (i+1) * width].get();
            // Right neighbor 
            if (j < width - 1) currentCell->neighbors[2] = cells[j + 1 + i * width].get();
            // Lower neighbor
            if (i > 0) currentCell->neighbors[3] = cells[j + (i - 1) * width].get();
        }
    }
}

double& Grid::get_field_data(Cell& cell, FieldType field_type)
{
    switch (field_type)
    {
    case Pressure:
        return cell.p;
    case Density:
        return cell.rho;
    case Velocity:
        cell.update_magnitude_u();
        return cell.magnitude_u;
    case XVelocity:
        return cell.u.x;
    case YVelocity:
        return cell.u.y;
    default:
        throw std::invalid_argument("layer type error");
    }
}

void Grid::file_set_force(std::string input_path, FieldType input_data_type)
{
    std::ifstream input(input_path); 

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixelIndex = ((height - 1 - i) * width + j);
            char openBrace, comma, closeBrace;
            switch (input_data_type) {
            case Velocity:
                input >> openBrace >> cells[pixelIndex]->u.x >> comma >> cells[pixelIndex]->u.y >> closeBrace;
                break;
            case XVelocity:
                input >> cells[pixelIndex]->u.x;
                break;
            case YVelocity:
                input >> cells[pixelIndex]->u.y;
                break;
            case Pressure:
                input >> cells[pixelIndex]->p;
                break;
            case Density:
                input >> cells[pixelIndex]->rho;
                break;
            default:
                break;
            }
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