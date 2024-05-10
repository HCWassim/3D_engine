// camera.h

#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/SDL.h"
#include "matrix.h"
#include "objects_3D.h"


// structure caméra:
typedef struct{
    Vector * camera_pos;
    Vector * camera_angle;
    Vector * directional_light;
    int camera_width, camera_height, camera_depth;
}Camera;

// pointer type camera operation
typedef void (*cam_change)(Camera *, float);

// initialisation de la caméra:
Camera *init_camera(int width, int height, int depth);

// libération espace de stockage associé à la caméra:
void free_cam(Camera *cam);

// vecteur direction dans laquelle la caméra pointe:
//void update_pointing_vector(Camera * cam);

// translation selon x:
void x(Camera *cam, float delta);

// translation selon y:
void y(Camera *cam, float delta);

// translation selon z:
void z(Camera *cam, float delta);

// rotation selon x:
void x_angle(Camera *cam, float delta);

// rotation selon y:
void y_angle(Camera *cam, float delta);

// rotation selon z:
void z_angle(Camera *cam, float delta);

// maj translation ou rotation:
void cam_update(Camera *cam, cam_change change, float delta);

// est dans le box de rendu:
int is_in_rendering(Camera * cam, Cube * cube);

// verifier si un point est dans le rendu camera
int is_in_cam_rendering(Camera * cam, float x, float y);

// représenter une ligne:
void line_graphic_representation(SDL_Renderer * renderer, float x1, float y1, float x2, float y2, float R, float G, float B);

// un triangle est visible:
int triangle_is_visible(Camera * cam, Vector * point_1, Vector * point_2, Vector * point_3);

// nettoyer une scene:
void clean_camera(SDL_Renderer * renderer);

// représenter un cube:
void cube_representation_2D(SDL_Renderer * renderer, Camera * cam, RenderCube * renderCube, Vector * tmp, Vector * tmp1, Vector * tmp2, int opti);

// mettre à jour orientation lumière:
void update_light(Camera * cam, float theta, float phi);

#endif // CAMERA_H
