#include "map.h"

map_t map_create(int *data, int width, int height)
{
    map_t map = {
        .data = data,
        .width = width,
        .height = height,
    };
    return map;
}

int map_get(map_t map, int col, int row)
{
    if (row < 0 || row >= map.height)
    {
        return 0;
    }
    if (col < 0 || col >= map.width)
    {
        return 0;
    }
    return map.data[row * map.width + col];
}