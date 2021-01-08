#include <SDL2_ttf/SDL_ttf.h>

// prints messages on screen; is faster than using printf

void console_create()
{
    TTF_Font *font = TTF_OpenFont("../assets/NewYork.ttf", 16);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, "Hello", color);
}