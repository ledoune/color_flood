#include "grid.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

grid *gridInit(int size) {
	grid *g = (grid *)calloc(1,sizeof(grid));
	if(!g) exit(1);
	g->rgbGrid = (RGB *)calloc(1,sizeof(RGB) * size * size);
	if(!g->rgbGrid) exit(1);
	g->ccGrid = (int *)calloc(1,sizeof(int) * size * size);
	if(!g->ccGrid) exit(1);
	g->size = size;
	return g;
}


void gridInitColors(grid *g, RGB *cTab, int cNb) {
	assert(cNb > 0);
	int i;
	for (i=0; i<(g->size * g->size); i++) {
		g->rgbGrid[i] = cTab[rand() % cNb];
	}
	g->maxLabel = gridLabelCC(g);
}

grid *gridImport(FILE *fp, int board_size, RGB *cTab, int cNb) {

	char buffer[256];
	char *pnext;
	grid *g = gridInit(board_size);
	int cIndex;
	int i, j;

	for(i=0; i<board_size; i++) {
		fgets(buffer, sizeof(buffer), fp);
		/* reset index and line pointer */
		pnext = buffer - 1;
		j = 0;
		/* line parsing */
		do {
			do pnext++; while(*pnext == ' '); /* skip spaces */
			if(*pnext == '\0') break; /* end of string */

			if(sscanf(pnext, "%d", &cIndex) != 1 || cIndex < 0 || cIndex > cNb - 1) {
				printf("Not a valid save\n");
				exit(1);
			}

			/*move pointer to end of word */
			do pnext++; while (*pnext != ' ' && *pnext != '\0');

			gridSetColor(g, cTab[cIndex], i, j);
			j++;

		} while(*pnext != '\0');
	}

	g->maxLabel = gridLabelCC(g);

	return g;
}

void gridExport(FILE *fp, grid *g, RGB *cTab, int cNb) {
	int x,y;
	for(x=0; x < g->size; x++) {
		for(y=0; y < g->size; y++) {
			fprintf(fp, "%s%d%s",
					(y>0) ? " ":"",
					rgbColorToInt(gridGetColor(g, x, y), cTab, cNb),
					(y==g->size-1)?"\n":"");
		}

	}
}

RGB gridGetColor(grid *g, int x, int y) {
	assert(x > -1 && y > -1 && x < g->size && y < g->size);
	return(g->rgbGrid[x * g->size + y]);
}

void gridSetColor(grid *g, RGB newColor, int x, int y) {
	assert(x > -1 && y > -1 && x < g->size && y < g->size);
	g->rgbGrid[x * g->size + y] = newColor;
}

int gridGetLabel(grid *g, int x, int y) {
	assert(x > -1 && y > -1 && x < g->size && y < g->size);
	return(g->ccGrid[x * g->size + y]);
}

void gridSetLabel(grid *g, int newLabel, int x, int y) {
	assert(x > -1 && y > -1 && x < g->size && y < g->size);
	g->ccGrid[x * g->size + y] = newLabel;
}

int gridGetMaxLabel(grid *g) {
	return(g->maxLabel);
}

bool gridIsUniform(grid *g) {
	bool res = true;
	int i = 1;
	while(res && i < (g->size * g->size)) {
		res = rgbEqual(g->rgbGrid[i-1],g->rgbGrid[i]);
		i++;
	}
	return res;
}

/* FONCTIONNE PAS
 * int gridGetCompatibleLabel(grid *g, int x, int y) {
 *	int lbl = 0,possLbl;
 *	RGB curCell = gridGetColor(g, x, y);
 *	if(x>0 && rgbEqual(gridGetColor(g, x-1, y),curCell)) {
 *		possLbl = gridGetLabel(g, x-1, y);
 *		lbl = (lbl && possLbl) ? MIN(lbl,possLbl) : MAX(lbl,possLbl);
 *	}
 *	if (x<g->size-1 && rgbEqual(gridGetColor(g, x+1, y),curCell)) {
 *		possLbl = gridGetLabel(g, x+1, y);
 *		lbl = (lbl && possLbl) ? MIN(lbl,possLbl) : MAX(lbl,possLbl);
 *	}
 *	if (y>0 &&rgbEqual(gridGetColor(g, x, y-1),curCell)) {
 *		possLbl = gridGetLabel(g, x, y-1);
 *		lbl = (lbl && possLbl) ? MIN(lbl,possLbl) : MAX(lbl,possLbl);
 *	}
 *	if (y>g->size-1 && rgbEqual(gridGetColor(g, x, y+1),curCell)) {
 *		possLbl = gridGetLabel(g, x, y+1);
 *		lbl = (lbl && possLbl) ? MIN(lbl,possLbl) : MAX(lbl,possLbl);
 *	}
 *	return lbl;
 *}
 *
 *void gridLabelCC(grid *g) {
 *	int nxtLabel = 1, cmpLabel;
 *	int i,j;
 *	* double parcours pour eviter :
 *	 * rgb 		lbl
 *	 * 1 1 1 2	1 1 1 2
 *	 * 1 1 1 2  ->	1 1 1 2
 *	 * 3 3 2 2	3 3 4 2
 *	 * NB : on pourrait regarder seulement les voisins haut et gauche dans le sens
 *	 * descendant et les voisins bas et droit en remontant, mais faudrait 2 fctn
 *	*
 *	for(i=0; i<g->size; i++) {
 *		for(j=0; j<g->size; j++) {
 *			cmpLabel = gridGetCompatibleLabel(g, i, j);
 *			if(!cmpLabel) cmpLabel = nxtLabel++;
 *			gridSetLabel(g, cmpLabel, i, j);
 *		}
 *	}
 *	gridPrintLabels(g);
 *	bool correction = true;
 *	while(correction) {
 *		correction = false;
 *		for(i=g->size-1; i>=0; i--) {
 *			for(j=g->size-1; j>=0; j--) {
 *				cmpLabel = gridGetCompatibleLabel(g, i, j);
 *				if(cmpLabel && (cmpLabel < gridGetLabel(g, i, j))) {
 *					gridSetLabel(g, cmpLabel, i, j);
 *					correction = true;
 *				}
 *			}
 *		}
 *	}
 *
 *}
 */

