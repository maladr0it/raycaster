#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include "drawing.h"

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
    {
        return;
    }
    Uint32 *pixels = surface->pixels;
    pixels[y * surface->w + x] = pixel;
}

static void draw_line_gentle(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 pixel)
{
    int d_x = x1 - x0;
    int d_y = y1 - y0;
    int x_inc = 1;
    int y_inc = 1;
    if (d_y < 0)
    {
        y_inc = -1;
        d_y = -d_y;
    }

    int error = 2 * d_y - d_x;
    int x = x0;
    int y = y0;
    while (x < x1)
    {
        put_pixel(surface, x, y, pixel);
        x += x_inc;

        if (error > 0)
        {
            y += y_inc;
            error += (2 * (d_y - d_x));
        }
        else
        {
            error += (2 * d_y);
        }
    }
}

static void draw_line_steep(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 pixel)
{
    int d_x = x1 - x0;
    int d_y = y1 - y0;
    int x_inc = 1;
    int y_inc = 1;
    if (d_x < 0)
    {
        x_inc = -1;
        d_x = -d_x;
    }

    int error = 2 * d_x - d_y;
    int x = x0;
    int y = y0;
    while (y < y1)
    {
        put_pixel(surface, x, y, pixel);
        y += y_inc;

        if (error > 0)
        {
            x += x_inc;
            error += (2 * (d_x - d_y));
        }
        else
        {
            error += (2 * d_x);
        }
    }
}

void draw_line(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 pixel)
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x1 > x0)
        {
            draw_line_gentle(surface, x0, y0, x1, y1, pixel);
        }
        else
        {
            draw_line_gentle(surface, x1, y1, x0, y0, pixel);
        }
    }
    else
    {
        if (y1 > y0)
        {
            draw_line_steep(surface, x0, y0, x1, y1, pixel);
        }
        else
        {
            draw_line_steep(surface, x1, y1, x0, y0, pixel);
        }
    }
}

void draw_rect(SDL_Surface *surface, int x0, int y0, int width, int height, Uint32 pixel)
{
    int from_x = x0 < 0 ? 0 : x0;
    int to_x = x0 + width > surface->w ? surface->w : x0 + width;
    int from_y = y0 < 0 ? 0 : y0;
    int to_y = y0 + height > surface->h ? surface->h : y0 + height;

    for (int y = from_y; y < to_y; y++)
    {
        for (int x = from_x; x < to_x; x++)
        {
            put_pixel(surface, x, y, pixel);
        }
    }
}

void draw_rect_centered(SDL_Surface *surface, int x0, int y0, int width, int height, Uint32 pixel)
{
    draw_rect(surface, x0 - width / 2, y0 - width / 2, width, height, pixel);
}