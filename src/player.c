#include <math.h>
#include <stdio.h>
#include "player.h"
#include "utils.h"

const double WALK_SPEED = 5; // metres per second
const double LOOK_SPEED = 2; // radians per second

player_t player_create(double x, double y)
{
    player_t player = {
        .x = x,
        .y = y,
        .angle = 0,
        .d_x = 0,
        .d_y = 0,
        .d_angle = 0};
    return player;
}

void player_walk(player_t *p, double dir_strafe, double dir_forward)
{
    p->d_x = WALK_SPEED * (dir_forward * cos(p->angle) + dir_strafe * cos(p->angle + M_PI_2));
    p->d_y = WALK_SPEED * (dir_forward * sin(p->angle) + dir_strafe * sin(p->angle + M_PI_2));
}

void player_stop_walk(player_t *p)
{
    p->d_x = 0;
    p->d_y = 0;
}

void player_look(player_t *p, double look_h)
{
    p->d_angle = LOOK_SPEED * look_h;
}

void player_update(player_t *p, double d_t)
{
    p->x += p->d_x * d_t / 1000;
    p->y += p->d_y * d_t / 1000;
    p->angle = mod(p->angle + p->d_angle * d_t / 1000, 2 * M_PI);
}