#include "game.h"

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Usage : %s board_size num_colors\n",argv[0]);
		exit(1);
	}
	srand(time(NULL));
	int board_size = atoi(argv[1]), num_colors = atoi(argv[2]);

	game *game = gameInit(board_size, num_colors);
	while(!gameOver(game)) {
		gamePrint(game);
		gamePlayTurn(game);
	}
	printf("YOU WON, CONGRATZ\n");
	gameFree(game);

	return 0;
}
