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
#include "DifferentialOperators.h"
//TODO
/*
* формулы 
* посмотреть библиотеки для векторных вычислений, cpp boost (ublas)
*/

/*
* для внешних добавить поле направление 0 1 2 3 разные разностные схемы для каждой грани 
* в cell поле для div grad и тд
* в целл есть ро и град тогда из грида берем ро и кладем в град (который в целл)
* форс кисти возращает вектор!!!
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    Grid grid(FIELD_WIDTH, FIELD_HEIGHT);
    grid.initialize(0, 10, vec2(0, 0));
    DifferentialOperators dop;
    
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        for (int j = 0; j < FIELD_WIDTH; j++)
        {
            int pixelIndex = ((FIELD_HEIGHT - 1 - i) * FIELD_WIDTH + j);

            grid.cells[pixelIndex]->rho = 50;

        }
    }

    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        for (int j = FIELD_WIDTH/2; j < FIELD_WIDTH; j++)
        {
            int pixelIndex = ((FIELD_HEIGHT - 1 - i) * FIELD_WIDTH + j);

            grid.cells[pixelIndex]->rho = 100;

        }
    }



    grid.to_file_field("tets.txt", Density);
    std::cout << grid.cells[((FIELD_HEIGHT - 1 - FIELD_HEIGHT/2) * FIELD_WIDTH + FIELD_WIDTH/2)]->rho;

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
                    brush.power = DEFAULT_BRUSH_POWER;
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                brush.radius += event.mouseWheelScroll.delta;
                brush.radius = std::max(1, brush.radius);
            }
        }
        window.clear();
        window.draw(current_view_layer);
        window.display();
    }

    return 0;
}