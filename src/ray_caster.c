#include <stdio.h>
#include "map.h"

// octant 1: x0 <= x1, y0 <= y1
double cast_ray_octant1(map_t map, int x0, int y0, int x1, int y1)
{
    int d_x = x1 - x0;
    int d_y = y1 - y0;
    int x_step = 1;
    int y_step = 1;

    int error = d_x;
    int error_prev = error;
    int x = x0;
    int y = y0;

    while (x < x1)
    {
        // visit square -> check left face
        printf("%d", map_get(map, x, y));
        // if (map_get(map, x, y))

        x += x_step;
        error += 2 * d_y;

        if (error > 2 * d_x)
        {
            y += y_step;
            error -= 2 * d_x;

            if (error + error_prev < 2 * d_x)
            {
                // lower square also hit -> check left face
            }
            else if (error + error_prev > 2 * d_x)
            {
                // upper square also hit -> check bottom face
            }
        }
        error_prev = error;
    }

    return 0;
}