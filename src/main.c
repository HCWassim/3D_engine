// librairie
#include <stdio.h>
#include <stdlib.h>
#include "../include/SDL.h"
#include "camera.h"
#include "objects_3D.h"
#include "projection.h"
#include "matrix.h"
#include "const_var.h"
#include "map.h"

// gcc (terminal windows): gcc src/*.c  -o bin/prgm -I include -L lib -lmingw32 -lSDL2main -lSDL2

// obtenir version SDL:
void get_SDL_Version(){
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("version SDL %d.%d.%d \n", nb.major, nb.minor, nb.patch);
}

// erreur de compilation API SDL:
void SDL_exit_with_error(const char *message){
    SDL_Log(message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);

}

// limitation du nombre de FPS:
void SDL_limit_FPS(unsigned int limit){
    unsigned int ticks = SDL_GetTicks();
    if(limit < ticks) return;
    else if(limit > ticks + FPS_LIMIT) SDL_Delay(FPS_LIMIT);
    else SDL_Delay(limit - ticks);
}

// Function to apply image to screen
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
    // Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    // Set the offsets
    offset.x = x;
    offset.y = y;
    // Blit the surface
    SDL_BlitSurface(source, NULL, destination, &offset);
}

int handle_events(Camera * cam, SDL_bool * is_launch){
    int is_moving = 0;
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        // gestionnaire d'évènement:
        switch (event.type){
            // fin de programme:
            case SDL_QUIT:
                *is_launch = SDL_FALSE;
                break;
            // souris:
            case SDL_MOUSEMOTION:
                is_moving = 1;
                // mouvement souris selon x:
                if(event.motion.xrel >= 5.0f || event.motion.xrel <= -5.0f){
                    if(event.motion.xrel > 0) cam_update(cam, y_angle, DELTA_ANGLE);
                    else cam_update(cam, y_angle, -DELTA_ANGLE);
                }
                // mouvement souris selon y:
                if(event.motion.yrel >= 5.0f || event.motion.yrel <= -5.0f){
                    if(event.motion.yrel > 0) cam_update(cam, x_angle, -DELTA_ANGLE);
                    else cam_update(cam, x_angle, DELTA_ANGLE);
                }
                // clavier:
            case SDL_KEYDOWN:
                is_moving = 1;
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        cam_update(cam, z, 2.0 * DELTA);
                        break;
                    case SDLK_r:
                        cam_update(cam, z, -2.0 * DELTA);
                        break;
                    case SDLK_UP:
                        cam_update(cam, y, -2.0 * DELTA);
                        break;
                    case SDLK_DOWN:
                        cam_update(cam, y, 2.0 * DELTA);
                        break;
                    case SDLK_LEFT:
                        cam_update(cam, x, -2.0 * DELTA);
                        break;
                    case SDLK_RIGHT:
                        cam_update(cam, x, 2.0 * DELTA);
                        break;
                    default:
                        continue;
                }
                break;
            default:
                break;
        }
    }
    return is_moving;
}


