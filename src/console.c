#include <SDL2_ttf/SDL_ttf.h>
#include <stdlib.h>
#include "console.h"

const SDL_Color COLOR = {255, 255, 255};

// prints messages on screen; is faster than using printf

console_t console_create(int line_width)
{
    TTF_Font *font = TTF_OpenFont("../assets/NewYork.ttf", 16);
    char *text = malloc(128 * sizeof(char));
    text[0] = '\0';

    console_t console = {
        .font = font,
        .color = COLOR,
        .line_width = line_width,
        .text = text,
        .cursor_pos = 0,
    };

    return console;
}

void console_log(console_t *console, char *format, ...)
{
    va_list vals;
    char buffer[64];

    va_start(vals, format);
    int line_len = vsprintf(buffer, format, vals);
    va_end(vals);

    strcpy(console->text + console->cursor_pos, buffer);
    console->cursor_pos += line_len;

    // add a blank space to avoid a visual bug with SDL_TTF
    strcpy(console->text + console->cursor_pos, " \n");
    console->cursor_pos += 2;
}

void console_clear(console_t *console)
{
    console->text[0] = '\0';
    console->cursor_pos = 0;
}

int console_render(console_t console, SDL_Renderer *renderer)
{
    int texture_width;
    int texture_height;

    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(console.font, console.text, console.color, console.line_width);
    if (surface == NULL)
    {
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        return 1;
    }

    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
    SDL_Rect dest_rect = {0, 0, texture_width, texture_height};

    if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) < 0)
    {
        return 1;
    };

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return 0;
}

void console_destroy(console_t console)
{
    TTF_CloseFont(console.font);
    free(console.text);
}
