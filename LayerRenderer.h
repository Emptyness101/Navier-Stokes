#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Grid.h"  

struct LayerRenderer 
{
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Sprite view_rho(const Grid& grid); 
};
