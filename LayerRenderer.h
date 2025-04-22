#pragma once

#include <vector>
#include <limits>

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Grid.h"  

struct LayerRenderer 
{
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::Uint8> pixelBuffer;
    sf::Sprite view_layer(Grid&, FieldType);
    LayerRenderer()
    {
        pixelBuffer.resize(FIELD_WIDTH * FIELD_HEIGHT * 4);
        texture.create(FIELD_WIDTH, FIELD_HEIGHT);
        float scaleX = static_cast<float>(WINDOW_WIDTH) / FIELD_WIDTH;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / FIELD_HEIGHT;
        sprite.setScale(scaleX, scaleY);
    }
};
