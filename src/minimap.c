#include <stdlib.h>
#include <math.h>
#include "minimap.h"
#include "drawing.h"
#include "console.h"
#include "utils.h"

const int PLAYER_DOT_SIZE = 5; // pixels;
const int ANGLE_LINE_LEN = 10; // pixels;
const int PX_PER_UNIT = 32;

minimap_t minimap_create(SDL_Renderer *renderer, int size)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);
    if (surface == NULL)
    {
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELTYPE_UNKNOWN, SDL_TEXTUREACCESS_STREAMING, size, size);
    if (texture == NULL)
    {
        exit(EXIT_FAILURE);
    }

    minimap_t minimap = {
        .renderer = renderer,
        .surface = surface,
        .texture = texture,
    };
    return minimap;
}

void minimap_render(minimap_t *minimap, SDL_Rect dest_rect, map_t map, player_t player)
{
    SDL_Surface *surface = minimap->surface;
    SDL_PixelFormat *format = surface->format;

    Uint32 bg_color = SDL_MapRGB(format, 0xff, 0x00, 0x00);
    Uint32 player_color = SDL_MapRGB(format, 0x00, 0x00, 0xff);
    Uint32 line_color = SDL_MapRGB(format, 0x00, 0xff, 0x00);
    Uint32 wall_color = SDL_MapRGB(format, 0xff, 0xff, 00);

    draw_rect(surface, 0, 0, surface->w, surface->h, bg_color);

    // draw map grid, fill walls
    for (int y = 0; y < map.height; y++)
    {
        for (int x = 0; x < map.width; x++)
        {
            double draw_x = surface->w / 2 + (x - player.x) * PX_PER_UNIT;
            double draw_y = surface->h / 2 + (y - player.y) * PX_PER_UNIT;
            if (map_get(map, x, y) == 1)
            {
                draw_rect(surface, draw_x, draw_y, PX_PER_UNIT, PX_PER_UNIT, wall_color);
            }
            draw_rect_outline(surface, draw_x, draw_y, PX_PER_UNIT, PX_PER_UNIT, line_color);
        }
    }

    // draw player
    draw_line(surface, surface->w / 2, surface->h / 2, surface->w / 2 + ANGLE_LINE_LEN * cos(player.angle), surface->w / 2 + ANGLE_LINE_LEN * sin(player.angle), player_color);
    draw_rect_centered(surface, surface->w / 2, surface->h / 2, PLAYER_DOT_SIZE, PLAYER_DOT_SIZE, player_color);

    SDL_UpdateTexture(minimap->texture, NULL, minimap->surface->pixels, minimap->surface->pitch);
    SDL_RenderCopy(minimap->renderer, minimap->texture, NULL, &dest_rect);
}

void minimap_destroy(minimap_t *minimap)
{
    SDL_DestroyTexture(minimap->texture);
    SDL_FreeSurface(minimap->surface);
}
