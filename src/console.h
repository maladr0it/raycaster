#ifndef CONSOLE_H
#define CONSOLE_H

typedef struct console
{
    TTF_Font *font;
    SDL_Color color;
    int line_width;
    char *text;
    int cursor_pos;
} console_t;

console_t console_create(int line_width);

void console_log(console_t *console, char *format, ...);

void console_clear(console_t *console);

int console_render(console_t console, SDL_Renderer *renderer);

void console_destroy(console_t console);

#endif