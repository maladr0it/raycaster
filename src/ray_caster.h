#ifndef RAY_CASTER_H
#define RAY_CASTER_H

#include <stdbool.h>
#include "map.h"

enum direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct ray_intersect
{
    bool hit;
    tile_t tile;
    double distance;
    double texture_u;
    enum direction face;

} ray_intersect_t;

void cast_ray(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle);

#endif