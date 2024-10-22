#include "ColorView.h"
#include <limits>

sf::Sprite ColorView::view_rho(const Grid& grid) 
{
    int FIELD_WIDTH = grid.cells.size();
    int FIELD_HEIGHT = grid.cells[0].size();

    std::vector<sf::Uint8> pixelBuffer(FIELD_WIDTH * FIELD_HEIGHT * 4);
    texture.create(FIELD_WIDTH, FIELD_HEIGHT);

    sf::Uint8 alpha = 255;

    double max_data = std::numeric_limits<double>::lowest();
    double min_data = std::numeric_limits<double>::max();

    for (const auto& row : grid.cells) 
    {
        for (const auto& cell : row) 
        {
            double data = cell->rho;
            if (data > max_data) max_data = data;
            if (data < min_data) min_data = data;
        }
    }

    for (int i = 0; i < FIELD_HEIGHT; i++) 
    {
        for (int j = 0; j < FIELD_WIDTH; j++) 
        {
            int pixelIndex = (i * FIELD_WIDTH + j) * 4;
            double data = grid.cells[i][j]->rho;

            if (data < min_data) data = min_data;
            if (data > max_data) data = max_data;
            double dv = max_data - min_data;

            double r, g, b;
            if (data < (min_data + 0.25 * dv)) {
                r = 0;
                g = 4 * (data - min_data) / dv;
                b = 1;
            }
            else if (data < (min_data + 0.5 * dv)) 
            {
                r = 0;
                g = 1;
                b = 1 + 4 * (min_data + 0.25 * dv - data) / dv;
            }
            else if (data < (min_data + 0.75 * dv)) 
            {
                r = 4 * (data - min_data - 0.5 * dv) / dv;
                g = 1;
                b = 0;
            }
            else 
            {
                r = 1;
                g = 1 + 4 * (min_data + 0.75 * dv - data) / dv;
                b = 0;
            }

            pixelBuffer[pixelIndex] = static_cast<sf::Uint8>(r * 255);
            pixelBuffer[pixelIndex + 1] = static_cast<sf::Uint8>(g * 255);
            pixelBuffer[pixelIndex + 2] = static_cast<sf::Uint8>(b * 255);
            pixelBuffer[pixelIndex + 3] = alpha;
        }
    }

    texture.update(pixelBuffer.data());
    sprite.setTexture(texture);
    return sprite;
}
