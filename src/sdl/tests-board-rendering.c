#include "game_board_rendering.h"

int main(int argc, char *argv[]) {
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;

	srand(time(NULL));

	if(!sdlInit(&gWindow, &gRenderer)) {
		fprintf(stderr, "Failed to initialize!\n");
	}
	else {
		game *g = NULL;
		g = gameInit(10,5);
		int playerColor = -1;
		/* TODO : change game struct to work more with integers and less with RGB */

		SDL_Event e;
		LButton **boardButtons = boardInitButtons(g, &gWindow, &gRenderer);

		bool quit = false;
		while(!quit) {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT) {
					quit = true;
				}
				else {
					boardHandleEvents(boardButtons, g->cNb, &e, &playerColor);
				}
			}

			gamePlayTurnSDL(g, playerColor);

			boardRenderButtons(boardButtons, g->cNb);
			boardRenderBoard(g, &gRenderer);

			SDL_RenderPresent(gRenderer);

			if(gameOver(g)) {
				quit = true;
			}
		}
		int i;
		for(i=0; i<g->cNb; i++) {
			LButton_Delete(boardButtons[i]);
			boardButtons[i] = NULL;
		}
	}

	sdlClose(&gWindow, &gRenderer);

	return 0;
}
