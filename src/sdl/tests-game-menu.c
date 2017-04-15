#include "game_menu_rendering.h"

int main(int argc, char *argv[]) {
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;

	if(!sdlInit(&gWindow, &gRenderer)) {
		fprintf(stderr, "Failed to initialize!\n");
	}
	else {
		GameState gs = GAMESTATE_MENU;
		SDL_Event e;

		LButton *menuButtons[MENU_BUTTONS_COUNT];
	   	menuInitButtons(&gWindow, &gRenderer, menuButtons);

		while(gs != GAMESTATE_QUIT) {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT) {
					gs = GAMESTATE_QUIT;
				}
				else {
					menuHandleEvents(menuButtons, &e, &gs);
				}
			}

			printf("%d\n",(int)gs);

			menuRender(menuButtons);

			SDL_RenderPresent(gRenderer);
		}
		int i;
		for(i=0; i<MENU_BUTTONS_COUNT; i++) {
			LButton_Delete(menuButtons[i]);
			menuButtons[i] = NULL;
		}
	}

	sdlClose(&gWindow, &gRenderer);

	return 0;
}
