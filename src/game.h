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
*/
typedef struct t_game {
	grid *grid; /**< Grille du jeu */
	int size; /**< Taille de la grille, ie nombre de cases sur un coté. (duplicate data, size in grid too)*/
	int cNb; /**< Nombre de couleurs différentes*/
	int turnCount; /**< Nombre de clic au cours de la partie*/
	RGB *cTab; /**< Tableau contenant toutes les couleurs*/
	RGB cPlayer; /**< Couleur du joueur, ie couleur de la case en haut à gauche (première case)*/
} game;

/**
*	\fn gameInit(int size, int cNb)
*	\brief Initialise une partie avec une grille qui contient un nombre donné de couleurs au hasard
*
*	\param size : taille de la grille à générer ie nombre de cases d'un coté
*	\param cNb : Nombre de couleurs différentes
*	\return Le jeu généré.
*/
game *gameInit(int size, int cNb);

/**
*	\fn gamePrint(game *g)
*	\brief Affiche la grille de jeu et d'autres informations
*
*	\param g : le jeu
*/
void gamePrint(game *g);

/**
*	\fn gameFree(game *g)
*	\brief Supprime la partie
*
*	\param g : le jeu
*/
void gameFree(game *g);

/**
*	\fn gamePlayTurn(game *g)
*	\brief Modifie la grille après que le joueur ait décidé d'une couleur
*
*	\param g : le jeu
*/
void gamePlayTurn(game *g);

/**
*	\fn gameOver(game *g)
*	\brief Teste si la partie est terminée (victoire du joueur) ou si elle continue
*
*	\param g : le jeu
*	\return true si le jeu est terminé, false sinon
*/
bool gameOver(game *g);

/**
*	\fn gameImport(char *save)
*	\brief Importe une partie depuis un fichier existant
*
*	\param save : le fichier
*	\return le jeu généré
*/
game *gameImport(char *save);

/**
*	\fn gameExport(game *g)
*	\brief *Exporte une partie dans un fichier
*
*	\param g : le jeu à exporter
*/
void gameExport(game *g);

#endif