int main(int argc, char **argv){
    // variable SDL:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // initialisation de la caméra:
    Camera * cam = init_camera(WIDTH, HEIGHT, 100);
//    cam->camera_pos->y += 5.0f;

    // traitement d'une erreur:
    if(SDL_Init(SDL_INIT_VIDEO) != 0) SDL_exit_with_error("ERREUR: echec initialisation du SDL");

    // création de fenêtre:
    window = SDL_CreateWindow("window sdl2",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_RESIZABLE);
    if(window == NULL) SDL_exit_with_error("ERREUR: echec initialisation fenêtre");

    // création renderer:
    renderer = SDL_CreateRenderer(window,
                                  -1 /*gestion du driver */,
                                  SDL_RENDERER_ACCELERATED /* utilisation carte graphique */);
    if(renderer == NULL) SDL_exit_with_error("ERREUR: echec initialisation de renderer");

    // paramètrage de renderer:
    if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0) SDL_exit_with_error("ERREUR: echec lors du changement de couleur");
    if(SDL_RenderDrawPoint(renderer, 100, 450) != 0) SDL_exit_with_error("ERREUR: impossible de représenter un pixel");
    SDL_RenderPresent(renderer);

    // variable de mouvement:
    SDL_bool is_launch = SDL_TRUE;

    // gestion des FPS:
    unsigned int frame_limit;

    // Gestion des vecteurs:
    Vector * tmp1 = init_vector(0,0,0), * tmp2 = init_vector(0,0,0), * tmp3 = init_vector(0,0,0);

    // Gestion des matrices:
    Matrix * ortho_matrix = init_orthographic_matrix(cam); // dim 4
    Matrix * temp_mat = init_matrix(DIM4, DIM4);

    // Gestion de la grille:
    Grid * grid = init_grid(DELTA_GRID);
    perlin_grid(grid, DELTA_GRID, DELTA_GRID, 32);
    print_grid(grid);

    // Gestion des cubes:
//    RenderCube * render_cube_lst[DELTA_GRID]; // [2 * DELTA_GRID];
    RenderCube * render_cube = init_render_cube(0, 0, 0);
    // Gestion des objets 3D:
//    RenderCube * renderCube; // = init_render_cube(0, 0, 0);

    // Boucle principal:
//    int first_loading = 1;
    float theta = 0.0f;
    translation_on_cube(render_cube->translation_cube, render_cube->translation_cube, z_translation, 3);
    while(is_launch){
//        printf("%f, %f, %f \n", cam->camera_pos->x, cam->camera_pos->y, cam->camera_pos->z);
        // calcul des FPS:
        frame_limit = SDL_GetTicks() + FPS_LIMIT;
        // gestion des évènements:
        handle_events(cam, &is_launch);
        theta += 0.001f;
        // contrôle FPS:
        SDL_RenderClear(renderer);
        // projection des objets:
        clean_camera(renderer);
        camera_cube(render_cube->translation_cube, render_cube->pov_cube, cam->camera_pos, cam->camera_angle, temp_mat);
//        rotation_on_cube(render_cube->translation_cube, rotation_z, 0.01f, temp_mat);
//        rotation_on_cube(render_cube->translation_cube, rotation_x, 0.0025f, temp_mat);
        perspective_cube(render_cube->pov_cube, render_cube->projection_cube, ortho_matrix, 1);
        cube_representation_2D(renderer, cam, render_cube, render_cube->tmp1, render_cube->tmp2, render_cube->tmp3, 0);
//        // optimisation d'affichage:
//        if(is_in_rendering(cam, renderCube->projection_cube)){
//            if((x != 0 && x != 2 * DELTA_GRID - 1 && z != 0 && z != 2 * DELTA_GRID - 1 && (big_neighbor(grid, x, z))) /*|| (cam->camera_angle->y < 0.5f && cam->camera_angle->y > -0.5f) */){
//                cube_representation_2D(renderer, cam, renderCube, renderCube->tmp1, renderCube->tmp2, renderCube->tmp3, 1);
//            }
//            else{
//                cube_representation_2D(renderer, cam, renderCube, renderCube->tmp1, renderCube->tmp2, renderCube->tmp3, 0);
//            }
//        }

//        rotation_on_vec(cam->directional_light, rotation_z, 0.1f, temp_mat);
        SDL_RenderPresent(renderer);
        // synchronisation des FPS:
        SDL_limit_FPS(frame_limit);
    }

    // Libération mémoire utilisé:
    free(window);
    free(renderer);
    free_cam(cam);
    free_matrix(ortho_matrix, ortho_matrix->rows);
    freeRenderCube(render_cube);
    free_cam(cam);
    free_vector(tmp1), free_vector(tmp2), free_vector(tmp3);
    free_matrix(temp_mat, temp_mat->rows);
    free_grid(grid, grid->size);

    // Fermeture SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}