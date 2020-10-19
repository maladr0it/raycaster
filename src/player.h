#ifndef PLAYER_H
#define PLAYER_H

struct player
{
  double x;
  double y;
  double dx;
  double dy;
};

void player_move(struct player *p, double dx, double dy);
void player_update(struct player *p, double dt);

#endif