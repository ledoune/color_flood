#ifndef _GAME_BOARD_RENDERING_H
#define _GAME_BOARD_RENDERING_H

#include "sdl_utils.h"
#include "game_states.h"
#include "../game/game.h"

#define SIDES_MARGINS 30
#define BUTTON_MARGIN 10

typedef struct sdlBoard {
	SDL_Window **gWindow;
	SDL_Renderer **gRenderer;
	TTF_Font *bannerFont;
	game *g;
	LTexture *bannerTitle;
	LTexture *bannerTurnCounter;
	LButton *bannerButtons[2];
	LButton **boardButtons;
	GameState gs;
} sdlBoard;

/* contructor destructor */
sdlBoard *boardInit(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer);
void boardDelete(sdlBoard *b);

/* creates buttons for color at the bottom of the screen */
LButton** boardInitButtons(sdlBoard *b);
void boardInitBanner(sdlBoard *b);
void boardUpdateTurn(sdlBoard *b);

/*handle buttons presses */
void boardHandleEvents(sdlBoard *b, SDL_Event *e, int *playerColor);

/* render functions */
void boardRenderButtons(LButton **boardButtons, int buttonsCount);
void boardRenderBanner(sdlBoard *b);
void boardRenderBoard(sdlBoard *b);

/* routine for controller */
GameState boardRoutine(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e);

/* trick : pass the x coodinate, the function replace it by the player color */
void colorButtonAction(int *playerColor);
void menuButtonAction(GameState *gs);

#endif
