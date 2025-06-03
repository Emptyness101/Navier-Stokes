#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>

#include "SFML/Graphics.hpp"

#include "Constants.h"
#include "vec2.h"
#include "Cell.h"
#include "Grid.h"
#include "Brush.h"
#include "LayerRenderer.h"
#include "Solver.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setVerticalSyncEnabled(true);

	Grid grid(FIELD_WIDTH, FIELD_HEIGHT);
	grid.initialize(0, 10, vec2(0, 0));

	Solver solver;
	LayerRenderer layer;
	FieldType current_layer = Dye;
	sf::Sprite current_view_layer = layer.view_layer(grid, current_layer);
	bool time_is_running = 0;

	Brush brush(DEFAULT_BRUSH_RADIUS, DEFAULT_BRUSH_POWER);
	int start_mouse_cell_y = 0;
	int start_mouse_cell_x = 0;
	int current_mouse_cell_x = 0;
	int current_mouse_cell_y = 0;

	float current_time = 0;

	FieldType out_type = Dye;

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
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					start_mouse_cell_y = sf::Mouse::getPosition(window).y / PIXEL_CELL_WIDTH;
					start_mouse_cell_x = sf::Mouse::getPosition(window).x / PIXEL_CELL_HEIGHT;
				}

				current_mouse_cell_y = sf::Mouse::getPosition(window).y / PIXEL_CELL_WIDTH;
				current_mouse_cell_x = sf::Mouse::getPosition(window).x / PIXEL_CELL_HEIGHT;

				if (current_mouse_cell_x < 0 || current_mouse_cell_x >= FIELD_WIDTH ||
					current_mouse_cell_y < 0 || current_mouse_cell_y >= FIELD_HEIGHT)
				{
					continue;
				}

				int cell_index = (FIELD_HEIGHT - 1 - current_mouse_cell_y) * FIELD_WIDTH + current_mouse_cell_x;

				vec2 force = brush.gauss_brush(current_mouse_cell_x, current_mouse_cell_y, start_mouse_cell_x, start_mouse_cell_y);
				double dye_production = brush.gauss_brush_scalar(current_mouse_cell_x, current_mouse_cell_y, start_mouse_cell_x, start_mouse_cell_y);

				solver.set_force(grid, cell_index, force, brush.radius);
				solver.set_dye(grid, cell_index, dye_production, brush.radius);
				//std::cout << force.x << std::endl;
				
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
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					time_is_running = !time_is_running;
				}
			}
		}
		layer.view_layer(grid, current_layer);

		if (time_is_running)
		{
			//solver.velocity_attenuation(grid);
			solver.advect(grid, DELTA_TIME, velocityDiffusionSP);

			solver.computeDiffusion(grid, DELTA_TIME);

			solver.computePressure(grid, pressure_c, DELTA_TIME);
			solver.project(grid);

			current_time += DELTA_TIME;
		}


		window.setTitle("Current time: " + std::to_string(grid.maxx));
		window.clear();
		window.draw(current_view_layer);
		window.display();
	}
	grid.to_file_field("MATLAB\\Fields\\Velocity.txt", out_type);
	return 0;
}