#include "sdl_utils.h"
#include "game_states.h"
#include "game_menu_rendering.h"
#include "game_board_rendering.h"
#include "game_settings_rendering.h"

int main(void) {	
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;
	/* default settings for a game */
	int boardSize = 12, cNb = 4;
	game *g = NULL;

	srand(time(NULL));

	if(!sdlInit(&gWindow, &gRenderer)) {
		fprintf(stderr, "Failed to initialize!\n");
	}
	else {
		GameState gs = GAMESTATE_MENU;
		SDL_Event e;

		while(gs != GAMESTATE_QUIT) {
			switch(gs) {
				case GAMESTATE_MENU:
					/* gs internaly changed but to stay coherent... */
					gs = menuRoutine(&gWindow, &gRenderer, &e, &gs);
					break;

				case GAMESTATE_PLAYING:
					g = gameInit(boardSize, cNb);
					gs = boardRoutine(g, &gWindow, &gRenderer, &e);
					gameFree(g);
					g = NULL;
					break;

				case GAMESTATE_SETTINGS:
					gs = settingsRoutine(&gWindow, &gRenderer, &e, &boardSize, &cNb);
					break;
				default:
					gs = GAMESTATE_MENU;
					gs = menuRoutine(&gWindow, &gRenderer, &e, &gs);
			}
		}
	}
	
	sdlClose(&gWindow, &gRenderer);

	return 0;
}

