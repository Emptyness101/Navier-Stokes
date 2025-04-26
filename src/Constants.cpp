#include "Constants.h"

using json = nlohmann::json;
std::ifstream data("src/Constants.json");
json json_data = json::parse(data);

int WINDOW_WIDTH = json_data["Dimensions"]["Window"]["width"];
int WINDOW_HEIGHT = json_data["Dimensions"]["Window"]["height"];

int FIELD_WIDTH = json_data["Dimensions"]["Field"]["Pixel"]["width"];
int FIELD_HEIGHT = json_data["Dimensions"]["Field"]["Pixel"]["height"];

float PIXEL_CELL_WIDTH = WINDOW_WIDTH / FIELD_WIDTH;
float PIXEL_CELL_HEIGHT = WINDOW_HEIGHT / FIELD_HEIGHT;

int PHYS_FIELD_WIDTH = json_data["Dimensions"]["Field"]["Physical"]["width"];
int PHYS_FIELD_HEIGHT = json_data["Dimensions"]["Field"]["Physical"]["height"];

float PHYS_CELL_WIDTH = PHYS_FIELD_WIDTH / (float)FIELD_WIDTH;
float PHYS_CELL_HEIGHT = PHYS_FIELD_HEIGHT / (float)FIELD_HEIGHT;

int DEFAULT_BRUSH_RADIUS = json_data["Brush"]["Default"]["radius"];
float DEFAULT_BRUSH_POWER = json_data["Brush"]["Default"]["power"];
float BRUSH_ATTENUATION_RATE = json_data["Brush"]["attenuation_rate"];

float DELTA_TIME = json_data["Time"]["delta"];

float THRESHOLD_ALIGNMENT = json_data["Solver"]["Other"]["threshold_alignment"];
int velocityIterations = json_data["Solver"]["Iterations"]["velocity"];
float velocityDiffusion = json_data["Solver"]["Phys"]["velocity_diffusion"];
float velocityDiffusionSP = json_data["Solver"]["Phys"]["velocity_diffusion_sp"];
int pressureIterations = json_data["Solver"]["Iterations"]["pressure"];
float pressure_c = json_data["Solver"]["Phys"]["pressure_constant"];
float vorticityStrength = json_data["Solver"]["Phys"]["vorticity_strength"];

float ATTENUATION_COEFFICIENT = json_data["Solver"]["Other"]["attenuation_coefficient"];