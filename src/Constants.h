#pragma once

#include "Json.hpp"
#include <fstream>

// Window settings
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

// Field settings
extern int FIELD_WIDTH;
extern int FIELD_HEIGHT;

// Cell size in pixels
extern float PIXEL_CELL_WIDTH;
extern float PIXEL_CELL_HEIGHT;

// Field size in physical units
extern int PHYS_FIELD_WIDTH;
extern int PHYS_FIELD_HEIGHT;

// Cell size in physical units
extern float PHYS_CELL_WIDTH;
extern float PHYS_CELL_HEIGHT;

// Brush settings
extern int DEFAULT_BRUSH_RADIUS;
extern float DEFAULT_BRUSH_POWER;
extern float BRUSH_ATTENUATION_RATE;

// Time settings
extern float DELTA_TIME;

// Solver settings
extern float THRESHOLD_ALIGNMENT;
extern int velocityIterations;
extern float velocityDiffusion;
extern float velocityDiffusionSP;
extern int pressureIterations;
extern float pressure_c;
extern float vorticityStrength;

// Attenuation settings
extern float ATTENUATION_COEFFICIENT;

enum FieldType
{
    Velocity,
    XVelocity,
    YVelocity,
    Pressure,
    Density, 
    Dye
};

const FieldType DEFAULT_FIELDTYPE = Velocity;