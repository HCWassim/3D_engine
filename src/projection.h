#ifndef PROJECTION_H
#define PROJECTION_H

#include "matrix.h"
#include "math.h"
#include "const_var.h"
#include "camera.h"

// Constantes globales orthographiques:
//extern const float E_X, E_Y, E_Z;

// Déclarations de fonctions :

// Créer une matrice de rotation selon l'axe x.
int rotation_x(Matrix * mat_rot_x, float angle);
// transposé
int rot_x(Matrix * mat_rot_x, float angle);

// Créer une matrice de rotation selon l'axe y.
int rotation_y(Matrix * mat_rot_y, float angle);
// transposé de y:
int rot_y(Matrix * mat_rot_y, float angle);

// Créer une matrice de rotation selon l'axe z.
int rotation_z(Matrix * mat_rot_z, float angle);
// transposé de z:
int rot_z(Matrix * mat_rot_z, float angle);

// Appliquer le point de vue de la caméra sur un objet.
int camera_pov(Vector * result, Vector * object_pos, Vector * camera_pos, Vector * camera_angle, Matrix * tmp);

// Initialiser la matrice de projection orthographique.
Matrix *init_orthographic_matrix(Camera  * camera);

// passage de coord 3D en perspective 2D.
void perspective_projection(Vector * vec_in, Vector * vec_out, Matrix * ortho_mat);

void update_ortho_matrix(Camera * camera, Matrix * mat);

#endif // PROJECTION_H
