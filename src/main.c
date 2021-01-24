#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"
#include "map.h"
#include "scene.h"
#include "minimap.h"
#include "inputs.h"
#include "player.h"
#include "console.h"

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;
const int MINIMAP_SIZE = 128;
SDL_Rect MINIMAP_DEST_RECT = {SCREEN_WIDTH - MINIMAP_SIZE, 0, MINIMAP_SIZE, MINIMAP_SIZE};

const int UPDATES_PER_SECOND = 60;
const int DT = 1000 / UPDATES_PER_SECOND;

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
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = SDL_CreateWindow(
        "RayCaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        exit(EXIT_FAILURE);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        exit(EXIT_FAILURE);
    }

    scene_t scene = scene_create(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    minimap_t minimap = minimap_create(renderer, MINIMAP_SIZE);
    console_init(renderer, SCREEN_WIDTH);

    struct game_state state =
        {
            .running = true,
            .map = map_create((int *)MAP_DATA, 5, 5),
            .player = player_create(2, 2),
        };

    SDL_Event e;

    while (state.running)
    {
        double d_t = DT;

        handle_input(&state);

        player_update(&(state.player), d_t);

        // clear screen
        SDL_RenderClear(renderer);
        console_clear();

        // render
        console_log("x: %f, y: %f, phi: %f", state.player.x, state.player.y, state.player.angle);

        scene_render(&scene, state.map, state.player);
        minimap_render(&minimap, MINIMAP_DEST_RECT, state.map, state.player);
        console_render();

        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}
