#include <stdio.h>
#include "window.h"
#include "input.h"
#include "draw.h"
#include "init.h"
#include "ennemis.h"
#include "debug.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    Win *app = malloc(sizeof(Win));
    // On initialise le générateur de nombre aléatoires
    srand(time(NULL));

    if (initSDL(app) < 0)
    {
        return -1;
    }

    // Génération de toutes les entités (joueur, ennemis et message de game over)
    Entity *gateau = init_entity(app, "Gâteau", 1, 128, 128, "ressource/gateau.png");
    Entity *salade = init_entity(app, "Salade", 0, 64, 64, "ressource/salade.png");
    Entity *carotte = init_entity(app, "Carotte", 0, 64, 64, "ressource/carotte.png");
    Entity *banane = init_entity(app, "Banane", 0, 64, 64, "ressource/banane.png");
    Entity *fin = init_entity(app, "Panneau Fin", 1, 250, 250, "ressource/game_over.png");

    int Game_Over = 0;

    while (Game_Over == 0)
    {
        prepareCanvas(app);
        create_food(app, gateau, gateau);
        // La fin du programme est gérée par l'input handler (SDL_QUIT, croix en haut de la fenêtre)
        if (input_handler(gateau) == -1)
            return 0;

        // Si le joueur touche un ennemi, il a perdu : on prépare donc le game over
        if (create_food(app, salade, gateau))
            Game_Over = 1;
        if (create_food(app, carotte, gateau))
            Game_Over = 1;
        if (create_food(app, banane, gateau))
            Game_Over = 1;
        presentCanvas(app);

        // Temps entre chaque frame
        SDL_Delay(16);
    }
    // On va centrer le message de fin
    drawFin(app, fin, gateau);
    // On l'affiche pendant 5 secondes
    SDL_Delay(5000);

    return 0;
}