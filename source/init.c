#include "init.h"
#include "debug.h"

int initSDL(Win *app) // pointeur sur obj app
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVERYTHING) < 0)
    {
        // Erreur lors de l'initialisation
        printf("AH ! ça a foiré! %s\n", SDL_GetError()); // si il y a erreur renvoyer -1
        return -1;
    }

    app->window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    // SDL_WINDOW_FULLSCREEN); // créer une fenêtre avec tous les paramètres nécessaires

    if (!app->window)
    {
        // Erreur lors de la création de la fenêtre
        printf("Sorry bro la fenêtre est restée fermée il fait trop froid dehors... %d x %d  %s\n ", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_GetError());
        return -1; // fenêtre pas crée donc return -1 + erreur
    }

    int width;
    int height;
    SDL_GetWindowSize(app->window, &width, &height);
    DEBUG_LOG(printf("Dimension fenêtre : %dx%d\n", width, height));

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);

    if (!app->renderer)
    {
        // Erreur lors de la création du renderer
        printf("Sorry bro le renderer n'a pas été crée %s\n ", SDL_GetError());
        return -1; // renderer pas crée donc return -1 + erreur
    }

    return 0;
}