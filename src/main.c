#include <SDL2/SDL.h>
#include <stdbool.h>
#include "main.h"
#include "map.h"
#include "scene.h"
#include "minimap.h"
#include "inputs.h"
#include "player.h"
#include "console.h"

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;
const int SCENE_WIDTH = 512;
const int SCENE_HEIGHT = 512;
const int MINIMAP_SIZE = 128;
SDL_Rect MINIMAP_DEST_RECT = {SCREEN_WIDTH - MINIMAP_SIZE, 0, MINIMAP_SIZE, MINIMAP_SIZE};

const int UPDATES_PER_SECOND = 60;
const int DT = 1000 / UPDATES_PER_SECOND;

// clang-format off
enum map_symbol MAP_DATA[100] = {
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
    'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W',
    'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W',
    'W', ' ', 'W', ' ', ' ', ' ', ' ', 'W', ' ', 'W',
    'W', ' ', 'W', ' ', ' ', ' ', ' ', 'W', ' ', 'W',
    'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W',
    'W', ' ', ' ', 'W', ' ', ' ', ' ', 'W', ' ', 'W',
    'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W',
    'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W', ' ', 'W',
    'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
};
// clang-format on

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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        exit(EXIT_FAILURE);
    }

    tile_t map_tiles[100];
    map_load_assets();
    map_create_tiles(map_tiles, MAP_DATA, 100);

    map_t map = map_create(map_tiles, 10, 10);
    scene_t scene = scene_create(renderer, SCENE_WIDTH, SCENE_HEIGHT);
    minimap_t minimap = minimap_create(renderer, MINIMAP_SIZE);
    console_init(renderer, SCREEN_WIDTH);

    struct game_state state =
        {
            .running = true,
            .map = map,
            .player = player_create(5, 5),
        };

    while (state.running)
    {
        console_clear();
        double d_t = DT;

        handle_input(&state);

        player_update(&(state.player), d_t);

        console_log("x: %f, y: %f, phi: %f", state.player.x, state.player.y, state.player.angle);

        // render
        SDL_RenderClear(renderer);
        scene_render(&scene, state.map, state.player);
        minimap_render(&minimap, MINIMAP_DEST_RECT, state.map, state.player);
        console_render();
        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}
