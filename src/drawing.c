#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

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

    int D = 2 * d_y - d_x;
    int x = x0;
    int y = y0;
    while (x < x1)
    {
        put_pixel(surface, x, y, pixel);
        x += x_inc;

        if (D > 0)
        {
            y += y_inc;
            D += (2 * (d_y - d_x));
        }
        else
        {
            D += (2 * d_y);
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

    int D = 2 * d_x - d_y;
    int x = x0;
    int y = y0;
    while (y < y1)
    {
        put_pixel(surface, x, y, pixel);
        y += y_inc;

        if (D > 0)
        {
            x += x_inc;
            D += (2 * (d_x - d_y));
        }
        else
        {
            D += (2 * d_x);
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