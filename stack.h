#ifndef _STACK_H
#define _STACK_H

/**
*	\file stack.c
*	\author LastButNotLeast
*	\date Mai 2017
*	\brief Gestion des piles
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
*	\struct stack
*	\brief Structure d'une pile
*/
struct node {
    int data;
    struct node* next;
};

typedef struct node* stack;



/**
*	\fn stackNew(void)
*	\brief Crée une nouvelle pile
*
*	\return la pile créée
*/
stack stackNew(void);

/**
*	\fn stackFree(stack *s)
*	\brief Supprime une pile
*
*	\param s : la pile à supprimer
*/
void stackFree(stack *s);

/**
*	\fn stackCopy(stack s)
*	\brief Copie une pile
*	\details La pile est copiée à l'envers
*
*	\param s : la pile à copier
*	\return la pile copiée
*/
stack stackCopy(stack s);

/**
*	\fn stackPush(stack *s, int data)
*	\brief Ajoute un élément à une pile
*
*	\param s : la pile à modifier
*	\param data : l'élément à ajouter
*	\return la pile avec le nouvel élément
*/
void stackPush(stack *s, int data);

/**
*	\fn stackPop(stack *s)
*	\brief Supprime le premier élément de la pile
*
*	\param s : la pile à modifier
*	\return la pile modifiée
*/
int stackPop(stack *s);

/**
*	\fn stackSize(stack s)
*	\brief Donne la taille d'une pile
*
*	\param s : la pile
*	\return la taille de la pile
*/
int stackSize(stack s);

/**
*	\fn stackPrint(stack s)
*	\brief Affiche les éléments d'une pile, séparés par des espaces
*
*	\param s : la pile
*/
void stackPrint(stack s);

/**
*	\fn stackIsEmpty(stack s)
*	\brief Teste si une pile est vide ou non
*
*	\param s : la pile
*	\return true si la pile est vide, false sinon
*/
bool stackIsEmpty(stack s);

#endif
