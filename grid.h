#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <time.h>
#include "colors.h"
#include <stdbool.h>

typedef struct t_grid {
	RGB* rgbGrid;
	int size;
} grid;

grid *gridInit(int size);
void gridInitColors(grid *g, RGB *cTab, int cNb);
void gridFree(grid *g);
/*
 * TODO : return int for errors ?
 * int gridSetColors(grid *g, RGB newColor, int x, int y);
 * RGB gridGetColor(grid *g, int x, int y);
 * type? gridPlayerGetCC(grid *g, RGB playerColor);
 * int gridPlayerSetColor(type? CC, RGB newColor);
 * bool gridPlayerVictory(grid *g);
 *
 */ 

#endif
