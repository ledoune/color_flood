#include "game.h"

int main(int argc, char *argv[]) {

	srand(time(NULL));

	/* generating game or loading */
	game *g = NULL;
	int board_size, num_colors;
	switch(argc) {
		case 2 :
			g = gameImport(argv[1]);
			printf("Game loaded %s\n", argv[1]);
			break;
		case 3 :
			board_size = atoi(argv[1]); num_colors = atoi(argv[2]);
			g = gameInit(board_size, num_colors);
			printf("Grid generated\n");
			break;
		default :
			printf("Usage : %s board_size num_colors\n\
			Or %s path/to/save\n",argv[0], argv[0]);
			exit(1);
	}

	while(!gameOver(g)) {
		gamePrint(g);
		gamePlayTurn(g);
	}

	printf("YOU WON, CONGRATZ\n");

	gameFree(g);

	return 0;
}
