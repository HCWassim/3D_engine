// ce fichier permet d'accéder à l'ensemble des constantes et variables nécessaire pour le 3D engine

// librairie
#include "math.h"

// PARAMETRE TECHNIQUE:
const int WIDTH = 1920, HEIGHT = 1080;
const float INCREASE = 1080.0f;
const float DELTA = 0.01f;
const float DELTA_ANGLE = 0.005f;
int DELTA_GRID = 1;
const unsigned int FPS_LIMIT = 7;

// PARAMETRE DE LA CAMERA:
const float X_POS = 0.0f;
const float Y_POS = -100.0f;
const float Z_POS = -50.0f;

// DIMENSION DES MATRICES:
int DIM4 = 4;
int DIM3 = 3;

// CUBE (ARETE):
int arete_cube[12][3] = {
        {0, 2, 1}, {2, 0, 3}, // Front face
        {6, 4, 5}, {4, 6, 7}, // Back face
        {5, 0, 1}, {0, 5, 4}, // Top
        {7, 2, 3}, {2, 7, 6}, // Side face 2
        {0, 7, 3}, {7, 0, 4}, // Side face 3
        {6, 1, 2}, {1, 6, 5}  // Side face 4*/
};

// CONSTANTE, VARIABLE & FONCTION POUR LA PROJECTION:
const float PI = 3.141592653589793f;
const float conv_deg_to_rad = PI / 180.0f;
const float conv_rad_to_deg = 180.0f / PI;
const float fov_y = 90.0f;
const float focal_near = 0.1f;
const float focal_far = 1000.0f;
const float aspect_ratio = (float)WIDTH / (float)HEIGHT;
// retourne la distance focal:
float focal_length(){
    return 1.0 / (float)tan((double)((fov_y * conv_deg_to_rad) / 2));
}

// LUMIERE:
const float X_RAY = -0.5f;
const float Y_RAY = -0.5f;
const float Z_RAY = -0.7f;

// COULEUR BACKGROUND (rgb): (1, 32, 48)
int R_BACKGROUND = 41, G_BACKGROUND = 43, B_BACKGROUND = 44;
int R_OBJ = 253, G_OBJ = 248, B_OBJ = 226;
// COULEUR ECRITURE (rgb): (218, 253, 186)