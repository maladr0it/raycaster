#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

SDL_Surface *texture_create(char *file);

Uint32 texture_get(SDL_Surface *texture, double u, double v);

void texture_destroy(SDL_Surface *texture);

#endif