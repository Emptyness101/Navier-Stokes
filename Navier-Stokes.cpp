#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include "vec2.h"
#include "Constants.h"

#include "Cell.h"
#include "Grid.h"
#include "LayerRenderer.h"


// -----------------------------------------
//                                           
//          НАЧАЛЬНЫЕ ДАННЫЕ
//  
// -----------------------------------------

//TODO
/*
* формулы 
* grid::setforce vector <vec2> f ---> grid 
* load from file
* mouse gauss kernel (в центре с радиусом задаем мышкой) и размываем по гауссу в сторону движения мышки
* посмотреть библиотеки для векторных вычислений, cpp boost
* 
* const:
* физ длина ширина
* колво пикселей
* кол-во ячеек верх низ
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    //Инициализация расчетной сетки 
    Grid grid(FIELD_WIDTH, FIELD_HEIGHT);
    grid.initialize(0, 10, vec2(0, 0));

    //Визуализация поля
    LayerRenderer layer;
    for (int i = 0 ; i < grid.height / 2; i++)
        for (int j = 0; j < grid.width; j++)
            grid.cells[i*grid.width + j]->u.x = j;

    sf::Sprite current_view_mode = layer.view_rho(grid);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(current_view_mode);
        window.display();
    }

    return 0;
}

