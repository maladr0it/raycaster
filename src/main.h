#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include "player.h"
#include "map.h"

struct game_state
{
    bool running;
    map_t map;
    player_t player;
};

#endif