#ifndef _GAME_MENU_RENDERING
#define _GAME_MENU_RENDERING

#include "sdl_utils.h"
#include "game_controller.h"

#define MENU_BUTTONS_COUNT 4

/* creates Play, Load, Settings, Quit buttons */
void menuInitButtons(SDL_Window **gWindow, SDL_Renderer **gRenderer, LButton *menuButtons[MENU_BUTTONS_COUNT]);
/* handle evends for the 4 buttons */
void menuHandleEvents(LButton *menuButtons[], SDL_Event *e, GameState *gs);
/* renders the menu */
void menuRender(LButton *menuButtons[]);

/* actions triggered by pressing the buttons */
void menuPlayAction(GameState *gs);
void menuLoadAction(GameState *gs);
void menuSettingsAction(GameState *gs);
void menuQuitAction(GameState *gs);

#endif
