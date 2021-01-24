#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "map.h"
#include "player.h"
#include "utils.h"
#include "ray_caster.h"
#include "drawing.h"
#include "console.h"

typedef struct scene
{
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
} scene_t;

static const double FOV = 60 * M_PI / (180);

scene_t scene_create(SDL_Renderer *renderer, int width, int height)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (surface == NULL)
    {
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELTYPE_UNKNOWN, SDL_TEXTUREACCESS_STREAMING, width, height);
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

    Uint32 wall_color = SDL_MapRGB(format, 0x00, 0xff, 0xff);
    Uint32 wall_color_shade = SDL_MapRGB(format, 0x00, 0x99, 0x99);
    Uint32 bg_color = SDL_MapRGB(format, 0, 0, 0);

    int n_rays = surface->w;
    double ray_angle = mod(player.angle - FOV / 2, 2 * M_PI);
    double ray_angle_inc = FOV / n_rays;
    ray_intersect_t intersect;

    draw_rect(surface, 0, 0, surface->w, surface->h, bg_color);

    cast_ray(&intersect, map, player.x, player.y, player.angle, player.angle);

    if (intersect.hit)
    {
        console_log("intersect %f", intersect.distance);
    }

#if 1
    for (int i = 0; i < n_rays; i++)
    {
        cast_ray(&intersect, map, player.x, player.y, player.angle, ray_angle);

        if (intersect.hit)
        {
            int height = min_int(scene->surface->h / intersect.distance, scene->surface->h);
            Uint32 color = (intersect.face == SOUTH || intersect.face == NORTH) ? wall_color_shade : wall_color;
            draw_col(scene->surface, i, height, color);
        }

        ray_angle = mod(ray_angle + ray_angle_inc, 2 * M_PI);
    }
#endif

    SDL_UpdateTexture(scene->texture, NULL, scene->surface->pixels, scene->surface->pitch);
    SDL_RenderCopy(scene->renderer, scene->texture, NULL, NULL);
}

void scene_destroy(scene_t *scene)
{
    SDL_DestroyTexture(scene->texture);
    SDL_FreeSurface(scene->surface);
}
