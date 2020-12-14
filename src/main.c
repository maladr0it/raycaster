#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"
#include "inputs.h"
#include "player.h"
#include "drawing.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const int MINIMAP_WIDTH = 100;
const int MINIMAP_HEIGHT = 100;

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

    SDL_Surface *screen = SDL_GetWindowSurface(window);
    if (screen == NULL)
    {
        return 1;
    }

    struct game_state state =
        {
            .running = true,
            .map = {.width = 20, .height = 20},
            .player = player_create(),
        };

    SDL_Event e;

    while (state.running)
    {
        // printf("player_x: %f, player_y: %f, player_angle: %f\n", state.player.x, state.player.y, state.player.angle);

        double d_t = 16;

        handle_input(&state);

        player_update(&(state.player), d_t);

        // clear screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

        // draw minimap
        SDL_Rect minimap_rect = {
            .w = MINIMAP_WIDTH,
            .h = MINIMAP_HEIGHT,
            .x = SCREEN_WIDTH - MINIMAP_WIDTH,
            .y = 0};
        SDL_FillRect(screen, &minimap_rect, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));

        // draw player position
        double minimap_player_x = SCREEN_WIDTH - MINIMAP_WIDTH + state.player.x * (MINIMAP_WIDTH / state.map.width);
        double minimap_player_y = MINIMAP_HEIGHT - (state.player.y) * (MINIMAP_HEIGHT / state.map.height);
        SDL_Rect minimap_player_rect = {
            .w = 10,
            .h = 10,
            .x = minimap_player_x,
            .y = minimap_player_y,
        };
        SDL_FillRect(screen, &minimap_player_rect, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));

        int line_end_x = minimap_player_x + 20 * cos(state.player.angle);
        int line_end_y = minimap_player_y + 20 * sin(-state.player.angle);
        draw_line(screen, minimap_player_x, minimap_player_y, line_end_x, line_end_y, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff));

        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
