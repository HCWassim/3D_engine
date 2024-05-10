// librairie
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define OCTAVES 4
#define PERSISTENCE 0.5

// Structure grille:
typedef struct{
    int size;
    int **grille;
}Grid;

typedef enum {
    // Toutes les faces doivent être rendues :
    all_face,
    five_face,
    four_face,
    three_face,
    two_face,
    one_face,
    no_face
} render_side;


// libérer espace mémoire d'une matrice:
void free_grid(Grid * grid, int limit){
    for(int i = 0; i < limit; i++){
        free(grid->grille[i]);
    }
    free(grid->grille);
    free(grid);
}

// Initialisation d'une grille:
Grid * init_grid(int size){
    Grid * grid = (Grid *) malloc(sizeof(Grid));
    // vérification de la réussite de l'allocation mémoire:
    if (grid == NULL) {
        fprintf(stderr, "ERREUR: echec allocation mémoire pour la structure grid");
        return NULL;
    }
    grid->size = size;
    // allocation mémoire de la matrice:
    grid->grille = (int **)malloc(size * sizeof(int *));
    if(grid->grille == NULL){
        fprintf(stderr,"ERREUR: echec allocation mémoire matrice (grille)");
        return NULL;
    }
    // allouer un mémoire pour chaque ligne de la matrice:
    for(int i = 0; i < size; i++){
        grid->grille[i] = (int *)malloc(size * sizeof(int));
        if(grid->grille[i] == NULL){
            fprintf(stderr, "ERREUR: echec allocation mémoire matrice (collones)");
            // libération espace mémoire alloué:
            free_grid(grid, i);
            return 0;
        }
    }
    return grid;
}

// grille rempli de valeur aléatoire:
void random_grid(Grid * grid, int min, int max){
    srand(time(NULL));
    for(int i = 0; i < grid->size; i++){
        for(int j = 0; j < grid->size; j++){
            int random_number = rand();
            random_number = random_number % (max - min + 1) + min;
            grid->grille[i][j] = random_number;
        }
    }
}

void print_grid(Grid * grid){
    printf("\n");
    for(int i = 0; i < grid->size; i++){
        for(int j = 0; j < grid->size; j++){
            printf("%d ", grid->grille[i][j]);
            if(j == (grid->size - 1)) printf("\n");
        }
    }
    printf("\n");
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

int hash(int x, int y) {
    return (int)(((x * 1619) + (y * 31337)) % 65536);
}

float grad(int hash, float x, float y) {
    switch (hash & 3) {
        case 0: return x + y;
        case 1: return -x + y;
        case 2: return x - y;
        case 3: return -x - y;
        default: return 0; // Never happens
    }
}

// Perlin noise function
float perlin(int grid_size, float x, float y) {
    // Calculate the coordinates within the range [0, grid->size)
    int X = ((int)floor(x) % grid_size + grid_size) % grid_size;
    int Y = ((int)floor(y) % grid_size + grid_size) % grid_size;

    // Calculate the fractional part of the coordinates
    float xf = x - floor(x);
    float yf = y - floor(y);

    // Calculate the fade values
    float u = fade(xf);
    float v = fade(yf);

    // Generate the hash values for the grid points
    int AA = hash(X, Y);
    int AB = hash(X, (Y + 1) % grid_size);
    int BA = hash((X + 1) % grid_size, Y);
    int BB = hash((X + 1) % grid_size, (Y + 1) % grid_size);

    // Interpolate along both axes
    float x1 = lerp(grad(AA, xf, yf), grad(BA, xf - 1, yf), u);
    float x2 = lerp(grad(AB, xf, yf - 1), grad(BB, xf - 1, yf - 1), u);
    float y1 = lerp(x1, x2, v);

    x1 = lerp(grad(AA, xf, yf), grad(AB, xf, yf - 1), u);
    x2 = lerp(grad(BA, xf - 1, yf), grad(BB, xf - 1, yf - 1), u);
    float y2 = lerp(x1, x2, v);

    // Return the final interpolated value
    return (lerp(y1, y2, v) + 1) / 2;
}


// Function to generate Perlin noise map
void perlin_grid(Grid * grid, int width, int height, float scale) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float sampleX = (float)x / scale;
            float sampleY = (float)y / scale;
            float amplitude = 1;
            float frequency = 1;
            float noiseValue = 0;

            for (int o = 0; o < OCTAVES; o++) {
                noiseValue += perlin(grid->size , sampleX * frequency, sampleY * frequency) * amplitude;
                amplitude *= PERSISTENCE;
                frequency *= 2;
            }

            grid->grille[y][x] = noiseValue;
        }
    }
}

// regarde les voisins d'optimisation:
int big_neighbor(Grid * grid, int x, int y){
    int current_val = grid->grille[x][y];
    if(grid->grille[x - 1][y - 1] >= current_val &&
       grid->grille[x - 1][y] >= current_val     &&
       grid->grille[x - 1][y + 1] >= current_val &&
       grid->grille[x][y - 1] >= current_val     &&
       grid->grille[x][y] >= current_val         &&
       grid->grille[x][y + 1] >= current_val     &&
       grid->grille[x + 1][y - 1] >= current_val &&
       grid->grille[x + 1][y] >= current_val     &&
       grid->grille[x + 1][y + 1] >= current_val
    ) return 1;
    else return 0;
}

//int main(){
//    Grid * grid = init_grid(50);
//    perlin_grid(grid, grid->size, grid->size, 32);
//    print_grid(grid);
//    free_grid(grid, grid->size);
//    return 0;
//}