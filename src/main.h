#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include "player.h"

struct game_state
{
    bool running;
    struct
    {
        double height;
        double width;
    } map;
    struct player player;
};

#endif