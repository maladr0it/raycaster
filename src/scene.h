#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"

typedef struct scene
{
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
} scene_t;

scene_t scene_create(SDL_Renderer *renderer, int width, int height);
void scene_render(scene_t *scene, map_t map, player_t player);
void scene_destroy(scene_t *scene);

#endif