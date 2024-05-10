#ifndef OBJECTS_3D_H
#define OBJECTS_3D_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "const_var.h"

// 3D Cube structure:
typedef struct {
    Vector *vec[8];  // Array of 8 vectors representing the vertices of a cube
} Cube;

// RenderCube structure with different cube representations:
typedef struct {
    Cube *default_cube;
    Cube *translation_cube;
    Cube *pov_cube;
    Cube *projection_cube;
    // Temporary vectors for intermediate calculations:
    Vector *tmp1, *tmp2, *tmp3;
} RenderCube;

// Function prototypes:

// Initialize a cube with a list of vectors:
Cube *init_cube(Vector *vector_lst[]);

// Initialize a unit cube with specified top, x, and z offsets:
Cube *unit_cube(float top, float x, float z);

// Initialize a RenderCube with specified parameters:
RenderCube *init_render_cube(float top, float x, float z);

// Free the memory allocated for a RenderCube:
void freeRenderCube(RenderCube *renderCube);

// Define a rotation function type (for rotating cubes):
typedef int (*type_rotation)(Matrix *tmp, float angle);

// Perform rotation on a cube using a given rotation function and angle:
void rotation_on_cube(Cube *rotated_cube, type_rotation rotation_func, float angle, Matrix *tmp);

// Perform rotation on a vector using a given rotation function and angle:
void rotation_on_vec(Vector *vec, type_rotation rotation_func, float angle, Matrix *tmp);

// Perspective projection for a cube with an orthographic matrix and scaling:
void perspective_cube(Cube *cube_in, Cube *cube_out, Matrix *ortho_mat, int scaling);

// Camera perspective projection for a cube:
int camera_cube(Cube *cube_in, Cube *cube_out, Vector *camera_pos, Vector *camera_angle, Matrix *tmp);

// Define a translation function type (for translating cubes):
typedef void (*type_translation)(Cube *cube_in, Cube *cube_out, float value);

// Translation functions along the X, Y, and Z axes:
void x_translation(Cube *cube_in, Cube *cube_out, float value);
void y_translation(Cube *cube_in, Cube *cube_out, float value);
void z_translation(Cube *cube_in, Cube *cube_out, float value);

// Perform translation on a cube using a specific translation function:
void translation_on_cube(Cube *cube_in, Cube *cube_out, type_translation translation, float value);

#endif // OBJECTS_3D_H
