#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "inputs.h"
#include "player.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
const double DT = 16;

static void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

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
            .player = {.x = 0, .y = 0, .dx = 0, .dy = 0},
        };

    SDL_Event e;

    while (state.running)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            handle_input(&state, e);
        }

        player_update(&(state.player), DT);

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
        SDL_Rect player_rect = {
            .h = 10, .w = 10, .x = state.player.x, .y = state.player.y};
        SDL_FillRect(screen, &player_rect, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));

        SDL_UpdateWindowSurface(window);
    }

    return 0;
}

static void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = surface->pixels;
    pixels[y * surface->w + x] = pixel;
}