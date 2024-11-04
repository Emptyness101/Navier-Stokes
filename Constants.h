#pragma once

// Window width and height in pixels
const int WINDOW_WIDTH	= 500;
const int WINDOW_HEIGHT = 500;

// Field height and width in pixels
const int FIELD_WIDTH  = 100;
const int FIELD_HEIGHT = 100;

// Cell height and width in pixels
const float PIXEL_CELL_WIDTH  = WINDOW_WIDTH / FIELD_WIDTH;
const float PIXEL_CELL_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

// Field height and width in physical units
const int PHYS_FIELD_WIDTH  = 10;
const int PHYS_FIELD_HEIGHT = 10;

// Cell height and width in physical units
const float PHYS_CELL_WIDTH  = PHYS_FIELD_WIDTH / FIELD_WIDTH;
const float PHYS_CELL_HEIGHT = PHYS_FIELD_HEIGHT / FIELD_HEIGHT;

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

const FieldType DEFAULT_FIELDTYPE = Density;