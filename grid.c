#include "grid.h"

grid *gridInit(int size) {
	/*
	 * TODO : verif malloc return value;
	 */
	grid *g = (grid *)calloc(1,sizeof(grid));
	g->rgbGrid = (RGB *)malloc(sizeof(RGB) * size * size);
	g->size = size;
	return g;
}


void gridInitColors(grid *g, RGB *cTab, int cNb) {
	int i;
	for (i=0; i<(g->size * g->size); i++) {
		g->rgbGrid[i] = cTab[rand() % (cNb - 1)];
	}
}

void gridFree(grid *g) {
	free(g->rgbGrid);
	free(g);
}
