#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

bool init();
bool load_media();
SDL_Surface *load_surface(char path[]);
void shutdown();

enum key_press_surfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *g_window = NULL;
SDL_Surface *g_screen_surface = NULL;
SDL_Surface *g_key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *g_current_surface = NULL;

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
    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_UP];
                    break;
                case SDLK_DOWN:
                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
                    break;
                case SDLK_LEFT:
                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
                    break;
                case SDLK_RIGHT:
                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;
                default:
                    g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                }
            }
        }

        SDL_BlitSurface(g_current_surface, NULL, g_screen_surface, NULL);
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
    g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("img/default.bmp");
    if (g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        return false;
    }
    g_key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("img/up.bmp");
    if (g_key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        return false;
    }
    g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("img/down.bmp");
    if (g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        return false;
    }
    g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("img/left.bmp");
    if (g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        return false;
    }
    g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("img/right.bmp");
    if (g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        return false;
    }

    return true;
}

SDL_Surface *load_surface(char path[])
{
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (surface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    return surface;
}

void shutdown()
{
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    SDL_Quit();
}