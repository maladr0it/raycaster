#include <stdlib.h>
#include <stdint.h>
#include "map.h"
#include "texture.h"

SDL_Surface *wall_texture;

void map_load_assets()
{
    wall_texture = texture_create("../assets/wall_texture.bmp");
}

void map_create_tiles(tile_t *out_tiles, enum map_symbol *map_symbols, int len)
{
    for (int i = 0; i < len; i++)
    {
        tile_t tile;

        switch (map_symbols[i])
        {
        case MAP_SYMBOL_FLOOR:
            tile.type = TILE_FLOOR;
            break;
        case MAP_SYMBOL_WALL:
            tile.type = TILE_WALL;
            tile.texture = wall_texture;
            break;
        default:
            tile.type = TILE_BLANK;
        }
        out_tiles[i] = tile;
    }
}

map_t map_create(tile_t *tiles, int width, int height)
{
    map_t map = {
        .tiles = tiles,
        .width = width,
        .height = height,
    };
    return map;
}

tile_t map_get(map_t map, int col, int row)
{
    if (row < 0 || row >= map.height || col < 0 || col >= map.width)
    {
        tile_t t = {.type = TILE_BLANK};
        return t;
    }

    return map.tiles[row * map.width + col];
}