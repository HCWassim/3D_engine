// librairie:
#include <stdio.h>
#include "matrix.h"
#include "math.h"
#include "const_var.h"
#include "camera.h"

// matrice rotation selon angle x:
int rotation_x(Matrix * mat_rot_x, float angle){
//    Matrix * mat_rot_x = init_matrix(4, 4);
    identity_matrix(mat_rot_x);
    change_val_matrix(mat_rot_x, 1, 1, (float)cos((double)(angle)));
    change_val_matrix(mat_rot_x, 1, 2, (float)sin((double)(angle)));
    change_val_matrix(mat_rot_x, 2, 1, (float)-sin((double)(angle)));
    change_val_matrix(mat_rot_x, 2, 2, (float)cos((double)(angle)));
    return 1;
}
// transposé de x:
int rot_x(Matrix * mat_rot_x, float angle){
//    Matrix * mat_rot_x = init_matrix(4, 4);
    identity_matrix(mat_rot_x);
    change_val_matrix(mat_rot_x, 1, 1, (float)cos((double)(angle)));
    change_val_matrix(mat_rot_x, 1, 2, (float)-sin((double)(angle)));
    change_val_matrix(mat_rot_x, 2, 1, (float)sin((double)(angle)));
    change_val_matrix(mat_rot_x, 2, 2, (float)cos((double)(angle)));
    return 1;
}

// matrice rotation selon angle y:
int rotation_y(Matrix * mat_rot_y, float angle){
//    Matrix * mat_rot_y = init_matrix(4, 4);
    identity_matrix(mat_rot_y);
    change_val_matrix(mat_rot_y, 0, 0, (float)cos((double)(angle)));
    change_val_matrix(mat_rot_y, 0, 2, (float)-sin((double)(angle)));
    change_val_matrix(mat_rot_y, 2, 0, (float)sin((double)(angle)));
    change_val_matrix(mat_rot_y, 2, 2, (float)cos((double)(angle)));
    return 1;
}
// transposé de y:
int rot_y(Matrix * mat_rot_y, float angle){
//    Matrix * mat_rot_y = init_matrix(4, 4);
    identity_matrix(mat_rot_y);
    change_val_matrix(mat_rot_y, 0, 0, (float)cos((double)(angle)));
    change_val_matrix(mat_rot_y, 0, 2, (float)sin((double)(angle)));
    change_val_matrix(mat_rot_y, 2, 0, (float)-sin((double)(angle)));
    change_val_matrix(mat_rot_y, 2, 2, (float)cos((double)(angle)));
    return 1;
}

// matrice rotation selon angle z:
int rotation_z(Matrix * mat_rot_z, float angle){
//    Matrix * mat_rot_z = init_matrix(4, 4);
    identity_matrix(mat_rot_z);
    change_val_matrix(mat_rot_z, 0, 0, (float)cos((double)(angle)));
    change_val_matrix(mat_rot_z, 0, 1, (float)sin((double)(angle)));
    change_val_matrix(mat_rot_z, 1, 0, (float)-sin((double)(angle)));
    change_val_matrix(mat_rot_z, 1, 1, (float)cos((double)(angle)));
    return 1;
}
// transposé de z:
int rot_z(Matrix * mat_rot_z, float angle){
//    Matrix * mat_rot_z = init_matrix(4, 4);
    identity_matrix(mat_rot_z);
    change_val_matrix(mat_rot_z, 0, 0, (float)cos((double)(angle)));
    change_val_matrix(mat_rot_z, 0, 1, (float)-sin((double)(angle)));
    change_val_matrix(mat_rot_z, 1, 0, (float)sin((double)(angle)));
    change_val_matrix(mat_rot_z, 1, 1, (float)cos((double)(angle)));
    return 1;
}

// point de vu de la caméra:
int camera_pov(Vector * result, Vector * object_pos, Vector * camera_pos, Vector * camera_angle, Matrix * tmp){
    if(object_pos == NULL || camera_pos == NULL || camera_angle == NULL) return 0; // fprintf(stderr, "ERREUR: Matrice non initialise \n")
    // différence distance caméra et objet:
    sum_vector(result, object_pos, camera_pos, 0);
    // rotation d'angle selon z:
    rotation_z(tmp, camera_angle->z);
    vector_product_matrix(result, tmp, result, DIM4);
    // rotation d'angle selon y:
    rotation_y(tmp, camera_angle->y);
    vector_product_matrix(result, tmp, result, DIM4);
    // rotation d'angle selon x:
    rotation_x(tmp, camera_angle->x);
    vector_product_matrix(result, tmp, result, DIM4);
    return 1;
}

// define orthographic projection matrix:
Matrix * init_orthographic_matrix(Camera * camera){
    Matrix * mat = init_matrix(DIM4, DIM4);
    neutral_matrix(mat);
    change_val_matrix(mat, 0, 0, focal_length());
    change_val_matrix(mat, 1, 1, focal_length());
    change_val_matrix(mat, 2, 2, -(focal_far / (focal_far - focal_near)));
    change_val_matrix(mat, 2, 3, -1.0f);
    change_val_matrix(mat, 3, 2, (focal_near + camera->camera_pos->z) * (focal_far + + camera->camera_pos->z) / (focal_far - focal_near));
    return mat;
}

void update_ortho_matrix(Camera * camera, Matrix * mat){
    change_val_matrix(mat, 3, 2, (focal_near + camera->camera_pos->z) * (focal_far + + camera->camera_pos->z) / (focal_far - focal_near));
}

// passage de coord 3D en perspective 2D
void perspective_projection(Vector * vec_in, Vector * vec_out, Matrix * ortho_mat){
    vector_product_matrix(vec_out, ortho_mat, vec_in, DIM4);
//    vec_out->x = product->x, vec_out->y = product->y, vec_out->z = product->z, vec_out->w = product->w;
    float w = vec_out->w;
    if(w != 0){
        vec_out->x /= w;
        vec_out->y /= w;
        vec_out->z /= w;
    }
}