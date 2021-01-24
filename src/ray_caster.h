#ifndef RAY_CASTER_H
#define RAY_CASTER_H

#include <stdbool.h>
#include "map.h"

enum face
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum surface_type
{
    WALL,
};

typedef struct ray_intersect
{
    bool hit;
    double distance;
    enum face face;
    int surface_type;
} ray_intersect_t;

void cast_ray(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle);

#endif