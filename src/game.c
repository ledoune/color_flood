#include "game.h"

game *gameInit(int size, int cNb) {
	if(size < 2 || cNb < 2) exit(1);
	game *g = (game *)calloc(1, sizeof(game));
	if(!g) exit(1);
	g->size = size;
	g->cNb = cNb;
	g->cTab = rgbArrayGenRand(cNb);
	while(rgbArrayHasDuplicate(g->cTab,cNb)) g->cTab = rgbArrayGenRand(cNb);
	g->grid = gridInit(size);
	gridInitColors(g->grid, g->cTab, cNb);
	g->cPlayer = gridGetColor(g->grid, 0, 0);
	return(g);
}	

void gamePrint(game *g) {
	printf("Color Flood :\nSize : %2d nb_Colors : %2d\n", g->size, g->cNb);
	printf("Colors available :\n");
	rgbArrayPrint(g->cTab, g->cNb);
	printf("Board state:\n");
	gridPrint(g->grid, g->cTab, g->cNb);
	/* tests */
	printf("Labels:\n");
	gridPrintLabels(g->grid);
	/* end tests */
	printf("Player's color: %d\n", rgbColorToInt(g->cPlayer,g->cTab,g->cNb));
	rgbPrint(g->cPlayer);
}

void gameFree(game *g) {
	free(g->cTab);
	gridFree(g->grid);
	free(g);
}

void gamePlayTurn(game *g) {
	char line[256];
	int color;
	printf("Enter new color: \n");
	if (fgets(line, sizeof(line), stdin)) {
    		if (1 == sscanf(line, "%d", &color)) {
			if(color < 0 || color > g->cNb-1 || rgbEqual(g->cPlayer, g->cTab[color])) {
				printf("Not a valid color\n");
			}
			else {
				gridSetColor(g->grid, g->cTab[color], 0, 0);
				gridFloodFillColor(g->grid, 0, 0);
				gridSetLabel(g->grid, gridGetMaxLabel(g->grid) + g->turnCount, 0, 0);
				gridFloodFillLabel(g->grid, 0, 0);
				g->cPlayer = g->cTab[color];
				g->turnCount++;
			}
    		}
	}
}

bool gameOver(game *g) {
	return(gridIsUniform(g->grid));
}
