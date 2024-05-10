#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

// Structure de vecteur :
struct vector {
    float x, y, z, w;
};
typedef struct vector Vector;

// Structure de matrice :
struct matrix {
    int rows;
    int cols;
    float x, y, z;
    float **matrice;
};
typedef struct matrix Matrix;


// Déclarations de fonctions :

// Afficher les valeurs d'une matrice dans la console.
int print_matrix(Matrix *mat);

// Mettre à jour les coordonnées d'une matrice en fonction de son contenu.
void update_coord(Matrix *mat);

// Libérer la mémoire allouée pour un vecteur.
void free_vector(Vector *vec);

// Libérer la mémoire allouée pour une matrice.
void free_matrix(Matrix *mat, int limit);

// Initialiser un vecteur et allouer de la mémoire pour celui-ci.
Vector * init_vector(float x, float y, float z);

// initialiser un vecteur à partir de deux points existant:
void vector_from_points(Vector * result, Vector * point_1, Vector * point_2);

// Initialiser une matrice et allouer de la mémoire pour celle-ci.
Matrix *init_matrix(int rows, int cols);

// Définir les valeurs d'un vecteur pour représenter le vecteur identité.
int identity_vector(Vector *vec);

// Définir les valeurs d'une matrice pour représenter la matrice identité.
int identity_matrix(Matrix *mat);

// Définir les valeurs d'un vecteur pour représenter le vecteur neutre.
int neutral_vector(Vector *vec);

// Définir les valeurs d'une matrice pour représenter la matrice neutre.
void neutral_matrix(Matrix *mat);

// Initialiser les valeurs d'une matrice en fonction d'un tableau 2D donné.
int init_values_matrix(Matrix *mat, int **lst_val, int lst_rows, int lst_cols);

// Multiplier un vecteur par un scalaire.
int scalar_vector(Vector *vec, float scalar);

// Multiplier une matrice par un scalaire.
int scalar_matrix(Matrix *mat, float scalar);

// Effectuer l'addition ou la soustraction de deux vecteurs.
int sum_vector(Vector * vec_sum, Vector *vec_1, Vector * vec_2, int is_addition);

// Effectuer l'addition ou la soustraction de deux matrices.
int sum_matrix(Matrix * mat_sum, Matrix *mat_1, Matrix *mat_2, int is_addition);

// Changer la valeur d'un élément spécifique dans une matrice.
void change_val_matrix(Matrix *mat, int x, int y, float value);

// Effectuer la multiplication vecteur-matrice pour la projection orthographique.
int vector_product_matrix(Vector * product, Matrix * ortho, Vector * coord, int dim);

// produit vectoriel de deux vecteurs:
int cross_product(Vector * result, Vector * vec_1, Vector * vec_2, int normalize);

// produit scalaire de deux vecteurs:
float scalar_product(Vector * vec_1, Vector * vec_2);

// norme d'un vecteur:
float normal_vector(Vector * vec);

// normaliser un vecteur:
void normalize_vector(Vector * vec);

#endif // MATRIX_H