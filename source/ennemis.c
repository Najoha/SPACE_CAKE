#include "draw.h"
#include "ennemis.h"
#include "window.h"
#include "debug.h"

int move_enemy(Entity *entity, Entity *player)
{
        // On ne déplace que les entités qui sont affichées.
        // Si l'ennemi n'a pas atteint le bord gauche, on peut le déplacer
        if (entity->pos_x > 0 && !entity->isplayer && entity->hasarrived)
        {
                entity->pos_x -= entity->speed;

                // Gestion des collisions entre le joueur et l'ennemi
                if (SDL_HasIntersection(&entity->RectPos, &player->RectPos) == SDL_TRUE)
                {
                        DEBUG_LOG(printf("Collision détectée entre %s et %s\n", entity->entityname, player->entityname));
                        return 1;
                }
        }
        return 0;
}

void is_displayed(Win *app, Entity *entity)
{
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
}

void is_arrived(Entity *entity)
{
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
}

void is_enemy_or_player(Entity *entity, int isplayer)
{    
    // Si l'entité est un joueur
    if (isplayer == 1)
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
}