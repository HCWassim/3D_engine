// librairie
#include <stdio.h>
#include <stdlib.h>
#include "const_var.h"

// structure vecteur:
struct vector{
    float x, y, z, w;
};
typedef struct vector Vector;

// structure matrice:
struct matrix{
    int rows;
    int cols;
    float x, y, z;
    float **matrice;
};
typedef struct matrix Matrix;

// afficher les valeurs d'une matrice:
int print_matrix(Matrix *mat){
    if(mat->matrice == NULL) return 0;
    printf("\n");
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            printf("%f ", mat->matrice[i][j]);
            if(j == (mat->cols - 1)) printf("\n");
        }
    }
    printf("\n");
    return 1;
}

// mettre à jour des matrices:
void update_coord(Matrix *mat){
    if(mat->rows <= 3 && mat->cols == 1){
        mat->x = mat->matrice[0][0];
        mat->y = mat->matrice[1][0];
        if(mat->rows == 3) mat->z = mat->matrice[2][0];
    }
}

// libérer espace mémoire d'un vecteur:
void free_vector(Vector *vec){
    free(vec);
}

// libérer espace mémoire d'une matrice:
void free_matrix(Matrix *mat, int limit){
    for(int i = 0; i < limit; i++){
        free(mat->matrice[i]);
    }
    free(mat->matrice);
    free(mat);
}

// initialiser un vecteur:
Vector * init_vector(float x, float y, float z){
    // allocation mémoire de la structure vecteur:
    Vector * vec = (Vector *)malloc(sizeof(Vector));
    vec->x = x, vec->y = y, vec->z = z;
    return vec;
}

// initialiser un vecteur à partir de deux points existant:
void vector_from_points(Vector * result, Vector * point_1, Vector * point_2){
    // allocation mémoire de la structure vecteur:
    result->x = point_1->x - point_2->x;
    result->y = point_1->y - point_2->y;
    result->z = point_1->z - point_2->z;
}

// initialiser une matrice:
Matrix * init_matrix(int rows, int cols){
    // allocation mémoire de la structure matrix:
    Matrix * mat = (Matrix *)malloc(sizeof(Matrix));
    // vérification de la réussite de l'allocation mémoire:
    if (mat == NULL) {
        fprintf(stderr, "ERREUR: echec allocation mémoire pour la structure matrice");
        return 0;
    }
    // allocation mémoire de la matrice:
    mat->rows = rows;
    mat->cols = cols;
    mat->matrice = (float **)malloc(rows * sizeof(float *));
    if(mat->matrice == NULL){
        fprintf(stderr,"ERREUR: echec allocation mémoire matrice (rows)");
        return 0;
    }
    // allouer un mémoire pour chaque ligne de la matrice:
    for(int i = 0; i < rows; i++){
        mat->matrice[i] = (float *)malloc(cols * sizeof(float));
        if(mat->matrice[i] == NULL){
            fprintf(stderr, "ERREUR: echec allocation mémoire matrice (collones)");
            // libération espace mémoire alloué:
            free_matrix(mat, i);
            return 0;
        }
    }
    return mat;
}

// norme d'un vecteur:
float normal_vector(Vector * vec){
    return sqrtf((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
}

// normaliser un vecteur:
void normalize_vector(Vector * vec){
    float norme = normal_vector(vec);
    vec->x /= norme, vec->y /= norme, vec->z /= norme;
}

// vecteur identité:
int identity_vector(Vector *vec){
    if(vec == NULL) return 0;
    vec->x = 1, vec->y = 1, vec->z = 1, vec->w = 1;
    return 1;
}

// matrice identité:
int identity_matrix(Matrix *mat){
    if(mat->cols != mat->rows) return 0;
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            if(i == j) mat->matrice[i][j] = 1.0f;
            else mat->matrice[i][j] = 0.0f;
        }
    }
    update_coord(mat);
    return 1;
}

// vecteur neutre:
int neutral_vector(Vector *vec){
    if(vec == NULL) return 0;
    vec->x = 0, vec->y = 0, vec->z = 0, vec->w = 0;
    return 1;
}
// matrice neutre:
void neutral_matrix(Matrix * mat){
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->rows; j++){
            mat->matrice[i][j] = 0.0f;
        }
    }
    update_coord(mat);
}

