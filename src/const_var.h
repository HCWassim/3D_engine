#ifndef CONST_VAR_H
#define CONST_VAR_H

#include <math.h>

// PARAMETRE DE LA CAMERA:
extern const float X_POS;
extern const float Y_POS;
extern const float Z_POS;

// TECHNICAL PARAMETERS:
extern const int WIDTH;
extern const int HEIGHT;
extern const float INCREASE;
extern const float DELTA;
extern const float DELTA_ANGLE;
extern int DELTA_GRID;
extern const unsigned int FPS_LIMIT;

// DIMENSION DES MATRICES:
int DIM4;
int DIM3;

// ARETES CUBE:
int arete_cube[12][3];

// PROJECTION CONSTANTS, VARIABLES & FUNCTIONS:
extern const float PI;
extern const float conv_deg_to_rad;
extern const float conv_rad_to_deg;
extern const float fov_y;
extern const float focal_near;
extern const float focal_far;
extern const float aspect_ratio;
// Functions to access projection parameters:
float focal_length();

// LUMIERE:
extern const float X_RAY;
extern const float Y_RAY;
extern const float Z_RAY;

// COULEUR BACKGROUND (rgb): (1, 32, 48)
int R_BACKGROUND, G_BACKGROUND, B_BACKGROUND;
int R_OBJ, G_OBJ, B_OBJ;

#endif // CONST_VAR_H
