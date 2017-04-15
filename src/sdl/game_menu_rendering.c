#include "game_menu_rendering.h"


void menuInitButtons(SDL_Window **gWindow, SDL_Renderer **gRenderer, LButton *menuButtons[MENU_BUTTONS_COUNT]) {
	int i;
	size_t fontSize = 40;
	TTF_Font *menuFont = TTF_OpenFont("./lazy.ttf", fontSize);
	menuButtons[0] = sdlCreateButton(gWindow,
								 gRenderer,
								 "Play",
								 menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 1/5 - (fontSize + 25),
								 (void (*)(int *))menuPlayAction);

	menuButtons[1] = sdlCreateButton(gWindow,
								 gRenderer,
								 "Load (WIP)",
								 menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 2/5 - (fontSize + 25),
								 (void (*)(int *))menuLoadAction);
	
	menuButtons[2] = sdlCreateButton(gWindow,
								 gRenderer,
								 "Settings (WIP)",
								 menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 3/5 - (fontSize + 25),
								 (void (*)(int *))menuSettingsAction);
	
	menuButtons[3] = sdlCreateButton(gWindow,
								 gRenderer,
								 "Quit",
								 menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 4/5 - (fontSize + 25),
								 (void (*)(int *))menuQuitAction);
	
}

void menuHandleEvents(LButton *menuButtons[], SDL_Event *e, GameState *gs) {
	int i;
	for(i=0; i<MENU_BUTTONS_COUNT; i++) {
		LButton_HandleEvent(menuButtons[i], e, (int *)gs);
	}
}

void menuRender(LButton *menuButtons[]) {
	int i;
	for(i=0; i<MENU_BUTTONS_COUNT; i++) {
		LButton_Render(menuButtons[i]);
	}
}


void menuPlayAction(GameState *gs) {
	(*gs) = GAMESTATE_PLAYING;
	/* TODO : create a game here ? */
}

void menuLoadAction(GameState *gs) {
	(*gs) = GAMESTATE_LOAD;
	/* TODO : load saves here, preview ? */
}

void menuSettingsAction(GameState *gs) {
	(*gs) = GAMESTATE_SETTINGS;
	/* TODO : rendering a settings menu here ? */
}

void menuQuitAction(GameState *gs) {
	(*gs) = GAMESTATE_QUIT;
	/* TODO : free a bunch of shit here I guess */
}
