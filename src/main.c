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

const int MAP[5][5] = {
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

    SDL_Surface *screen = SDL_GetWindowSurface(window);
    if (screen == NULL)
    {
        return 1;
    }

    struct game_state state =
        {
            .running = true,
            .map = {.width = 5, .height = 5},
            .player = player_create(2, 2),
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

        // draw 3d world
        // for many angles, check the first wall it intercepts
        // check every square the line crosses
        // start with just the player's facing

        double fov = 1;
        double fov_range_start = state.player.angle - fov / 2;
        double fov_range_end = state.player.angle + fov / 2;
        double fov_range = fov_range_end - fov_range_start;
        double d_fov = fov_range / SCREEN_WIDTH;

        printf("\n");

        for (int col = 0; col < SCREEN_WIDTH; col++)
        {
            double angle = fov_range_start + col * d_fov;

            double x_inc = cos(angle);
            double y_inc = sin(angle);
            double x = state.player.x;
            double y = state.player.y;

            while (x > 0 && x < state.map.width && y > 0 && y < state.map.height)
            {
                // wall detected
                if (MAP[(int)y][(int)x] == 1)
                {
                    // we now have the location of the first wall you can see
                    // calculate exactly how far you are from it

                    // TODO: this isn't where the wall actually is; only the north-west corner of it
                    double wall_x = floor(x);
                    double wall_y = floor(y);

                    double d_x = state.player.x - wall_x;
                    double d_y = state.player.y - wall_y;

                    double distance = sqrt(d_x * d_x + d_y * d_y);

                    printf("angle: %f distance: %f\n", angle, distance);

                    // draw vertical line
                    double line_height = SCREEN_HEIGHT / distance;

                    for (int i = SCREEN_HEIGHT - (SCREEN_HEIGHT + line_height) / 2; i < SCREEN_HEIGHT - (SCREEN_HEIGHT - line_height) / 2; i++)
                    {
                        put_pixel(screen, col, i, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));
                    }
                    break;
                }

                x += x_inc;
                y += y_inc;
            }
        }

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
            .w = 4,
            .h = 4,
            .x = minimap_player_x,
            .y = minimap_player_y,
        };
        SDL_FillRect(screen, &minimap_player_rect, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00));

        // draw player angle
        int line_end_x = minimap_player_x + 20 * cos(state.player.angle);
        int line_end_y = minimap_player_y + 20 * sin(-state.player.angle);
        draw_line(screen, minimap_player_x, minimap_player_y, line_end_x, line_end_y, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff));

        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
