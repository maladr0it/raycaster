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

typedef struct raycast_result
{
    bool hit;
    double distance;
    enum face face;
    int surface_type;
} raycast_result_t;

void cast_ray(raycast_result_t *result, map_t map, double x0, double y0, double angle, double ray_angle);

#endif