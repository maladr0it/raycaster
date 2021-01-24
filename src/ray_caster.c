#include <stdio.h>
#include <math.h>
#include <float.h>
#include "ray_caster.h"
#include "map.h"

static const double FOV = 60 * M_PI / (180);

static raycast_result_t get_h_intersection_above(map_t map, double x0, double y0, double angle, double ray_angle)
{
    raycast_result_t result;
    result.hit = false;
    result.distance = DBL_MAX;
    int y_step = -1;
    double x_step = y_step / tan(ray_angle);
    int y = floor(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (x > 0 && x < map.width && y > 0)
    {
        if (map_get(map, (int)x, y - 1) == 1)
        {
            result.hit = true;
            result.distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            result.face = SOUTH;
            result.surface_type = 1;
            return result;
        }
        x += x_step;
        y += y_step;
    }
    return result;
}

static raycast_result_t get_h_intersection_below(map_t map, double x0, double y0, double angle, double ray_angle)
{
    raycast_result_t result;
    result.hit = false;
    result.distance = DBL_MAX;
    int y_step = 1;
    double x_step = y_step / tan(ray_angle);
    int y = ceil(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (x > 0 && x < map.width && y < map.height)
    {
        if (map_get(map, (int)x, y) == 1)
        {
            result.hit = true;
            result.distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            result.face = NORTH;
            result.surface_type = 1;
            return result;
        }
        x += x_step;
        y += y_step;
    }
    return result;
}

static raycast_result_t get_v_intersection_left(map_t map, double x0, double y0, double angle, double ray_angle)
{
    raycast_result_t result;
    result.hit = false;
    result.distance = DBL_MAX;
    int x_step = -1;
    double y_step = x_step * tan(ray_angle);
    int x = floor(x0);
    double y = y0 + (x - x0) * tan(ray_angle);

    while (y > 0 && y < map.height && x > 0)
    {
        if (map_get(map, x - 1, (int)y) == 1)
        {
            result.hit = true;
            result.distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            result.face = EAST;
            result.surface_type = 1;
            return result;
        }
        x += x_step;
        y += y_step;
    }
    return result;
}

static raycast_result_t get_v_intersection_right(map_t map, double x0, double y0, double angle, double ray_angle)
{
    raycast_result_t result;
    result.hit = false;
    result.distance = DBL_MAX;
    int x_step = 1;
    double y_step = x_step * tan(ray_angle);
    int x = ceil(x0);
    double y = y0 + (x - x0) * tan(ray_angle);

    while (y > 0 && y < map.height && x < map.width)
    {
        if (map_get(map, x, (int)y) == 1)
        {
            result.hit = true;
            result.distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            result.face = WEST;
            result.surface_type = 1;
            return result;
        }
        x += x_step;
        y += y_step;
    }
    return result;
}

void cast_ray(raycast_result_t *result, map_t map, double x0, double y0, double angle, double ray_angle)
{
    raycast_result_t h_intersection;
    raycast_result_t v_intersection;

    if (ray_angle >= M_PI)
    {
        h_intersection = get_h_intersection_above(map, x0, y0, angle, ray_angle);
    }
    else
    {
        h_intersection = get_h_intersection_below(map, x0, y0, angle, ray_angle);
    }

    if (ray_angle >= M_PI_2 && ray_angle < (M_PI + M_PI_2))
    {
        v_intersection = get_v_intersection_left(map, x0, y0, angle, ray_angle);
    }
    else
    {
        v_intersection = get_v_intersection_right(map, x0, y0, angle, ray_angle);
    }

    *result = h_intersection.distance < v_intersection.distance ? h_intersection : v_intersection;
}