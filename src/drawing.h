#ifndef DRAWING_H
#define DRAWING_H

#include <SDL2/SDL.h>

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_line(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 pixel);
void draw_rect(SDL_Surface *surface, int x0, int y0, int width, int height, Uint32 pixel);
void draw_rect_centered(SDL_Surface *surface, int x0, int y0, int width, int height, Uint32 pixel);
void draw_rect_outline(SDL_Surface *surface, int x0, int y0, int width, int height, Uint32 pixel);
void draw_col(SDL_Surface *surface, int x0, int height, Uint32 pixel);

#endif