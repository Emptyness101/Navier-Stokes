#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include "vec2.h"
#include "Constants.h"

#include "Cell.h"
#include "Grid.h"
#include "LayerRenderer.h"

//TODO
/*
* формулы 
* grid::setforce vector <vec2> f ---> grid 
* load from file
* посмотреть библиотеки для векторных вычислений, cpp boost
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    Grid grid(FIELD_WIDTH, FIELD_HEIGHT);
    grid.initialize(0, 10, vec2(0, 0));

    LayerRenderer layer;
    FieldType current_layer = DEFAULT_FIELDTYPE;
    sf::Sprite current_view_layer = layer.view_layer(grid, current_layer);

    int brush_radius  = DEFAULT_BRUSH_RADIUS;
    float brush_power = DEFAULT_BRUSH_POWER;

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
                int mouse_cell_y = sf::Mouse::getPosition(window).y / CELL_WIDTH;
                int mouse_cell_x = sf::Mouse::getPosition(window).x / CELL_HEIGHT;

                float sigma = brush_radius / 2.0;

                for (int dy = -brush_radius; dy <= brush_radius; dy++)
                {
                    for (int dx = -brush_radius; dx <= brush_radius; dx++)
                    {
                        int y = mouse_cell_y + dy;
                        int x = mouse_cell_x + dx;
                        float distance = dx * dx + dy * dy;

                        if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) continue;

                        if (distance <= brush_radius * brush_radius)
                        {
                            float weight = std::exp(-distance / (2 * sigma * sigma)); // 1/sigma*sqrt(6.28) useless!
                            int cell_index = (FIELD_HEIGHT - 1 - y) * FIELD_WIDTH + x;
                            layer.get_layer_data(*grid.cells[cell_index], current_layer) += brush_power * weight;
                        }
                    }
                }
                layer.view_layer(grid, current_layer);
                brush_power = std::max(0.f, brush_power - BRUSH_ATTENUATION_RATE);
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    brush_power = DEFAULT_BRUSH_POWER;
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                brush_radius += event.mouseWheelScroll.delta;
                brush_radius = std::max(0, brush_radius); // BUG: if radius is 0 then infinite paint 
            }
        }
        window.clear();
        window.draw(current_view_layer);
        window.display();
    }

    return 0;
}

