/**
*	\file solveur1.h
*	\author LastButNotLeast
*	\date Mars 2017
*	\brief
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "rgb.h"
#include "grid.h"

typedef struct t_stack{
  game* g;
  int NbAttempts;
  int color;
  struct t_stack *next;
  int size;
} Stack;

typedef struct t_ensSol {
    Stack *sol;
    struct t_ensSol *next;
    int size;
} ensSol;
