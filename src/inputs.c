#include <SDL2/SDL.h>
#include "main.h"
#include "inputs.h"
#include "player.h"
#include "math.h"

const Uint8 *keyboard_state;

void handle_input(struct game_state *state)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            state->running = false;
        }
    }

    // movement
    double input_strafe = 0;
    double input_forward = 0;
    keyboard_state = SDL_GetKeyboardState(NULL);

    if (keyboard_state[SDL_SCANCODE_A])
    {
        input_strafe -= 1;
    }
    if (keyboard_state[SDL_SCANCODE_D])
    {
        input_strafe += 1;
    }
    if (keyboard_state[SDL_SCANCODE_W])
    {
        input_forward += 1;
    }
    if (keyboard_state[SDL_SCANCODE_S])
    {
        input_forward -= 1;
    }

    double input_magnitude = sqrt(pow(input_strafe, 2) + pow(input_forward, 2));

    if (input_magnitude > 0)
    {
        player_walk(&(state->player), input_strafe / input_magnitude, input_forward / input_magnitude);
    }
    else
    {
        player_stop_walk(&(state->player));
    }

    // looking
    double input_look = 0;

    if (keyboard_state[SDL_SCANCODE_LEFT])
    {
        input_look -= 1;
    }
    if (keyboard_state[SDL_SCANCODE_RIGHT])
    {
        input_look += 1;
    }

    player_look(&(state->player), input_look);
}