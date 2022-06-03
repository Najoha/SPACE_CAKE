#include "draw.h"
#include "window.h"
#include "debug.h"
#include "ennemis.h"
#include <string.h>

void prepareCanvas(Win *app)
{
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255); // Couleur du fond
    SDL_RenderClear(app->renderer);
}

void presentCanvas(Win *app)
{
    SDL_RenderPresent(app->renderer);
}

SDL_Texture *loadTexture(Win *app, char *img_path)
{
    SDL_Texture *texture;
    // texture = NULL;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", img_path);
    texture = IMG_LoadTexture(app->renderer, img_path);
    if (texture == NULL)
    {
        // Erreur lors du chargement de la texture
        printf(" Y'a pas d'images chakal %s\n", IMG_GetError());
    }
    return texture;
}

/*
**  drawEntity
*/

int drawEntity(Win *app, Entity *entity, Entity *player)
{
    entity->RectPos = (SDL_Rect){entity->pos_x, entity->pos_y, entity->width, entity->height};
    if (move_enemy(entity, player))
        // Si une collision entre le joueur et l'ennemi est détectée
        return 1;

    // L'ennemi a atteint le bord gauche, on le remet comme non affiché et à repartir depuis le bord droit
    if (entity->pos_x <= 0 && !entity->isplayer)
    {
        DEBUG_LOG(printf("Entité %s arrivée au bord !!\n", entity->entityname));
        entity->pos_x = WINDOW_WIDTH - 64;
        entity->pos_y = rand() % (WINDOW_HEIGHT - 64);
        // On demande une arrivée aléatoire de l'ennemi
        entity->hasarrived = 0;
        DEBUG_LOG(printf("entity->pos_y = %d\n", entity->pos_y));
    }

    // On détermine si une entity non affichée doit apparaître
    if (!entity->hasarrived)
    {
        if (rand() % 120 == 0)
        {
            entity->hasarrived = 1;
        }
    }

    // Si l'entity est affichable, on l'affiche
    if (entity->hasarrived)
    {
        SDL_RenderCopy(app->renderer, entity->texture, NULL, &entity->RectPos);
    }
    return 0;
}

Entity *init_entity(Win *app, char *entityname, char isplayer, int width, int height, char *texture)
{
    Entity *entity = malloc(sizeof(Entity));
    entity->entityname = malloc(30);
    strcpy(entity->entityname, entityname);
    entity->isplayer = isplayer;

    // Si l'entité est un joueur
    if (isplayer)
    {
        entity->hasarrived = 1;
        entity->speed = 10;
        entity->pos_x = 100;
        entity->pos_y = 100;
    }
    // Si l'entité est un ennemi
    else
    {
        entity->hasarrived = 0;
        // La vitesse est variable selon le type d'ennemi (nom)
        if (!strcmp(entity->entityname, "Carotte"))
        {
            entity->speed = 7;
        }
        else
        {
            entity->speed = 4;
        }
        entity->pos_x = WINDOW_WIDTH - 10;
        entity->pos_y = rand() % (WINDOW_HEIGHT - 64);

        DEBUG_LOG(printf("entity->pos_y = %d\n", entity->pos_y));
    }

    entity->width = width;
    entity->height = height;
    entity->texture = loadTexture(app, texture);

    // On sauve le Rect qui contient l'entity
    entity->RectPos = (SDL_Rect){entity->pos_x, entity->pos_y, entity->width, entity->height};

    return entity;
}

void drawFin(Win *app, Entity *fin, Entity *player) // Fonction d'affichage de la texture du Game Over
{
    if (!fin)
        // Si l'entity fin n'existe pas
        return;

    fin->pos_x = WINDOW_WIDTH / 2 - fin->width / 2;
    fin->pos_y = WINDOW_HEIGHT / 2 - fin->height / 2;
    prepareCanvas(app);
    drawEntity(app, fin, player);
    presentCanvas(app);
}