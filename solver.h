/**
*	\file solver.c
*	\author LastButNotLeast
*	\date Mai 2017
*	\brief Gestion du solveur
*/


#include <stdlib.h>
#include "stack.h"
#include "../game/game.h"

/**
*	\fn
*	\brief
*
*	\param
*	\param
*	\return
*/


/**
*	\fn processNeighbours(game *g, int x, int y, int *adjMatrix)
*	\brief Modifie la matrice d'adjacence.
*   \details On choisit une case de la grille, on obtient son label et le label d'une case voisine : ces deux nombres sont les coordonnées dans la matrice d'une case où on inscrit 1. On procède de même pour chaque case voisine.
*   \details Les autres cases sont laisées à 0.
*
*	\param g : la partie
*   \param x : ligne de la case choisie
*	\param y : colonne de la case choisie
*   \param adjMatrix : la matrice d'adjacence à modifier
*	\return La matriche d'adjacence modifiée
*/
void processNeighbours(game *g, int x, int y, int *adjMatrix);

/**
*	\fn solverComputeAdjMatrix(game *g)
*	\brief Crée la matrice d'adjacence associée à une partie.
*
*	\param g : la partie
*	\return la matrice d'adjacence
*/
int* solverComputeAdjMatrix(game *g);

/**
*	\fn solverComputeLblToColorArray(game *g)
*	\brief Crée un tableau qui contient en i-ème position la couleur du i-ème label
*
*	\param g : la partie
*	\return le tableau
*/
int* solverComputeLblToColorArray(game *g);

/**
*	\fn solverGameOver(const int *playerLabels, const int maxLabel)
*	\brief Teste si la partie est finie
*
*	\param g : la partie
*	\return true si la partie est finie, false sinon
*/
bool solverGameOver(const int *playerLabels, const int maxLabel);

/**
*	\fn solve(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack *best, int playedColor)
*	\brief Affiche succesivement les meilleurs solutions trouvées
*
*	\param adjMatrix : la matrice d'adjacence
*	\param lblToColor : la tableau qui associe à chaque label sa souleur
*	\param playerLabels : tableau qui contient en i-ème position 1 si le i-ème label a déjà été connecté au label actuel, 0 sinon
*	\param maxLabel : label maximal
*	\param colorRange : nombre de couleurs
*	\param maxDepth : nombre de coups joués dans la meilleure solution
*	\param currDepth : nombre de coups dans la solution actuelle
*	\param solution : la solution actuelle
*	\param best : la meilleure solution
*	\param playedColor : la couleur à jouer
*/
void solve(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack *best, int playedColor);


void solve2(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack *best, int playedColor, int* tabNeighbourLabel, int *tabSeenColors);

int* solverNeighboursLabel(game *g);
