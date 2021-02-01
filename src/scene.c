#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "scene.h"
#include "map.h"
#include "player.h"
#include "utils.h"
#include "ray_caster.h"
#include "drawing.h"

static const double FOV = 60 * M_PI / (180);

scene_t scene_create(SDL_Renderer *renderer, int width, int height)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if (surface == NULL)
    {
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (surface == NULL)
    {
        exit(EXIT_FAILURE);
    }

    scene_t scene = {
        .renderer = renderer,
        .surface = surface,
        .texture = texture,
    };
    return scene;
}

void scene_render(scene_t *scene, map_t map, player_t player)
{
    SDL_Surface *surface = scene->surface;
    SDL_PixelFormat *format = surface->format;
    Uint32 sky_color = SDL_MapRGB(format, 0xa8, 0xc8, 0xeb);
    Uint32 ground_color = SDL_MapRGB(format, 0x40, 0x3d, 0x39);

    // 168 200 235

    int n_rays = surface->w;
    double ray_angle = mod(player.angle - FOV / 2, 2 * M_PI);
    double ray_angle_inc = FOV / n_rays;
    ray_intersect_t intersect;

    draw_rect(surface, 0, 0, surface->w, surface->h / 2, sky_color);
    draw_rect(surface, 0, surface->h / 2, surface->w, surface->h, ground_color);

    for (int i = 0; i < n_rays; i++)
    {
        cast_ray(&intersect, map, player.x, player.y, player.angle, ray_angle);

        if (!intersect.hit)
        {
            continue;
        }

        if (intersect.tile.type == TILE_WALL)
        {
            draw_col(scene->surface, intersect, i);
        }

        ray_angle = mod(ray_angle + ray_angle_inc, 2 * M_PI);
    }

    SDL_UpdateTexture(scene->texture, NULL, scene->surface->pixels, scene->surface->pitch);
    SDL_RenderCopy(scene->renderer, scene->texture, NULL, NULL);
}

void scene_destroy(scene_t *scene)
{
    SDL_DestroyTexture(scene->texture);
    SDL_FreeSurface(scene->surface);
}
