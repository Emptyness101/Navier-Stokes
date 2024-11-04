#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "Constants.h"
#include "vec2.h"
#include "Cell.h"
#include "Grid.h"
#include "Brush.h"
#include "LayerRenderer.h"

//TODO
/*
* формулы 
* посмотреть библиотеки для векторных вычислений, cpp boost (ublas)
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    Grid grid(FIELD_WIDTH, FIELD_HEIGHT);
    grid.initialize(0, 10, vec2(0, 0));

    LayerRenderer layer;
    FieldType current_layer = DEFAULT_FIELDTYPE;
    sf::Sprite current_view_layer = layer.view_layer(grid, current_layer);

    Brush brush(DEFAULT_BRUSH_RADIUS, DEFAULT_BRUSH_POWER);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                std::cout << "Window has been resized!" << std::endl;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                int mouse_cell_y = sf::Mouse::getPosition(window).y / PIXEL_CELL_WIDTH;
                int mouse_cell_x = sf::Mouse::getPosition(window).x / PIXEL_CELL_HEIGHT;
                brush.gauss_brush(grid, current_layer, mouse_cell_x, mouse_cell_y);
                layer.view_layer(grid, current_layer);
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    brush.brush_power = DEFAULT_BRUSH_POWER;
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                brush.brush_radius += event.mouseWheelScroll.delta;
                brush.brush_radius = std::max(1, brush.brush_radius);
            }
        }
        window.clear();
        window.draw(current_view_layer);
        window.display();
    }

    return 0;
}