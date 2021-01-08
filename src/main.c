#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"
#include "map.h"
#include "inputs.h"
#include "player.h"
#include "drawing.h"
#include "console.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int MINIMAP_WIDTH = 100;
const int MINIMAP_HEIGHT = 100;

int MAP_DATA[5][5] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1}};

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "RayCaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        return 1;
    }

    SDL_Surface *canvas = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    if (canvas == NULL)
    {
        return 1;
    }

    SDL_Texture *canvas_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STREAMING, canvas->w, canvas->h);
    if (canvas_texture == NULL)
    {
        return 1;
    }

    if (TTF_Init() < 0)
    {
        return 1;
    }

    struct game_state state =
        {
            .running = true,
            .map = map_create((int *)MAP_DATA, 5, 5),
            .player = player_create(2, 2),
        };

    SDL_Event e;

    while (state.running)
    {
        double d_t = 16;

        handle_input(&state);

        player_update(&(state.player), d_t);

        // clear screen
        SDL_RenderClear(renderer);
        SDL_FillRect(canvas, NULL, SDL_MapRGB(canvas->format, 0x00, 0x00, 0x00));

        // draw minimap
        SDL_Rect minimap_rect = {
            .w = MINIMAP_WIDTH,
            .h = MINIMAP_HEIGHT,
            .x = SCREEN_WIDTH - MINIMAP_WIDTH,
            .y = 0};
        SDL_FillRect(canvas, &minimap_rect, SDL_MapRGB(canvas->format, 0xff, 0x00, 0x00));

        // draw player position
        double minimap_player_x = SCREEN_WIDTH - MINIMAP_WIDTH + state.player.x * (MINIMAP_WIDTH / state.map.width);
        double minimap_player_y = MINIMAP_HEIGHT - (state.player.y) * (MINIMAP_HEIGHT / state.map.height);
        SDL_Rect minimap_player_rect = {
            .w = 4,
            .h = 4,
            .x = minimap_player_x,
            .y = minimap_player_y,
        };
        SDL_FillRect(canvas, &minimap_player_rect, SDL_MapRGB(canvas->format, 0x00, 0xff, 0x00));

        // draw player angle
        int line_end_x = minimap_player_x + 20 * cos(state.player.angle);
        int line_end_y = minimap_player_y + 20 * sin(-state.player.angle);
        draw_line(canvas, minimap_player_x, minimap_player_y, line_end_x, line_end_y, SDL_MapRGB(canvas->format, 0x00, 0x00, 0xff));

        // render to screen
        // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, canvas);
        SDL_UpdateTexture(canvas_texture, NULL, canvas->pixels, canvas->pitch);
        SDL_RenderCopy(renderer, canvas_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
