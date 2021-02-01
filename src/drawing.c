#include <math.h>
#include "drawing.h"
#include "utils.h"

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
    int from_x = clamp_int(x0, 0, surface->w);
    int to_x = clamp_int(x0 + width, 0, surface->w);
    int from_y = clamp_int(y0, 0, surface->h);
    int to_y = clamp_int(y0 + height, 0, surface->h);

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

void draw_rect_outline(SDL_Surface *surface, int x0, int y0, int width, int height, Uint32 pixel)
{
    int from_x = clamp_int(x0, 0, surface->w);
    int to_x = clamp_int(x0 + width, 0, surface->w);
    int from_y = clamp_int(y0, 0, surface->h);
    int to_y = clamp_int(y0 + height, 0, surface->h);

    for (int x = from_x; x < to_x; x++)
    {
        put_pixel(surface, x, y0, pixel);
        put_pixel(surface, x, y0 + height, pixel);
    }
    for (int y = from_y; y < to_y; y++)
    {
        put_pixel(surface, x0, y, pixel);
        put_pixel(surface, x0 + width, y, pixel);
    }
}

// TODO: consider performance here
Uint32 change_brightness(Uint32 pixel)
{
    Uint8 r, g, b;
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBX8888);
    SDL_GetRGB(pixel, format, &r, &g, &b);

    r /= 2;
    g /= 2;
    b /= 2;

    return SDL_MapRGB(format, r, g, b);
}

void draw_col(SDL_Surface *surface, ray_intersect_t intersect, int x0)
{
    int from_y;
    int to_y;
    double from_v;
    double to_v;
    if (intersect.distance >= 1)
    {
        int height = surface->h / intersect.distance;
        from_y = (surface->h - height) / 2;
        to_y = surface->h - from_y;
        from_v = 0;
        to_v = 1;
    }
    else
    {
        from_y = 0;
        to_y = surface->h;
        from_v = (1 - intersect.distance) / 2;
        to_v = 1 - from_v;
    }

    double u = intersect.texture_u;
    double v = from_v;
    double v_inc = (to_v - from_v) / (to_y - from_y);

    for (int y = from_y; y < to_y; y++)
    {
        Uint32 color = texture_get(intersect.tile.texture, u, v);
        if (intersect.face == NORTH || intersect.face == SOUTH)
        {
            color = change_brightness(color);
        }
        put_pixel(surface, x0, y, color);
        v += v_inc;
    }
}