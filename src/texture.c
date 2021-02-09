#include <math.h>
#include "texture.h"
#include "console.h"
#include "utils.h"

SDL_Surface *texture_create(char *file)
{
    SDL_Surface *surface = SDL_LoadBMP(file);
    if (surface == NULL)
    {
        exit(EXIT_FAILURE);
    }

    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBX8888);
    SDL_Surface *converted = SDL_ConvertSurface(surface, format, 0);
    SDL_FreeSurface(surface);

    return converted;
}

Uint32 texture_get(SDL_Surface *texture, double u, double v)
{
    int x = u * (texture->w - 1) + 0.5;
    int y = v * (texture->h - 1) + 0.5;
    Uint32 *pixels = texture->pixels;
    return pixels[y * texture->w + x];
}

void texture_destroy(SDL_Surface *texture)
{
    SDL_FreeFormat(texture->format);
    SDL_FreeSurface(texture);
}