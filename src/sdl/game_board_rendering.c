#include "game_board_rendering.h"

LButton** boardInitButtons(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	int i;
	LButton** colorButtons = (LButton **)calloc(g->cNb, sizeof(LButton *));
	tileSide = (SCREEN_WIDTH - SIDES_MARGINS * 2 - BUTTON_MARGIN * (g->cNb -1)) / g->cNb;

	for(i=0; i<g->cNb; i++) {
		colorButtons[i] = sdlCreateButton(gWindow,
										  gRenderer,
										  NULL,
										  NULL,
										  g->cTab[i].R,
										  g->cTab[i].G,
										  g->cTab[i].B,
										  tileSide,
										  tileSide,
										  SIDES_MARGINS + i * (tileSide + BUTTON_MARGIN),
										  SCREEN_HEIGHT - SIDES_MARGINS - tileSide,
										  &colorButtonAction);
	}

	return colorButtons;
}

void boardHandleEvents(LButton **boardButtons, int buttonsCount, SDL_Event *e, int *playerColor) {
	int i;
	for(i=0; i<buttonsCount; i++) {
		/* maybe make a function in button_wrapper to check if inside */
		if(e->type == SDL_MOUSEBUTTONUP) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			LButton *b = boardButtons[i];

			bool inside = true;

			if(x < b->mPosition.x) {
				inside = false;
			}
			else if(x > b->mPosition.x + LTexture_GetWidth(b->mBackground)) {
				inside = false;
			}
			else if(y < b->mPosition.y) {
				inside = false;
			}
			else if(y > b->mPosition.y + LTexture_GetHeight(b->mBackground)) {
				inside = false;
			}
			if(inside) {
				(*playerColor) = boardButtons[i]->mPosition.x;
			}
		}

		LButton_HandleEvent(boardButtons[i], e, playerColor);
	}
}

void boardRenderButtons(LButton **boardButtons, int buttonsCount) {
	int i;
	for(i=0; i<buttonsCount; i++) {
		LButton_Render(boardButtons[i]);
	}
}

void colorButtonAction(int *playerColor) {
	/* x coodinate -> color index */
	int newColor = ((*playerColor) - SIDES_MARGINS) / (tileSide + BUTTON_MARGIN);
	(*playerColor) = newColor;
}