void gridFloodFillLabel(grid *g, int x, int y) {
	assert(x > -1 && y > -1 && x < g->size && y < g->size);
	int lbl = gridGetLabel(g, x, y);
	assert(lbl);
	RGB currColor = gridGetColor(g, x, y);
	if(x>0 && rgbEqual(gridGetColor(g, x-1, y), currColor) && gridGetLabel(g, x-1, y) != lbl) {
		gridSetLabel(g, lbl, x-1, y);
		gridFloodFillLabel(g, x-1, y);
	}
	if(x<g->size-1 && rgbEqual(gridGetColor(g, x+1, y), currColor) && gridGetLabel(g, x+1, y) != lbl) {
		gridSetLabel(g, lbl, x+1, y);
		gridFloodFillLabel(g, x+1, y);
	}
	if(y>0 && rgbEqual(gridGetColor(g, x, y-1), currColor) && gridGetLabel(g, x, y-1) != lbl) {
		gridSetLabel(g, lbl, x, y-1);
		gridFloodFillLabel(g, x, y-1);
	}
	if(y<g->size-1 && rgbEqual(gridGetColor(g, x, y+1), currColor) && gridGetLabel(g, x, y+1) != lbl) {
		gridSetLabel(g, lbl, x, y+1);
		gridFloodFillLabel(g, x, y+1);
	}
}

void gridFloodFillColor(grid *g, int x, int y) {
	assert(x > -1 && y > -1 && x < g->size && y < g->size);
	RGB c = gridGetColor(g, x, y);
	int currLbl = gridGetLabel(g, x, y);
	if(x>0 && (gridGetLabel(g, x-1, y) == currLbl) && !rgbEqual(gridGetColor(g, x-1, y), c) ) {
		gridSetColor(g, c, x-1, y);
		gridFloodFillColor(g, x-1, y);
	}
	if(x<g->size-1 && (gridGetLabel(g, x+1, y) == currLbl) && !rgbEqual(gridGetColor(g, x+1, y), c) ) {
		gridSetColor(g, c, x+1, y);
		gridFloodFillColor(g, x+1, y);
	}
	if(y>0 && (gridGetLabel(g, x, y-1) == currLbl) && !rgbEqual(gridGetColor(g, x, y-1), c) ) {
		gridSetColor(g, c, x, y-1);
		gridFloodFillColor(g, x, y-1);
	}
	if(y<g->size-1 && (gridGetLabel(g, x, y+1) == currLbl) && !rgbEqual(gridGetColor(g, x, y+1), c) ) {
		gridSetColor(g, c, x, y+1);
		gridFloodFillColor(g, x, y+1);
	}
}


int gridLabelCC(grid *g) {
	int nxtLabel = 1;
	int i,j;
	for(i=0; i<g->size; i++) {
		for(j=0; j<g->size; j++) {
			if(!gridGetLabel(g, i, j)) {
				gridSetLabel(g, nxtLabel, i, j);
				nxtLabel++;
				gridFloodFillLabel(g, i, j);
			}
		}
	}
	return nxtLabel;
}

void gridPrint(grid *g, RGB *cTab, int cNb) {
	assert(cNb > 0);
	int i, j;
	for(i=0; i<g->size; i++) {
		for(j=0; j<g->size; j++) {
			printf("%3d ",rgbColorToInt(g->rgbGrid[i*g->size + j], cTab, cNb));
		}
		printf("\n");
	}
}

void gridPrintLabels(grid *g) {
	int i, j;
	for(i=0; i<g->size; i++) {
		for(j=0; j<g->size; j++) {
			printf("%3d ",gridGetLabel(g, i, j));
		}
		printf("\n");
	}
}

void gridFree(grid *g) {
	free(g->rgbGrid);
	free(g->ccGrid);
	free(g);
}
