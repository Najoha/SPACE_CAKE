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