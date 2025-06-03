#include "LayerRenderer.h"

sf::Sprite LayerRenderer::view_layer(Grid& grid, FieldType layerType)
{
    double max_data = std::numeric_limits<double>::lowest();
    double min_data = std::numeric_limits<double>::max();

    for (int i = 1; i < FIELD_HEIGHT-1; i++)
    {
        for (int j = 1; j < FIELD_WIDTH-1; j++)
        {
            double data = grid.get_field_data(*grid.cells[j + i * grid.width], layerType);
            max_data = 20;// std::max(max_data, data);
            min_data = 0;// std::min(min_data, data);
            grid.maxx = max_data;
        }
    }

    for (int i = 1; i < FIELD_HEIGHT -1; i++)
    {
        for (int j = 1; j < FIELD_WIDTH -1; j++)
        {
            int pixelIndex = ((FIELD_HEIGHT - 1 - i) * FIELD_WIDTH + j) * 4;

            double data = grid.get_field_data(*grid.cells[j + i * grid.width], layerType);
            data = std::clamp(data, min_data, max_data);
            double dv = max_data - min_data;

            double r, g, b;
            if (data < (min_data + 0.25 * dv))
            {
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
            pixelBuffer[pixelIndex + 3] = static_cast<sf::Uint8>(255);
        }
    }

    texture.update(pixelBuffer.data());
    sprite.setTexture(texture);

    return sprite;
}

