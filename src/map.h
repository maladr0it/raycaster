#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

enum map_symbol
{
    MAP_SYMBOL_WALL = 'W',
    MAP_SYMBOL_FLOOR = ' ',
};

enum tile_type
{
    TILE_FLOOR,
    TILE_WALL,
    TILE_BLANK,
};

typedef struct tile
{
    enum tile_type type;
    union
    {
        struct
        {
            SDL_Surface *texture;
        };
        struct
        {
        };
        struct
        {
        };
    };
} tile_t;

typedef struct map
{
    int width;
    int height;
    tile_t *tiles;
} map_t;

void map_create_tiles(tile_t *out_tiles, enum map_symbol *map_symbols, int len);

void map_load_assets();

map_t map_create(tile_t *tiles, int width, int height);

tile_t map_get(map_t map, int col, int row);

#endif