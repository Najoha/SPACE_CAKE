#include "input.h"
#include "draw.h"
#include "window.h"
#include <stdio.h>

int input_handler(Entity *entity)
{
    SDL_Event event;

    SDL_PollEvent(&event); // on passe l'adresse de la structure event

    switch (event.type)
    {
        // Fermeture du programme (croix en haut de la fenêtre)
    case SDL_QUIT:
        return -1;
        // Déplacements du joueur
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            entity->pos_y -= entity->speed;
            break;
        case SDLK_DOWN:
            entity->pos_y += entity->speed;
            break;
        case SDLK_RIGHT:
            entity->pos_x += entity->speed;
            break;
        case SDLK_LEFT:
            entity->pos_x -= entity->speed;
            break;
        }
        break;
    case SDL_KEYUP:
        break;
    default:
        break;
    }

    // Gestion des collisions du joueur avec les murs (on ne peut pas dépasser de l'écran)
    SDL_DisplayMode current = getWindowSize();

    if (entity->pos_y < 0)
    {
        entity->pos_y = 0;
    }
    else if (entity->pos_y > (current.h) - entity->height)
    {
        entity->pos_y -= 4;
    }

    if (entity->pos_x < 0)
    {
        entity->pos_x = 0;
    }
    else if (entity->pos_x > (current.w) - entity->height)
    {
        entity->pos_x -= 4;
    }

    return 0;
}