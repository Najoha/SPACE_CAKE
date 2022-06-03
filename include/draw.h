#ifndef DRAW
#define DRAW

#include "window.h"
#include <SDL2/SDL_image.h>

typedef struct
{
    char *entityname; // Nom de l'entité
    char isplayer;    // Détermine si l'entité est le joueur ou un ennemi
    char hasarrived;  // Détermine si l'entité est déjà apparue à l'écran (permet de gérer un décalage d'arrivée des ennemis)
    int speed;        // Vitesse de déplacement de l'entité (en pixel par frame)
    int pos_x;
    int pos_y;
    int width;
    int height;
    SDL_Rect RectPos; // Rectangle déterminant la position de l'entity
    SDL_Texture *texture;
} Entity;

void prepareCanvas(Win *app);
void presentCanvas(Win *app);

SDL_Texture *loadTexture(Win *app, char *img_path);

int drawEntity(Win *win, Entity *entity, Entity *player);
void drawFin(Win *app, Entity *fin, Entity *player);

Entity *init_entity(Win *app, char *entityname, char isplayer, int width, int height, char *texture);

#endif /*!DRAW*/