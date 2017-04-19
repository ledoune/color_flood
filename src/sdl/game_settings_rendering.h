#ifndef _GAME_SETTINGS_RENDERING_H
#define _GAME_SETTINGS_RENDERING_H

#include "sdl_utils.h"
#include "game_states.h"

#define SIDE_MARGIN 30
#define TEXT_MARGIN 20

typedef struct settingsScreen {
	LTexture *banner;

	int *boardSize;
	int *colorAmount;
	LTexture *mSizeQuery;
	LTextbox *mSizeInput;
	LTexture *mColorQuery;
	LTextbox *mColorInput;

	LButton *menuButton;
	GameState gs;

} settingsScreen;

/* constructor destructor */
settingsScreen* settingsInit(int *boardSize, int *colorAmount, SDL_Window **gWindow, SDL_Renderer **gRenderer);
void settingsDelete(settingsScreen *s);

/* events */
void settingsHandleEvent(settingsScreen *s, SDL_Event *e);

/* normalize input to match game settings values */
void settingsProcessInput(settingsScreen *s);

/* render */
void settingsRender(settingsScreen *s);

GameState settingsRoutine(SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e, int *boardSize, int *colorAmount);

/* menu button */
void settingsMenuAction(GameState *gs);

#endif
