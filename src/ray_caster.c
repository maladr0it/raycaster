#include <stdio.h>
#include "map.h"

// octant 1: x0 <= x1, y0 <= y1
double cast_ray_octant1(map_t map, double x0, double y0, double angle)
{
    // get player's offset from horizontal grid line

    double h_grid_line_offset = x0 - (int)x0;

    return 0;
}