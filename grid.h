#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "rgb.h"

typedef struct t_grid {
	RGB* rgbGrid;
	int* ccGrid;
	int size;
	int maxLabel;
} grid;

grid *gridInit(int size);
void gridInitColors(grid *g, RGB *cTab, int cNb);
RGB gridGetColor(grid *g, int x, int y);
void gridSetColor(grid *g, RGB newColor, int x, int y);
int gridGetLabel(grid *g, int x, int y);
void gridSetLabel(grid *g, int newLable, int x, int y);
int gridGetMaxLabel(grid *g);
bool gridIsUniform(grid *g);
/* int gridGetCompatibleLabel(grid *g, int x, int y); */
void gridFloodFillLabel(grid *g, int x, int y);
void gridFloodFillColor(grid *g, int x, int y);
int gridLabelCC(grid *g);
void gridPrint(grid *g, RGB *cTab, int cNb);
void gridPrintLabels(grid *g);
void gridFree(grid *g);

#endif
