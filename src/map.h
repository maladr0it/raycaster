#ifndef MAP_H
#define MAP_H

typedef struct map
{
    int width;
    int height;
    int *data;
} map_t;

map_t map_create(int *data, int width, int height);
int map_get(map_t map, int col, int row);

#endif