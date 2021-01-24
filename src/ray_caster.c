#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "map.h"
#include "console.h"
#include "utils.h"

typedef struct v2
{
    double x;
    double y;
} v2_t;

const double FOV = 60 * M_PI / (180);

static v2_t get_h_intersection_above(map_t map, double x0, double y0, double ray_angle)
{

    int y_step = -1;
    double x_step = y_step / tan(ray_angle);
    int y = floor(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (x > 0 && x < map.width && y > 0)
    {
        if (map_get(map, (int)x, y - 1) == 1)
        {
            break;
        }
        x += x_step;
        y += y_step;
    }
    v2_t intersection = {.x = x, .y = y};
    return intersection;
}

static v2_t get_h_intersection_below(map_t map, double x0, double y0, double ray_angle)
{
    int y_step = 1;
    double x_step = y_step / tan(ray_angle);
    int y = ceil(y0);
    double x = x0 + (y - y0) / tan(ray_angle);

    while (x > 0 && x < map.width && y < map.height)
    {
        if (map_get(map, (int)x, y) == 1)
        {
            break;
        }
        x += x_step;
        y += y_step;
    }
    v2_t intersection = {.x = x, .y = y};
    return intersection;
}

static v2_t get_v_intersection_left(map_t map, double x0, double y0, double ray_angle)
{
    int x_step = -1;
    double y_step = x_step * tan(ray_angle);
    int x = floor(x0);
    double y = y0 + (x - x0) * tan(ray_angle);

    while (y > 0 && y < map.height && x > 0)
    {
        if (map_get(map, x - 1, (int)y) == 1)
        {
            break;
        }
        x += x_step;
        y += y_step;
    }
    v2_t intersection = {.x = x, .y = y};
    return intersection;
}

static v2_t get_v_intersection_right(map_t map, double x0, double y0, double ray_angle)
{
    int x_step = 1;
    double y_step = x_step * tan(ray_angle);
    int x = ceil(x0);
    double y = y0 + (x - x0) * tan(ray_angle);

    while (y > 0 && y < map.height && x < map.width)
    {
        if (map_get(map, x, (int)y) == 1)
        {
            break;
        }
        x += x_step;
        y += y_step;
    }

    v2_t intersection = {.x = x, .y = y};
    return intersection;
}

void cast_rays(double *ray_distances, int n_rays, map_t map, double x0, double y0, double angle)
{
    const double COS_ANGLE = cos(angle);
    const double SIN_ANGLE = sin(angle);

    double ray_angle_inc = FOV / n_rays;
    double ray_angle = mod(angle - FOV / 2, 2 * M_PI);

    for (int i = 0; i < n_rays; i++)
    {
        v2_t h_intersection;
        v2_t v_intersection;

        if (ray_angle >= M_PI)
        {
            h_intersection = get_h_intersection_above(map, x0, y0, ray_angle);
        }
        else
        {
            h_intersection = get_h_intersection_below(map, x0, y0, ray_angle);
        }

        if (ray_angle >= M_PI_2 && ray_angle < (M_PI + M_PI_2))
        {
            v_intersection = get_v_intersection_left(map, x0, y0, ray_angle);
        }
        else
        {
            v_intersection = get_v_intersection_right(map, x0, y0, ray_angle);
        }

        // console_log("h intersect %f, %f", h_intersection.x, h_intersection.y);
        // console_log("v intersect %f, %f", v_intersection.x, v_intersection.y);

        double h_intersection_dist = (h_intersection.x - x0) * COS_ANGLE + (h_intersection.y - y0) * SIN_ANGLE;
        double v_intersection_dist = (v_intersection.x - x0) * COS_ANGLE + (v_intersection.y - y0) * SIN_ANGLE;
        ray_distances[i] = h_intersection_dist < v_intersection_dist ? h_intersection_dist : v_intersection_dist;

        ray_angle = mod(ray_angle + ray_angle_inc, 2 * M_PI);
    }
}