#ifndef GAME_H
#define GAME_H

/**
*	\file game.c
*	\author LastButNotLeast
*	\date Mars 2017
*	\brief Gestion du jeu pendant une partie.
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "rgb.h"
#include "grid.h"

#define SAVES_FOLDER "saves"

/**
*	\struct t_game
*	\brief Structure de la partie
*/
typedef struct t_game {
	grid *grid;
	int size;
	/* duplicate data, size in grid too */
	int cNb;
	int turnCount;
	RGB *cTab;
	RGB cPlayer;
} game;

/**
*	\fn gameInit(int size, int cNb)
*	\brief Initialise une partie avec une grille qui contient un nombre donné de couleurs, générées au hasard
*
*	\param size : taille de la grille à générer ie nombre de cases d'un coté
*	\param cNb : Nombre de couleurs différentes
*	\return Le jeu généré.
*/
game *gameInit(int size, int cNb);

/**
*	\fn gameFree(game *g)
*	\brief Supprime la partie
*
*	\param g : le jeu
*/
void gameFree(game *g);


/**
*	\fn gamePrint(game *g)
*	\brief Affiche la grille de jeu et d'autres informations
*
*	\param g : le jeu
*/
void gamePrint(game *g);


/**
*	\fn gamePlayTurn(game *g)
*	\brief Modifie la grille après que le joueur ait décidé d'une couleur
*
*	\param g : le jeu
*/
void gamePlayTurn(game *g);

/**
*	\fn gamePlayTurnSDL(game *g, int newColor)
*	\brief Modifie la grille en jouant la couleur newColor (utilisé par l'interface game_board_rendering
*
*	\param g : le jeu
*	\param newColor : indice de la couleur a jouer
*/
void gamePlayTurnSDL(game *g, int newColor);

/**
*	\fn gameOver(game *g)
*	\brief Teste si la partie est terminée (victoire du joueur) ou si elle continue
*
*	\param g : le jeu
*	\return true si le jeu est terminé, false sinon
*/
bool gameOver(game *);

void gameExport(game *g);
game *gameImport(char *save);

#endif
