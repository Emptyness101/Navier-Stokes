#pragma once

// Ўирина и высота окна
const int WINDOW_WIDTH	= 500;
const int WINDOW_HEIGHT = 500;

// Ўирина и высота расчетной области
const int FIELD_WIDTH  = 50;
const int FIELD_HEIGHT = 50;

// Ўирина и высота €чейки
const float CELL_WIDTH  = WINDOW_WIDTH / FIELD_WIDTH;
const float CELL_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

// Ќачальный размер кисти
const int   DEFAULT_BRUSH_RADIUS   = 1;
const float DEFAULT_BRUSH_POWER    = 100;
const float BRUSH_ATTENUATION_RATE = 0.1;

enum FieldType
{
    Velocity,
    XVelocity,
    YVelocity,
    Pressure,
    Density
};