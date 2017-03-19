#ifndef GRID_H
#define GRID_H

/**
*	\file grid.c
*	\author LastButNotLeast
*	\date Mars 2017
*	\brief Gestion de la grille de jeu
*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "rgb.h"

/**
*	\struct t_grid
*	\brief Structure d'une grille
*
*	\details \a rgbGrid : tableau contenant les couleurs (en code RGB) des cases de la grille, mises les unes à la suite des autres
*	\n\a ccGrid : tableau contenant la composante connexe (désignée par un entier supérieur ou égal à 1 : "label") à laquelle appartient la case associée
*	\n\a size : taille de la grille, ie nombre de case sur un coté
*	\n\a maxLabel : nombre de composantes connexes
*/
typedef struct t_grid {
	RGB* rgbGrid;
	int* ccGrid;
	int size;
	int maxLabel;
} grid;

/**
*	\fn gridInit(int size)
*	\brief Initialise une grille d'une taille donnée
*
*	\param size : taille de la grille à générer ie nombre de cases d'un coté
*	\return La grille générée.
*/
grid *gridInit(int size);

/**
*	\fn gridInitColors(grid *g, RGB *cTab, int cNb)
*	\brief Génère des couleurs au hasard dans une grille, associe à chaque case son label et obtient le label maximal.
*
*	\param g : la grille dans laquelle il faut mettre des couleurs
*	\param cTab : tableau contenant les couleurs en code RGB, dans lequel on va piocher
*	\param cNb : nombre de couleurs du tableau
*/
void gridInitColors(grid *g, RGB *cTab, int cNb);

/**
*	\fn gridGetColor(grid *g, int x, int y)
*	\brief Donne la couleur d'une case d'une grille.
*
*	\param g : la grille
*	\param x : numéro de la colonne qui contient la case visée
*	\param y : numéro de la ligne qui contient la case visée
*	\return La couleur de la case.
*/
RGB gridGetColor(grid *g, int x, int y);

/**
*	\fn gridSetColor(grid *g, RGB newColor, int x, int y)
*	\brief Affecte une couleur à une case d'une grille.
*
*	\param g : la grille
*	\param newColor : la couleur à affecter en code RGB
*	\param x : numéro de la ligne qui contient la case visée
*	\param y : numéro de la colonne qui contient la case visée
*/
void gridSetColor(grid *g, RGB newColor, int x, int y);

/**
*	\fn gridGetLabel(grid *g, int x, int y)
*	\brief Obtient le label d'une case de la grille
*
*	\param g : la grille
*	\param x : numéro de la ligne qui contient la case visée
*	\param y : numéro de la colonne qui contient la case visée
*	\return Le numéro de la composante connexe de la case.
*/
int gridGetLabel(grid *g, int x, int y);

/**
*	\fn gridSetLabel(grid *g, int newLabel, int x, int y)
*	\brief Associe un label à une case de la grille
*
*	\param g : la grille
*	\param newLabel : le label à associer
*	\param x : numéro de la ligne qui contient la case visée
*	\param y : numéro de la colonne qui contient la case visée
*	\return Le numéro de la composante connexe de la case.
*/
void gridSetLabel(grid *g, int newLabel, int x, int y);

/**
*	\fn gridGetMaxLabel(grid *g)
*	\brief Obtient le plus grand label dans la grille
*	\details Ce nombre n'est pas le nombre de labels dans la grille, et par conséquent pas le nombre de composantes connexes.
*
*	\param g : la grille
*	\return Le label maximal.
*/
int gridGetMaxLabel(grid *g);

/**
*	\fn gridIsUniform(grid *g)
*	\brief Cherche si la grille est composée d'une seule couleur
*
*	\param g : la grille
*	\return true si la grille est unicolore, false sinon.
*/
bool gridIsUniform(grid *g);

/**
*	\fn gridFloodFillLabel(grid *g, int x, int y)
*	\brief Modifie le label de toutes les cases appartenant à la même composante connexe qu'une case visée, pour y associer le label de la case en question.
*
*	\param g : la grille
*	\param x : numéro de la ligne qui contient la case visée
*	\param y : numéro de la colonne qui contient la case visée
*/
void gridFloodFillLabel(grid *g, int x, int y);

/**
*	\fn gridFloodFillColor(grid *g, int x, int y)
*	\brief Modifie la couleur de toutes les cases appartenant à la même composante connexe (ie même label) qu'une case visée, pour y associer la couleur de la case en question.
*
*	\param g : la grille
*	\param x : numéro de la ligne qui contient la case visée
*	\param y : numéro de la colonne qui contient la case visée
*/
void gridFloodFillColor(grid *g, int x, int y);

/**
*	\fn gridIsUniform(grid *g)
*	\brief Associe à chaque case un label (commun aux autres cases de la même composante connexe) et obtient le plus grand label
*	\details Le label maximal n'est pas le nombre de labels dans la grille, et par conséquent pas le nombre de composantes connexes
*
*	\param g : la grille
*	\return Le plus grand label
*/
int gridLabelCC(grid *g);

/**
*	\fn gridPrint(grid *g, RGB *cTab, int cNb)
*	\brief Affiche la grille : chaque case est représentée par le rang de sa couleur (comme élément du tableau de couleurs).
*
*	\param g : la grille
*	\param cTab : tableau contenant toutes les couleurs en code RGB
*	\param cNb : nombre de couleurs différentes contenues dans le tableau
*/
void gridPrint(grid *g, RGB *cTab, int cNb);

/**
*	\fn gridPrintLabels(grid *g)
*	\brief Affiche la grille : chaque case est représentée par son label.
*
*	\param g : la grille
*/
void gridPrintLabels(grid *g);

/**
*	\fn gridFree(grid *g)
*	\brief Supprime la grille.
*
*	\param g : la grille
*/
void gridFree(grid *g);

#endif
