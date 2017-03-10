#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <time.h>
#include "colors.h"

typedef struct t_grid {
	RGB* rgbGrid;
	int size;
} grid;

grid *gridInit(int size);
void gridInitColors(grid *g, RGB *cTab, int cNb);
void gridFree(grid *g);
/*
 * TODO : gridSetColors(grid *g, RGB newColor, coord);
 */ 

#endif
