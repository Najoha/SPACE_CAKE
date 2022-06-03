#ifndef WINDOW
#define WINDOW

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Space Cake"

typedef struct{
    SDL_Renderer    *renderer;
    SDL_Window      *window;
} Win;

SDL_DisplayMode getWindowSize();

#endif /* !WINDOW*/

/*
Définition de tout ce qui est utile pour la création de notre
fenêtre

Fichier main dans source.
*/
