#include "player.h"

void player_move(struct player *p, double dx, double dy)
{
  p->dx += dx;
  p->dy += dy;
}

void player_update(struct player *p, double dt)
{
  p->x += p->dx * dt / 1000;
  p->y += p->dy * dt / 1000;
}