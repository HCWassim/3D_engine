// librairie
#include <stdlib.h>
#include "../include/SDL.h"
#include "objects_3D.h"
#include "matrix.h"
#include "display.h"


// structure caméra:
typedef struct{
    Vector * camera_pos;
    Vector * camera_angle;
    Vector * directional_light;
    int camera_width, camera_height, camera_depth;
}Camera;

// signature for the operation function
typedef void (*cam_change)(Camera *, float);

// initialisation d'une caméra:
Camera * init_camera(int width, int height, int depth){
    // allocation mémoire de la caméra:
    Camera * cam = (Camera *)malloc(sizeof(Camera));
    // echec de l'allocation mémoire:
    if(cam == NULL) return 0;
    cam->camera_pos = init_vector(0.0f,0.0f,0.0f);
    if(cam->camera_pos == NULL) return 0;
    cam->camera_angle = init_vector(0,0,0);
    if(cam->camera_angle == NULL) return 0;
    cam->directional_light = init_vector(-0.45f,-0.45f,-0.45f);
    if(cam->directional_light == NULL) return 0;
    cam->camera_width = width;
    cam->camera_height = height;
    cam->camera_depth = depth;
    return cam;
}

// libérer espace mémoire d'une caméra:
void free_cam(Camera * cam){
    free_vector(cam->camera_pos);
    free_vector(cam->camera_angle);
    free_vector(cam->directional_light);
    free(cam);
}

// mouvement linéaire de la caméra selon x:
void x(Camera * cam, float delta){
    cam->camera_pos->x += delta * cos(cam->camera_angle->y);
//    cam->camera_pos->y += delta * (cos(cam->camera_angle->x) - sin(cam->camera_angle->x));
    cam->camera_pos->z += - delta * sin(cam->camera_angle->y);
}

// mouvement linéaire de la caméra selon y:
void y(Camera * cam, float delta){
    cam->camera_pos->y += delta;
}

// mouvement linéaire de la caméra selon z:
void z(Camera * cam, float delta){
    cam->camera_pos->z += delta;
}

// mouvement angulaire de la caméra selon x:
void x_angle(Camera * cam, float delta){
    if(delta > 0 && cam->camera_angle->x < 1.0f) cam->camera_angle->x += delta;
    if(delta < 0 && cam->camera_angle->x > -1.0f) cam->camera_angle->x += delta;
}

// mouvement angulaire de la caméra selon y:
void y_angle(Camera * cam, float delta){
    if(delta > 0 && cam->camera_angle->y < 1.0f) cam->camera_angle->y += delta;
    if(delta < 0 && cam->camera_angle->y > -1.0f) cam->camera_angle->y += delta;
}

// mouvement angulaire de la caméra selon z:
void z_angle(Camera * cam, float delta){
    cam->camera_angle->z += delta;

}

// cas général:
void cam_update(Camera * cam, cam_change change, float delta){
    change(cam, delta);
}

// est dans le rendu camera:
int is_in_cam_rendering(Camera * cam, float x, float y){
    if (x >= 0.0f && x <= cam->camera_width * 2 &&
        y >= 0.0f && y <= cam->camera_height * 2) return 1;
    else return 0;
}

int is_in_rendering(Camera * cam, Cube * cube){
    float limit = 100.0f;
    float x = cube->vec[0]->x, y = cube->vec[0]->y;
    if((0.0f - limit <= x && x <= cam->camera_width + limit)  &&
       (0.0f - limit <= y && y <= cam->camera_height + limit)) return 1;
    else return 0;
}

// un triangle est visible:
int triangle_is_visible(Camera * cam, Vector * point_1, Vector * point_2, Vector * point_3){
    if(is_in_cam_rendering(cam, point_1->x, point_1->y) ||
       is_in_cam_rendering(cam, point_2->x, point_2->y) ||
       is_in_cam_rendering(cam, point_3->x, point_3->y)) return 1;
    else return 0;
}

// nettoyer une scene:
void clean_camera(SDL_Renderer * renderer){
    SDL_SetRenderDrawColor(renderer, R_BACKGROUND, G_BACKGROUND, B_BACKGROUND, SDL_ALPHA_OPAQUE); // background
    SDL_RenderClear(renderer); // nettoyage du fond
}

// représenter un cube:
void cube_representation_2D(SDL_Renderer * renderer, Camera * cam, RenderCube * renderCube, Vector * tmp, Vector * tmp1, Vector * tmp2, int opti){
    Cube * proj_cube = renderCube->projection_cube;
    int point_1, point_2, point_3;
    float projection, light;
    int begin, end;
    if(opti){
        begin = 4, end = 6;
    }
    else{
        begin = 0, end = 12;
    }
    for(int i = begin; i < end; i++){
        // couple de points:
        point_1 = arete_cube[i][0], point_2 = arete_cube[i][1], point_3 = arete_cube[i][2];
        // création de vecteurs correspondant aux arrête d'une face:
        vector_from_points(tmp1, proj_cube->vec[point_1], proj_cube->vec[point_2]);
        vector_from_points(tmp2, proj_cube->vec[point_3], proj_cube->vec[point_2]);
        // produit vectoriel:
        cross_product(tmp, tmp2, tmp1, 1);
        // projection:
        projection = tmp->z * (cam->camera_pos->z - proj_cube->vec[point_3]->z);
        // dans le champ de la caméra:
        if (triangle_is_visible(cam, proj_cube->vec[point_1], proj_cube->vec[point_2], proj_cube->vec[point_3]) && projection < 0.0f){
            // directionnal light:
            vector_from_points(tmp1, renderCube->translation_cube->vec[point_1], renderCube->translation_cube->vec[point_2]);
            vector_from_points(tmp2, renderCube->translation_cube->vec[point_3], renderCube->translation_cube->vec[point_2]);
            cross_product(tmp, tmp2, tmp1, 1);
            light = scalar_product(cam->directional_light, tmp);
            if(light < 0.0f) light = 0.0f;
//            light = 1.0f - light;
            fill_triangle(renderer, proj_cube->vec[point_1], proj_cube->vec[point_2], proj_cube->vec[point_3], R_OBJ * light, G_OBJ * light, B_OBJ * light);
            line_graphic_representation(renderer,
                                        proj_cube->vec[point_1]->x, proj_cube->vec[point_1]->y,
                                        proj_cube->vec[point_3]->x, proj_cube->vec[point_3]->y,
                                        0, 0, 0);
            line_graphic_representation(renderer,
                                        proj_cube->vec[point_2]->x, proj_cube->vec[point_2]->y,
                                        proj_cube->vec[point_3]->x, proj_cube->vec[point_3]->y,
                                        0, 0, 0);
        }
    }
}

// mettre à jour la lumière:
void update_light(Camera * cam, float theta, float phi){
    float r = 1.0f;
    float x_comp = r * (float)(sin((double)theta) * cos((double)phi) * 0.5f + r * sin((double)theta) * sin((double)phi));
    float y_comp = r * (float)(cos((double)theta) * (-1.0f / sqrtf(2.0f)) + r * sin((double)theta) * sin((double)phi));
    float z_comp = r * (float)(cos((double)theta) * (1.0f / sqrtf(2.0f)) + r * sin((double)theta) * cos((double)phi) * -0.5f) + r * sin((double)theta) * sin((double)phi);
    cam->directional_light->x = x_comp;
    cam->directional_light->y = y_comp;
    cam->directional_light->z = z_comp;

}