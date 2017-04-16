#ifndef _GAME_BOARD_RENDERING_H
#define _GAME_BOARD_RENDERING_H

#include "sdl_utils.h"
#include "game_states.h"
#include "../game/game.h"

#define SIDES_MARGINS 30
#define BUTTON_MARGIN 10

static size_t buttonSide = 0;

/* creates buttons for color at the bottom of the screen */
LButton** boardInitButtons(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer);

/*handle buttons presses */
void boardHandleEvents(LButton **boardButtons, int buttonsCount, SDL_Event *e, int *playerColor);

/* render functions */
void boardRenderButtons(LButton **boardButtons, int buttonsCount);
void boardRenderBoard(game *g, SDL_Renderer **gRenderer);

/* routine for controller */
GameState boardRoutine(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e);

/* trick : pass the x coodinate, the function replace it by the player color */
void colorButtonAction(int *playerColor);

#endif
