// display.c
// Librairie:
#include "../include/SDL.h"
#include "matrix.h"
#include "math.h"

// représenter un pixel graphiquement
void pixel_graphic_representation(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x, y);
}

// représenter une ligne:
void line_graphic_representation(SDL_Renderer * renderer, float x1, float y1, float x2, float y2, float R, float G, float B){
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// remplir un triangle:
void fill_triangle(SDL_Renderer * renderer, Vector * point_1, Vector * point_2, Vector * point_3, int R, int G, int B) {
    // Sort vertices based on y-coordinate
    if (point_1->y > point_2->y) {
        Vector * temp = point_1;
        point_1 = point_2;
        point_2 = temp;
    }
    if (point_1->y > point_3->y) {
        Vector * temp = point_1;
        point_1 = point_3;
        point_3 = temp;
    }
    if (point_2->y > point_3->y) {
        Vector * temp = point_2;
        point_2 = point_3;
        point_3 = temp;
    }

    // Calculate slopes of AB, AC, and BC
    float slopeAB = (point_2->y - point_1->y) != 0 ? (float)(point_2->x - point_1->x) / (point_2->y - point_1->y) : 0;
    float slopeAC = (point_3->y - point_1->y) != 0 ? (float)(point_3->x - point_1->x) / (point_3->y - point_1->y) : 0;
    float slopeBC = (point_3->y - point_2->y) != 0 ? (float)(point_3->x - point_2->x) / (point_3->y - point_2->y) : 0;

    // Start filling scanlines
    int startY = point_1->y;
    int endY = point_2->y;
    for (int scanlineY = startY; scanlineY <= endY; scanlineY++) {
        // Calculate starting and ending x-coordinates for current scanline
        if(slopeAB != 0.0f || slopeAC != 0.0f){
            int startX = point_1->x + (scanlineY - point_1->y) * slopeAB;
            int endX = point_1->x + (scanlineY - point_1->y) * slopeAC;

            // Draw horizontal line from startX to endX
            line_graphic_representation(renderer, startX, scanlineY, endX, scanlineY, R, G, B);
        }
    }

    // Continue filling for the second half of the triangle
    startY = point_2->y;
    endY = point_3->y;
    for (int scanlineY = startY; scanlineY <= endY; scanlineY++) {
        // Calculate starting and ending x-coordinates for current scanline
        if(slopeAB != 0.0f || slopeAC != 0.0f){
            int startX = point_2->x + (scanlineY - point_2->y) * slopeBC;
            int endX = point_1->x + (scanlineY - point_1->y) * slopeAC;

            // Draw horizontal line from startX to endX
            line_graphic_representation(renderer, startX, scanlineY, endX, scanlineY, R, G, B);
        }
    }
}