#include <stdio.h>
#include <math.h>
#include <float.h>
#include "ray_caster.h"
#include "map.h"
#include "console.h"

static const double FOV = 60 * M_PI / (180);

static const int MAX_DIST = 16;

static void get_h_intersect_above(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle)
{
    double y_step = -1;
    double x_step = y_step / tan(ray_angle);
    double y = floor(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (fabs(x - x0) < MAX_DIST && fabs(y - y0) < MAX_DIST)
    {
        if (map_get(map, floor(x), y - 1) == 1)
        {
            intersect->hit = true;
            intersect->distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            intersect->face = SOUTH;
            intersect->surface_type = 1;
            return;
        }
        x += x_step;
        y += y_step;
    }
}

static void get_h_intersect_below(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle)
{
    double y_step = 1;
    double x_step = y_step / tan(ray_angle);
    double y = ceil(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (fabs(x - x0) < MAX_DIST && fabs(y - y0) < MAX_DIST)
    {
        if (map_get(map, floor(x), y) == 1)
        {
            intersect->hit = true;
            intersect->distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            intersect->face = NORTH;
            intersect->surface_type = 1;
            return;
        }
        x += x_step;
        y += y_step;
    }
}

static void get_v_intersect_left(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle)
{
    double x_step = -1;
    double y_step = x_step * tan(ray_angle);
    double x = floor(x0);
    double y = y0 + (x - x0) * tan(ray_angle);

    while (fabs(x - x0) < MAX_DIST && fabs(y - y0) < MAX_DIST)
    {
        if (map_get(map, x - 1, floor(y)) == 1)
        {
            intersect->hit = true;
            intersect->distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            intersect->face = EAST;
            intersect->surface_type = 1;
            return;
        }
        x += x_step;
        y += y_step;
    }
}

static void get_v_intersect_right(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle)
{
    double x_step = 1;
    double y_step = x_step * tan(ray_angle);
    double x = ceil(x0);
    double y = y0 + (x - x0) * tan(ray_angle);

    while (fabs(x - x0) < MAX_DIST && fabs(y - y0) < MAX_DIST)
    {
        if (map_get(map, x, floor(y)) == 1)
        {
            intersect->hit = true;
            intersect->distance = (x - x0) * cos(angle) + (y - y0) * sin(angle);
            intersect->face = WEST;
            intersect->surface_type = 1;
            return;
        }
        x += x_step;
        y += y_step;
    }
}

void cast_ray(ray_intersect_t *intersect, map_t map, double x0, double y0, double angle, double ray_angle)
{
    ray_intersect_t h_intersect;
    h_intersect.hit = false;
    h_intersect.distance = DBL_MAX;

    ray_intersect_t v_intersect;
    v_intersect.hit = false;
    v_intersect.distance = DBL_MAX;

    if (ray_angle > M_PI)
    {
        get_h_intersect_above(&h_intersect, map, x0, y0, angle, ray_angle);
    }
    else if (ray_angle < M_PI)
    {
        get_h_intersect_below(&h_intersect, map, x0, y0, angle, ray_angle);
    }

    if (ray_angle > M_PI_2 && ray_angle < (M_PI + M_PI_2))
    {
        get_v_intersect_left(&v_intersect, map, x0, y0, angle, ray_angle);
    }
    else if (ray_angle < M_PI_2 || ray_angle > (M_PI + M_PI_2))
    {
        get_v_intersect_right(&v_intersect, map, x0, y0, angle, ray_angle);
    }

    *intersect = h_intersect.distance < v_intersect.distance ? h_intersect : v_intersect;
}