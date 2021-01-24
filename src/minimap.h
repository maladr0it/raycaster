#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"

typedef struct minimap
{
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
} minimap_t;

minimap_t minimap_create(SDL_Renderer *renderer, int size);
void minimap_render(minimap_t *minimap, SDL_Rect dest_rect, map_t map, player_t player);
void minimap_destroy(minimap_t *minimap);

#endif