// initialiser les valeurs dans une matrice:
int init_values_matrix(Matrix *mat, int **lst_val, int lst_rows, int lst_cols){
    if(mat->rows != lst_rows || mat->cols != lst_cols) return 0;
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            mat->matrice[i][j] = lst_val[i][j];
        }
    }
    update_coord(mat);
    return 1;
}

// multiplier un vecteur par un scalaire:
int scalar_vector(Vector * vec, float scalar){
    if(vec == NULL) return 0;
    vec->x *= scalar, vec->y *= scalar, vec->z *= scalar, vec->w *= scalar;
    return 1;
}
// multiplier une matrice avec un scalaire:
int scalar_matrix(struct matrix *mat, float scalar){
    if(mat->matrice == NULL) return 0;
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            mat->matrice[i][j] *= scalar;
        }
    }
    update_coord(mat);
    return 1;
}

// déterminer l'addition ou soustraction de deux vecteur:
int sum_vector(Vector * vec_sum, Vector *vec_1, Vector * vec_2, int is_addition){
    if(is_addition){
        vec_sum->x = vec_1->x + vec_2->x;
        vec_sum->y = vec_1->y + vec_2->y;
        vec_sum->z = vec_1->z + vec_2->z;
        vec_sum->z = vec_1->z + vec_2->z;
    }
    else{
        vec_sum->x = vec_1->x - vec_2->x;
        vec_sum->y = vec_1->y - vec_2->y;
        vec_sum->z = vec_1->z - vec_2->z;
        vec_sum->z = vec_1->z - vec_2->z;
    }
    return 1;
}

// déterminer l'addition ou la soustraction de deux matrices:
int sum_matrix(Matrix * mat_sum, Matrix *mat_1, Matrix *mat_2, int is_addition){
    if(mat_1->rows != mat_2->rows || mat_1->cols != mat_2->cols) fprintf(stderr, "ERREUR: somme impossible");
    for(int i = 0; i < mat_1->rows; i++){
        for(int j = 0; j < mat_1->cols; j++){
            if(is_addition) mat_sum->matrice[i][j] = mat_1->matrice[i][j] + mat_2->matrice[i][j];
            else mat_sum->matrice[i][j] = mat_1->matrice[i][j] - mat_2->matrice[i][j];
        }
    }
    update_coord(mat_sum);
    return 1;
}

// change value of a matrix:
void change_val_matrix(Matrix * mat, int x, int y, float value){
    mat->matrice[x][y] = value;
    update_coord(mat);
}

// orthographic matrix product:
int vector_product_matrix(Vector * product, Matrix * ortho, Vector * coord, int dim){
    if (coord == NULL || ortho->rows != dim || ortho->cols != dim) {
        fprintf(stderr, "ERREUR: produit orthographique impossible");
        return 0;
    }
//    Vector * product = init_vector(0,0,0);
    if(product){
        product->x = ortho->matrice[0][0] * coord->x + ortho->matrice[0][1] * coord->y + ortho->matrice[0][2] * coord->z + ortho->matrice[0][3] * coord->w;
        product->y = ortho->matrice[1][0] * coord->x + ortho->matrice[1][1] * coord->y + ortho->matrice[1][2] * coord->z + ortho->matrice[1][3] * coord->w;
        product->z = ortho->matrice[2][0] * coord->x + ortho->matrice[2][1] * coord->y + ortho->matrice[2][2] * coord->z + ortho->matrice[2][3] * coord->w;
        if(dim == DIM4){
            product->w = ortho->matrice[3][0] * coord->x + ortho->matrice[3][1] * coord->y + ortho->matrice[3][2] * coord->z + ortho->matrice[3][3] * coord->w;
        }
    }
    return 1;
}

// produit vectoriel de deux vecteurs:
int cross_product(Vector * result, Vector * vec_1, Vector * vec_2, int normalize){
//    Vector * result = init_vector(0,0,0);
    result->x = (vec_1->y * vec_2->z) - (vec_1->z * vec_2->y);
    result->y = (vec_1->z * vec_2->x) - (vec_2->z * vec_1->x);
    result->z = (vec_1->x * vec_2->y) - (vec_1->y * vec_2->x);
    if(normalize){
        float n = normal_vector(result);
        result->x /= n, result->y /= n, result->z /= n;
    }
    return 1;
}

// produit scalaire de deux vecteurs:
float scalar_product(Vector * vec_1, Vector * vec_2){
    return (vec_1->x * vec_2->x) + (vec_1->y * vec_2->y) + (vec_1->z * vec_2->z);
}