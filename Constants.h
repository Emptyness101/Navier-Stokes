#pragma once

// Window width and height in pixels
const int WINDOW_WIDTH	= 1000;
const int WINDOW_HEIGHT = 1000;

// Field height and width in pixels
const int FIELD_WIDTH  = 200;
const int FIELD_HEIGHT = 200;

// Cell height and width in pixels
const float PIXEL_CELL_WIDTH  = WINDOW_WIDTH / FIELD_WIDTH;
const float PIXEL_CELL_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

// Field height and width in physical units
const int PHYS_FIELD_WIDTH  = 50;
const int PHYS_FIELD_HEIGHT = 50;

// Cell height and width in physical units
const float PHYS_CELL_WIDTH  = PHYS_FIELD_WIDTH / (float)FIELD_WIDTH;
const float PHYS_CELL_HEIGHT = PHYS_FIELD_HEIGHT / (float)FIELD_HEIGHT;

// Brush settings
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

const FieldType DEFAULT_FIELDTYPE = Velocity;