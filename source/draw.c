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

void drawEntity(Win *app, Entity *entity)
{
    SDL_Rect dest= {entity->pos_x, entity->pos_y, entity->width, entity->height};
    // dest.x = entity->pos_x;

    SDL_RenderCopy(app->renderer, entity->texture, NULL, &dest);
}

int create_food(Win *app, Entity *entity, Entity *player)
{
    entity->RectPos = (SDL_Rect){entity->pos_x, entity->pos_y, entity->width, entity->height};
    if (move_enemy(entity, player))
        // Si une collision entre le joueur et l'ennemi est détectée
        return 1;

    is_displayed(app, entity);

    is_arrived(entity);

    return 0;
}

Entity *init_entity(Win *app, char *entityname, int isplayer, int width, int height, char *texture)
{
    Entity *entity = malloc(sizeof(Entity));
    entity->entityname = malloc(sizeof(entity->entityname));
    strcpy(entity->entityname, entityname);
    entity->isplayer = isplayer;

    is_enemy_or_player(entity, isplayer);
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
    create_food(app, fin, player);
    presentCanvas(app);
}