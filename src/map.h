#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define OCTAVES 4
#define PERSISTENCE 0.5

// Structure for grid:
typedef struct {
    int size;
    int **grille;
} Grid;

// Function to free memory allocated for the grid
void free_grid(Grid * grid, int limit);

// Function to initialize a grid
Grid * init_grid(int size);

// Function to fill a grid with random values within a given range
void random_grid(Grid * grid, int min, int max);

// Function to print the contents of a grid
void print_grid(Grid * grid);

// Perlin noise function
float perlin(int grid_size, float x, float y);

// Function to generate Perlin noise map
void perlin_grid(Grid * grid, int width, int height, float scale);

// regarde les voisins d'optimisation:
int big_neighbor(Grid * grid, int x, int y);

#endif /* MAP_H */
