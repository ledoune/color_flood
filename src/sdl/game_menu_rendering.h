#ifndef _GAME_MENU_RENDERING
#define _GAME_MENU_RENDERING

#include "sdl_utils.h"
#include "game_states.h"

#define MENU_BUTTONS_COUNT 4

typedef struct menu {
	TTF_Font *menuFont;
	size_t fontSize;
	LTexture *bannerText;
	LTexture *bannerBackground;
	LButton *menuButtons[MENU_BUTTONS_COUNT];
	SDL_Window **gWindow;
	SDL_Renderer **gRenderer;
} menu;

/* creates Play, Load, Settings, Quit buttons and banner */
menu *menuInit(SDL_Window **gWindow, SDL_Renderer **gRenderer);
void menuInitButtons(menu *m);
void menuInitBanner(menu *m);
void menuDelete(menu *m);

/* handle evends for the 4 buttons */
void menuHandleEvents(menu *m, SDL_Event *e, GameState *gs);

/* renders the menu */
void menuRender(menu *m);
void menuBannerRender(menu *m);

/* routine for controller */
GameState menuRoutine(SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e, GameState *gs);

/* actions triggered by pressing the buttons */
void menuPlayAction(GameState *gs);
void menuLoadAction(GameState *gs);
void menuSettingsAction(GameState *gs);
void menuQuitAction(GameState *gs);

#endif
