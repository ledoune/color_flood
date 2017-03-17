#include "game.h"

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Usage : %s board_size num_colors\n",argv[0]);
		exit(1);
	}
	srand(time(NULL));
	int board_size = atoi(argv[1]), num_colors = atoi(argv[2]);

	game *g = gameInit(board_size, num_colors);

	/*
	while(!gameOver(g)) {
		gamePrint(g);
		gamePlayTurn(g);
	}

	printf("YOU WON, CONGRATZ\n");
	*/
	game *test = gameImport("test.data");
	gamePrint(test);

	gameFree(g);
	gameFree(test);

	return 0;
}
