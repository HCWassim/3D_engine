#ifndef DISPLAY_H
#define DISPLAY_H

#include "../include/SDL.h"
#include "matrix.h"

void pixel_graphic_representation(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b);
void line_graphic_representation(SDL_Renderer *renderer, float x1, float y1, float x2, float y2, float R, float G, float B);
void fill_triangle(SDL_Renderer *renderer, Vector *point_1, Vector *point_2, Vector *point_3, int R, int G, int B);

#endif /* DISPLAY_H */
