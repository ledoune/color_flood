#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "rgb.h"
#include "grid.h"

typedef struct t_game {
	grid *grid;
	int size;
	/* duplicate data, size in grid too */
	int cNb;
	int turnCount;
	RGB *cTab;
	RGB cPlayer;
} game;

game *gameInit(int size, int cNb);
void gamePrint(game *g);
void gameFree(game *g);
void gamePlayTurn(game *g);
void gamePlayTurnSDL(game *g, int newColor);
bool gameOver(game *);
void gameExport(game *g);
game *gameImport(char *save);

#endif
