#pragma once

// Window width and height in pixels
const int WINDOW_WIDTH	= 1000;
const int WINDOW_HEIGHT = 1000;

// Field height and width in pixels
const int FIELD_WIDTH  = 100;
const int FIELD_HEIGHT = 100;

// Cell height and width in pixels
const float PIXEL_CELL_WIDTH  = WINDOW_WIDTH / FIELD_WIDTH;
const float PIXEL_CELL_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

// Field height and width in physical units
const int PHYS_FIELD_WIDTH  = 50;
const int PHYS_FIELD_HEIGHT = 50;

// Cell height and width in physical units
const float PHYS_CELL_WIDTH  = PHYS_FIELD_WIDTH / (float)FIELD_WIDTH;
const float PHYS_CELL_HEIGHT = PHYS_FIELD_HEIGHT / (float)FIELD_HEIGHT;

//Brush settings
const int   DEFAULT_BRUSH_RADIUS   = 1;
const float DEFAULT_BRUSH_POWER    = 50;
const float BRUSH_ATTENUATION_RATE = 0.001;

//Time settings
const float DELTA_TIME = 0.01;


const int velocityIterations = 5; // Можно настроить (обычно 20-50)
const float velocityDiffusion = 0.01f; // Зависит от симуляции
const int pressureIterations = 5;
const float pressure_c = 1.5f;

//Attenuation settings
const float ATTENUATION_COEFFICIENT = 0.99;

//Threshold's
const float THRESHOLD_ALIGNMENT = 1e-5;

enum FieldType
{
    Velocity,
    XVelocity,
    YVelocity,
    Pressure,
    Density
};

const FieldType DEFAULT_FIELDTYPE = Velocity;