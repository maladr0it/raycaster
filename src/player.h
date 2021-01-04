#ifndef PLAYER_H
#define PLAYER_H

struct player
{
    double x;
    double y;
    double angle;
    double d_x;
    double d_y;
    double d_angle;
};

struct player player_create(double x, double y);
void player_walk(struct player *p, double dir_strafe, double dir_forward);
void player_stop_walk(struct player *p);
void player_look(struct player *p, double look_h);
void player_look_stop(struct player *p);
void player_update(struct player *p, double d_t);

#endif