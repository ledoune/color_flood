#ifndef RGB_H
#define RGB_H

/**
*	\file rgb.c
*	\author LastButNotLeast
*	\date Mars 2017
*	\brief Gestion des couleurs
*/
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
*	\struct t_RGB
*	\brief Structure d'une couleur en utilisant le code rgb
*/
typedef struct t_RGB {
	unsigned char R; /*!< pourcentage de rouge */
	unsigned char G; /*!< pourcentage de vert */
	unsigned char B; /*!< pourcentage de bleu */
} RGB;


/**
*	\fn rgbNew(int R, int G, int B)
*	\brief Créer une couleur en utilisant les pourcentages donnés de chaque composante
*
*	\param R : pourcentage de rouge (en 256)
*	\param G : pourcentage de vert (en 256)
*	\param B : pourcentage de bleu (en 256)
*	\return : la couleur (enc ode RGB)
*/
RGB rgbNew(int R, int G, int B);

/**
*	\fn rgbImport(FILE *fp, int cNb)
*	\brief Importe des couleurs à partir d'un fichier
*
*	\param fp : le fichier
*	\param cNb : nombre de couleurs différentes
*	\return un tableau contenant les couleurs importées
*/
RGB* rgbImport(FILE *fp, int cNb);

/**
*	\fn rgbExport(FILE *fp, RGB *cTab, int cNb)
*	\brief Exporte un tableau de couleurs dans un fichier
*
*	\param fp : le fichier
*	\param cTab : le tableau de couleurs
*	\param cNb : le nombre de couleurs différentes
*/
void rgbExport(FILE *fp, RGB *cTab, int cNb);

/**
*	\fn rgbPrint(RGB c)
*	\brief Affiche les trois composantes de la couleur
*
*	\param c : une couleur
*/
void rgbPrint(RGB c);

/**
*	\fn rgbArrayPrint(RGB *tab, int size)
*	\brief Affiche un tableau contenant plusieurs couleurs
*
*	\param tab : le tableau qui contient les couleurs
*	\param size : nombre de couleurs dans le tableau
*/
void rgbArrayPrint(RGB *tab, int size);

/**
*	\fn rgbGenRand()
*	\brief Genère une couleur au hasard.
*
*	\return La couleur générée avec le code RGB.
*/
RGB rgbGenRand();

/**
*	\fn rgbArrayGenRand(int nb)
*	\brief Génère un tableau de couleurs au hasard.
*
*	\details : la taille du tableau doit être non nulle.
*	\param nb : taille du tableau à générer.
*	\return Le tableau de couleurs avec le code RGB.
*/
RGB* rgbArrayGenRand(int nb);

/**
*	\fn rgbEqual(RGB c1, RGB c2)
*	\brief Teste deux couleurs pour savoir si ce sont les mêmes.
*
*	\param c1 : la première couleur
*	\param c2 : la deuxième couleur
*	\return true si les couleurs sont les mêmes, false sinon.
*/
bool rgbEqual(RGB c1, RGB c2);

/**
*	\fn rgbColorToInt(RGB c, RGB* tab, int size)
*	\brief Cherche une couleur donnée dans un tableau de couleurs.
*
*	\param c : la couleur cherchée
*	\param tab : le tableau de couleurs
*	\param size : la taille du tableau
*	\return Le rang de la couleur dans le tableau si elle a été trouvée ; -1 sinon.
*/
int rgbColorToInt(RGB c, RGB* tab, int size);

/**
*	\fn rgbArrayFree(RGB *tab)
*	\brief Supprime un tableau de couleurs.
*
*	\param tab : le tableau à supprimer
*/
void rgbArrayFree(RGB *tab);

/**
*	\fn rgbArrayHasDuplicate(RGB *tab, int size)
*	\brief Teste une tableau de couleurs pour savoir si deux couleurs sont les mêmes
*
*	\param tab : le tableau de couleurs
*	\param size : la taille du tableau
*	\return true s'il y a deux couleurs identiques, false sinon.
*/
bool rgbArrayHasDuplicate(RGB *tab, int size);

#endif
