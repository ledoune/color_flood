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
#include "rgb.h"
#include "grid.h"

/**
*	\struct t_game
*	\brief Structure de la partie
*
*	\details \var grid : Grille du jeu
*	\n\var size : Taille de la grille, ie nombre de cases sur un coté
*	\n\var cNb : Nombre de couleurs différentes
*	\n\var turnCount : Nombre de clic au cours de la partie
*	\n\var cTab : Tableau contenant toutes les couleurs
*	\n\var cPlayer : Couleur du joueur, ie couleur de la case en haut à gauche (première case)
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
*	\brief Initialise une partie avec une grille qui contient un nombre donné de couleurs au hasard
*
*	\param size : taille de la grille à générer ie nombre de cases d'un coté
*	\param cNb : Nombre de couleurs différentes
*	\return La grille générée.
*/
game *gameInit(int size, int cNb);

/**
*	\fn gamePrint(game *g)
*	\brief Affiche la grille de jeu et d'autres informations
*
*	\param g : la grille
*/
void gamePrint(game *g);

/**
*	\fn gameFree(game *g)
*	\brief Supprime la partie
*
*	\param g : la grille
*/
void gameFree(game *g);

/**
*	\fn gamePlayTurn(game *g)
*	\brief Modifie la grille après que le joueur ait décidé d'une couleur
*
*	\param g : la grille
*/
void gamePlayTurn(game *g);

/**
*	\fn gameOver(game *g)
*	\brief Teste si la partie est terminée (victoire du joueur) ou si elle continue
*
*	\param g : la grille
*	\return true si le jeu est terminé, false sinon
*/
bool gameOver(game *g);

#endif
