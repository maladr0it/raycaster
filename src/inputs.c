#include "main.h"
#include "inputs.h"
#include "player.h"

// listen for keyboard inputs
void handle_input(struct game_state *state, SDL_Event e)
{
    if (e.type == SDL_QUIT)
    {
        state->running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            player_move(&(state->player), 0, -5);
            break;
        case SDLK_DOWN:
            player_move(&(state->player), 0, +5);
            break;
        default:
            break;
        }
    }
}