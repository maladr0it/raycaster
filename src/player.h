#ifndef PLAYER_H
#define PLAYER_H

typedef struct player
{
    double x;
    double y;
    double angle;
    double d_x;
    double d_y;
    double d_angle;
} player_t;

player_t player_create(double x, double y);

void player_walk(player_t *player, double dir_strafe, double dir_forward);

void player_stop_walk(player_t *player);

void player_look(player_t *player, double look_h);

void player_look_stop(player_t *player);

void player_update(player_t *player, double d_t);

#endif