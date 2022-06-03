#ifndef ENNEMIS
#define ENNEMIS

#include <SDL2/SDL.h>
#include "draw.h"

int move_enemy(Entity *entity, Entity * player) ;
void is_displayed(Win *app, Entity *entity) ;
void is_arrived(Entity *entity) ;
void is_enemy_or_player(Entity *entity, int isplayer) ;


#endif /* !ENNEMIS */