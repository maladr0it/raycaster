#include <math.h>
#include <stdio.h>
#include "player.h"

typedef struct player player_t;

const double WALK_SPEED = 100;
const double LOOK_SPEED = 10;

player_t player_create()
{
    player_t player = {
        .x = 0,
        .y = 100,
        .angle = M_PI + 0.1,
        .d_x = 0,
        .d_y = 0,
        .d_angle = 0};

    return player;
}

void player_walk(player_t *p, double dir_strafe, double dir_forward)
{
    p->d_x = WALK_SPEED * (dir_strafe * cos(p->angle) + dir_forward * cos(M_PI_2 + p->angle));
    p->d_y = WALK_SPEED * (dir_strafe * sin(p->angle) + dir_forward * sin(M_PI_2 + p->angle));
}

void player_stop_walk(player_t *p)
{
    p->d_x = 0;
    p->d_y = 0;
}

void player_look(player_t *p, double look_h)
{
    p->d_angle = look_h;
}

void player_stop_look(player_t *p)
{
    p->d_angle = 0;
}

void player_update(player_t *p, double d_t)
{
    p->x += p->d_x * d_t / 1000;
    p->y += p->d_y * d_t / 1000;
}