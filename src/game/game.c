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
	return g ;
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
				g->turnCount++;
				gridSetColor(g->grid, g->cTab[color], 0, 0);
				gridFloodFillColor(g->grid, 0, 0);
				gridSetLabel(g->grid, gridGetMaxLabel(g->grid) + g->turnCount, 0, 0);
				gridFloodFillLabel(g->grid, 0, 0);
				g->cPlayer = g->cTab[color];
			}
    	}
	}
}

void gamePlayTurnSDL(game *g, int newColor) {
	if(!(newColor < 0 || newColor > g->cNb-1 || rgbEqual(g->cPlayer, g->cTab[newColor]))) {
		gridSetColor(g->grid, g->cTab[newColor], 0, 0);
		gridFloodFillColor(g->grid, 0, 0);
		gridSetLabel(g->grid, gridGetMaxLabel(g->grid) + g->turnCount, 0, 0);
		gridFloodFillLabel(g->grid, 0, 0);
		g->cPlayer = g->cTab[newColor];
		g->turnCount++;
	}	
}

bool gameOver(game *g) {
	return gridIsUniform(g->grid);
}

game *gameImport(char *save) {

	char buffer[256];
	int size, colors;
	/* char *save_path = "saves/";
	 * strcat(save_path, save)
	 * FILE *fp = fopen(save_path,"r");
	 */ 

	FILE *fp = fopen(save,"r");
	if(fp == NULL) {
		printf("save not found\n");
		exit(1);
	}

	/* FILE FORMAT :
	 * grid_size cNb
	 * R G B (cNb lines)
	 * 11 12 13 ....
	 * 21 22 23 ....
	 * .............
	 */

	fgets(buffer, sizeof(buffer), fp);
	if(sscanf(buffer, "%d %d", &size, &colors) != 2) {
		printf("Not a valid save file\n");
		exit(1);
	}

	if(size < 2 || colors < 2) exit(1);
	game *g = (game *)calloc(1, sizeof(game));
	if(!g) exit(1);
	g->size = size;
	g->cNb = colors;
	g->turnCount = 0;
	g->cTab = rgbImport(fp, colors);
	g->grid = gridImport(fp, size, g->cTab, colors);
	g->cPlayer = gridGetColor(g->grid, 0, 0);

	fclose(fp);

	return g;
}

void gameExport(game *g) {

	char name[100];
	/* generate name from date */
	sprintf(name, "save_%ju.data",time(NULL));
	FILE *fp = fopen(name,"ab+");
	if(fp == NULL) exit(1);

	fprintf(fp, "%d %d\n", g->size, g->cNb);

	rgbExport(fp, g->cTab, g->cNb);
	gridExport(fp, g->grid, g->cTab, g->cNb);

	fclose(fp);

}
