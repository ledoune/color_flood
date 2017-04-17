#include "game_menu_rendering.h"

menu* menuInit(SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	menu *newMenu = (menu *)calloc(1, sizeof(menu));

	newMenu->bannerText = NULL;
	newMenu->bannerBackground = NULL;
	newMenu->gWindow = gWindow;
	newMenu->gRenderer = gRenderer;
	newMenu->fontSize = 40;
	newMenu->menuFont = TTF_OpenFont("./src/sdl/fonts/CaviarDreams.ttf", newMenu->fontSize);

	menuInitButtons(newMenu);
	menuInitBanner(newMenu);

	return newMenu;
}


void menuInitButtons(menu *m) {
	m->menuButtons[0] = sdlCreateButton(m->gWindow,
								 m->gRenderer,
								 "Play",
								 m->menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 m->fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 2/6 - (m->fontSize + 25) / 2,
								 (void (*)(int *))menuPlayAction);

	m->menuButtons[1] = sdlCreateButton(m->gWindow,
								 m->gRenderer,
								 "Load (WIP)",
								 m->menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 m->fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 3/6 - (m->fontSize + 25) / 2,
								 (void (*)(int *))menuLoadAction);
	
	m->menuButtons[2] = sdlCreateButton(m->gWindow,
								 m->gRenderer,
								 "Settings (WIP)",
								 m->menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 m->fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 4/6 - (m->fontSize + 25) / 2,
								 (void (*)(int *))menuSettingsAction);
	
	m->menuButtons[3] = sdlCreateButton(m->gWindow,
								 m->gRenderer,
								 "Quit",
								 m->menuFont,
								 0xFF,
								 0xF8,
								 0xDC,
								 SCREEN_WIDTH,
								 m->fontSize + 25,
								 0,
								 SCREEN_HEIGHT * 5/6 - (m->fontSize + 25) / 2,
								 (void (*)(int *))menuQuitAction);
	
}

void menuInitBanner(menu *m) {

	/* text */
	SDL_Color c = {0x00, 0x00, 0x00};
	m->bannerText = LTexture_New();
	LTexture_Init(m->bannerText, m->gWindow, m->gRenderer);
	LTexture_SetFont(m->bannerText, m->menuFont);
	LTexture_LoadFromRenderedText(m->bannerText, "COLOR FLOOD", c);

	/* background ? */
}

void menuDelete(menu *m) {
	int i;
	for(i=0; i<MENU_BUTTONS_COUNT; i++) {
		LButton_Delete(m->menuButtons[i]);
		m->menuButtons[i] = NULL;
	}
	LTexture_Delete(m->bannerText);
	LTexture_Delete(m->bannerBackground);
	TTF_CloseFont(m->menuFont);

	m->bannerText = NULL;
	m->bannerBackground = NULL;
	m->menuFont = NULL;
	m->gWindow = NULL;
	m->gRenderer = NULL;


	free(m);

}

void menuHandleEvents(menu *m, SDL_Event *e, GameState *gs) {
	int i;
	for(i=0; i<MENU_BUTTONS_COUNT; i++) {
		LButton_HandleEvent(m->menuButtons[i], e, (int *)gs);
	}
}

void menuRender(menu *m) {
	int i;
	for(i=0; i<MENU_BUTTONS_COUNT; i++) {
		LButton_Render(m->menuButtons[i]);
	}
	menuBannerRender(m);
}

void menuBannerRender(menu *m) {
	LTexture_Render(m->bannerText, 
			        SCREEN_HEIGHT * 1/6 - m->fontSize / 2,
					(SCREEN_WIDTH - LTexture_GetWidth(m->bannerText)) / 2,
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);
}

GameState menuRoutine(SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e, GameState *gs) {
	menu *m = menuInit(gWindow, gRenderer);

	while((*gs) == GAMESTATE_MENU) {
		/* window background color */
		SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(*gRenderer);

		while(SDL_PollEvent(e) != 0) {
			if(e->type == SDL_QUIT) {
				*gs = GAMESTATE_QUIT;
			}
			else {
				menuHandleEvents(m, e, gs);
			}
		}
		
		menuRender(m);

		SDL_RenderPresent(*gRenderer);
	}

	menuDelete(m);
	
	return *gs;
}


void menuPlayAction(GameState *gs) {
	(*gs) = GAMESTATE_PLAYING;
}

void menuLoadAction(GameState *gs) {
	(*gs) = GAMESTATE_LOAD;
}

void menuSettingsAction(GameState *gs) {
	(*gs) = GAMESTATE_SETTINGS;
}

void menuQuitAction(GameState *gs) {
	(*gs) = GAMESTATE_QUIT;
}
