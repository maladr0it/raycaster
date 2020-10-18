#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

bool init();
bool load_media();
void shutdown();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *g_window = NULL;
SDL_Surface *g_screen_surface = NULL;
SDL_Surface *g_test_surface = NULL;

int main(int argc, char *args[])
{
    if (!init())
    {
        printf("Failed to initialize\n");
        return 1;
    };

    if (!load_media())
    {
        printf("Failed to load media\n");
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_BlitSurface(g_test_surface, NULL, g_screen_surface, NULL);
        SDL_UpdateWindowSurface(g_window);
    }

    shutdown();
    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    g_window = SDL_CreateWindow(
        "Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    g_screen_surface = SDL_GetWindowSurface(g_window);
    return true;
}

bool load_media()
{
    g_test_surface = SDL_LoadBMP("x.bmp");

    if (g_test_surface == NULL)
    {
        printf("Unable to load image! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void shutdown()
{
    SDL_FreeSurface(g_test_surface);
    g_test_surface = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    SDL_Quit();
}