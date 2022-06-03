//int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode * mode);
#include <SDL2/SDL_image.h>
#include "window.h"

SDL_DisplayMode getWindowSize()
{
    SDL_DisplayMode current;

    int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);

    if(should_be_zero != 0)
    {
        // In case of error...
        SDL_Log("Could not get display mode for video display #%d: %s", 0, SDL_GetError());
        SDL_Log("%p", SDL_GetWindowDisplayIndex);
    }

    return current;
}