#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "map.h"
#include "console.h"

typedef struct v2
{
    double x;
    double y;
} v2_t;

v2_t get_h_intersection_above(map_t map, double x0, double y0, double ray_angle)
{
    int y_step = 1;
    double x_step = y_step / tan(ray_angle);
    int y = ceil(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (x > 0 && x < map.width && y < map.height)
    {
        console_log("checking %f, %d", x, y);
        if (map_get(map, floor(x), y) == 1)
        {
            break;
        }
        x += x_step;
        y += y_step;
    }
    v2_t intersection = {.x = x, .y = y};
    return intersection;
}

v2_t get_h_intersection_below(map_t map, double x0, double y0, double ray_angle)
{
    int y_step = -1;
    double x_step = y_step / tan(ray_angle);
    int y = floor(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (x > 0 && x < map.width && y > 0)
    {
        if (map_get(map, ceil(x), y) == 1)
        {
            break;
        }
        x += x_step;
        y += y_step;
    }
    v2_t intersection = {.x = x, .y = y};
    return intersection;
}

double cast_ray(map_t map, double x0, double y0, double angle)
{
    double ray_angle = angle;
    v2_t h_intersection;

    if (ray_angle < M_PI)
    {
        h_intersection = get_h_intersection_above(map, x0, y0, ray_angle);
    }
    else
    {
        h_intersection = get_h_intersection_above(map, x0, y0, ray_angle);
    }

    if (ray_angle < M_PI_2 || ray_angle >= (M_PI + M_PI_2))
    {
        // test v_right
    }
    else
    {
        // test v_left
    }
    console_log("intersect x: %f", h_intersection.x);
    console_log("intersect y: %f", h_intersection.y);

    return 0;
}