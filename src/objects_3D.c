// Librairie:
//#include <stdlib.h>
//#include "matrix.h"
//#include "projection.h"
//#include "const_var.h"
//#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "const_var.h"
#include "projection.h"

// cube en 3D:
/*
typedef struct{
    Vector * vec[8];
}Cube;*/
/*
// cube de rendu:
typedef struct{
    Cube * default_cube;
    Cube * translation_cube;
    Cube * pov_cube;
    Cube * projection_cube;
    // temporory vectors:
    Vector * tmp1, * tmp2, * tmp3;
}RenderCube;*/

// initialiser un figure à 6 face:
Cube * init_cube(Vector * vector_lst[]){
    Cube * c1 = (Cube *)malloc(sizeof(Cube));
    for(int i = 0; i < 8; i++){
        c1->vec[i] = vector_lst[i];
    }
    return c1;
}

// cube unité
Cube * unit_cube(float top, float x, float z){
    Cube * c1 = (Cube *)malloc(sizeof(Cube));
    c1->vec[0] = init_vector(0.0f + x,  -1.0f + top,    0.0f + z);
    c1->vec[1] = init_vector(1.0f + x,  -1.0f + top,    0.0f + z);
    c1->vec[2] = init_vector(1.0f + x,  0.0f,          0.0f + z);
    c1->vec[3] = init_vector(0.0f + x,  0.0f,          0.0f + z);
    c1->vec[4] = init_vector(0.0f + x,  -1.0f + top,    1.0f + z);
    c1->vec[5] = init_vector(1.0f + x,  -1.0f + top,    1.0f + z);
    c1->vec[6] = init_vector(1.0f + x,  0.0f,          1.0f + z);
    c1->vec[7] = init_vector(0.0f + x,  0.0f,          1.0f + z);
    return c1;
}

// initialiser un cube de rendu:
RenderCube * init_render_cube(float top, float x, float z){
    RenderCube * renderCube = (RenderCube *) malloc(sizeof(RenderCube ));
    renderCube->default_cube = unit_cube(top, x, z);
    renderCube->translation_cube = unit_cube(top, x, z);
    renderCube->pov_cube = unit_cube(top, x, z);
    renderCube->projection_cube = unit_cube(top, x, z);

    renderCube->tmp1 = init_vector(0,0,0);
    renderCube->tmp2 = init_vector(0,0,0);
    renderCube->tmp3 = init_vector(0,0,0);

    return renderCube;
}

// Libérer espace mémoire d'un renderCube:
void freeRenderCube(RenderCube * renderCube){
    free(renderCube->default_cube);
    free(renderCube->translation_cube);
    free(renderCube->pov_cube);
    free(renderCube->projection_cube);
    free_vector(renderCube->tmp1);
    free_vector(renderCube->tmp2);
    free_vector(renderCube->tmp3);
    free(renderCube);
}

// signature fonction pour le type de rotation:
typedef int (*type_rotation)(Matrix * tmp, float angle);

// fonction projection perspective d'une cube:
void perspective_cube(Cube * cube_in, Cube * cube_out, Matrix * ortho_mat, int scaling){
    for(int i = 0; i < 8; i++){
        cube_out->vec[i]->x = cube_in->vec[i]->x, cube_out->vec[i]->y = cube_in->vec[i]->y, cube_out->vec[i]->z = cube_in->vec[i]->z, cube_out->vec[i]->w = cube_in->vec[i]->w;
        perspective_projection(cube_in->vec[i], cube_out->vec[i], ortho_mat);
        if(scaling){
            cube_out->vec[i]->x += 5.0f, cube_out->vec[i]->y += 5.0f;
            cube_out->vec[i]->x *= 0.1f * (float )INCREASE, cube_out->vec[i]->y *= 0.1f * (float )INCREASE;
        }
    }
}

// perspective caméra pour un cube:
int camera_cube(Cube * cube_in, Cube * cube_out, Vector * camera_pos, Vector * camera_angle, Matrix * tmp){
    for(int i = 0; i < 8; i++){
        camera_pov(cube_out->vec[i], cube_in->vec[i], camera_pos, camera_angle, tmp);
    }
    return 1;
}

// fonction prennant en compte une rotation pour un cube:
void rotation_on_cube(Cube * rotated_cube, type_rotation rotation_func, float angle, Matrix * tmp){
    rotation_func(tmp, angle);
    for(int i = 0; i < 8; i++){
        vector_product_matrix(rotated_cube->vec[i], tmp, rotated_cube->vec[i], DIM4);
    }
}

// fonction prennant en compte une rotation pour un vecteur:
void rotation_on_vec(Vector * vec, type_rotation rotation_func, float angle, Matrix * tmp){
    rotation_func(tmp, angle);
    vector_product_matrix(vec, tmp, vec, DIM4);
}

// signature fonction pour le type de translation:
typedef void (*type_translation)(Cube * cube_in, Cube * cube_out, float value);

// translation selon axe x:
void x_translation(Cube * cube_in, Cube * cube_out, float value){
    for(int i = 0; i < 8; i++){
        cube_out->vec[i]->x = cube_in->vec[i]->x + value;
        cube_out->vec[i]->y = cube_in->vec[i]->y;
        cube_out->vec[i]->z = cube_in->vec[i]->z;
        cube_out->vec[i]->w = cube_in->vec[i]->w;
    }
}

// translation selon axe y:
void y_translation(Cube * cube_in, Cube * cube_out, float value){
    for(int i = 0; i < 8; i++){
        cube_out->vec[i]->x = cube_in->vec[i]->x;
        cube_out->vec[i]->y = cube_in->vec[i]->y + value;
        cube_out->vec[i]->z = cube_in->vec[i]->z;
        cube_out->vec[i]->w = cube_in->vec[i]->w;
    }
}

// translation selon axe z:
void z_translation(Cube * cube_in, Cube * cube_out, float value){
    for(int i = 0; i < 8; i++){
        cube_out->vec[i]->x = cube_in->vec[i]->x;
        cube_out->vec[i]->y = cube_in->vec[i]->y;
        cube_out->vec[i]->z = cube_in->vec[i]->z + value;
        cube_out->vec[i]->w = cube_in->vec[i]->w;
    }
}

// translation d'un cube:
void translation_on_cube(Cube * cube_in, Cube * cube_out, type_translation translation, float value){
    translation(cube_in, cube_out, value);
}