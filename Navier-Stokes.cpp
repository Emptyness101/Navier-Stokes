#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include "vec2.h"
#include "Cell.h"
/*
  В этом файле определены классы Cell, Boundary и Inner, которые представляют ячейки сетки.
  Каждый класс содержит информацию о позиции, скорости, давлении, плотности и соседних ячейках
*/
#include "Grid.h"
/*
    В этом файле определён класс Grid, который предоставляет интерфейс для управления ячейками сетки.
    Класс включает методы для инициализации массива ячеек, заполнения их данными, а также
    вывода информации о каждой ячейке.

    Текущая реализация:
    Конструктор: Grid(int width, int height) : width(width), height(height)

    Метод: initialize(double initial_p, double initial_rho, vec2 velocity) 
    Описание: Инициализация полей давления, плотности и скорости. В каждой ячейке значения равны.

    Метод: initialize(vec2 velocity_left, double p_left, double rho_left,
                      vec2 velocity_right, double p_right, double rho_right)
    Описание: Инициализация полей давления, плотности и скорости. В левой половине сетки ячейки имеют одно значение, а в правой — другое.

    Метод: set_neighbors()
    Описание: Вспомогательный метод для методов инициализации, заполняет поле соседи у каждой ячейки.
    Массив{верх,низ,лево,право}.

    Метод: print_cell_info(int i, int j) 
    Описание: Вывод в консоль информации о ячейке

    Метод: print_cell_neighbors(int i, int j) 
    Описание: Вывод в консоль информации о соседях ячейки
*/
#include "LayerRenderer.h"
/* 
    В этом файле определён класс ColorView, который отвечает за визуализацию данных ячеек сетки.
    Класс предоставляет методы для создания текстур и спрайтов на основе информации из ячейки

    Текущая реализация:
    Метод: sf::Sprite view_rho(const Grid& grid)
    Описание: Визуализация поля плотности
*/

// -----------------------------------------
//                                           
//          НАЧАЛЬНЫЕ ДАННЫЕ
//  
// -----------------------------------------

// Ширина расчетной области
const int WIDTH  = 500;
// Высота расчетной области
const int HEIGHT = 500;

//TODO
/*
* формулы 
* grid::setforce vector <vec2> f ---> grid 
* load from file
* mouse gauss kernel (в центре с радиусом задаем мышкой) и размываем по гауссу в сторону движения мышки
* посмотреть библиотеки для векторных вычислений, cpp boost
* const to h.file
* мастабирвоание ячеек
* 
* const:
* физ длина ширина
* колво пикселей
* кол-во ячеек верх низ
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    //Инициализация расчетной сетки 
    Grid grid(WIDTH, HEIGHT);
    grid.initialize(0, 10, vec2(0, 0));

    //Визуализация поля
    LayerRenderer layer;
    for (int i = 0 ; i < grid.height / 2; i++)
        for (int j = 0; j < grid.width; j++)
            grid.cells[i*grid.width + j]->rho = i + j;

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

