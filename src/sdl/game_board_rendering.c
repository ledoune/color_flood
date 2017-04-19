#include "game_board_rendering.h"

static size_t buttonSide = 0;

sdlBoard* boardInit(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	sdlBoard *newBoard = (sdlBoard *)calloc(1, sizeof(sdlBoard));

	newBoard->gWindow = gWindow;
	newBoard->gRenderer = gRenderer;
	newBoard->g = g;
	newBoard->boardButtons = boardInitButtons(newBoard);
	newBoard->bannerFont = TTF_OpenFont("./src/sdl/fonts/CaviarDreams.ttf", 20);
	newBoard->gs = GAMESTATE_PLAYING;

	boardInitBanner(newBoard);

	return newBoard;
}

void boardDelete(sdlBoard *b) {
	int i;
	for(i=0; i<b->g->cNb; i++) {
		LButton_Delete(b->boardButtons[i]);
		b->boardButtons[i] = NULL;
	}
	free(b->boardButtons);
	LButton_Delete(b->bannerButtons[0]);
	LButton_Delete(b->bannerButtons[1]);
	LTexture_Delete(b->bannerTitle);
	LTexture_Delete(b->bannerTurnCounter);
	TTF_CloseFont(b->bannerFont);

	b->gWindow = NULL;
	b->gRenderer = NULL;
	b->g = NULL;
	b->bannerTitle = NULL;
	b->bannerTurnCounter = NULL;
	b->boardButtons = NULL;

	free(b);
}

LButton** boardInitButtons(sdlBoard *b) {
	int i;
	LButton** colorButtons = (LButton **)calloc(b->g->cNb, sizeof(LButton *));
	buttonSide = (SCREEN_WIDTH - SIDES_MARGINS * 2 - BUTTON_MARGIN * (b->g->cNb -1)) / b->g->cNb;

	for(i=0; i<b->g->cNb; i++) {
		colorButtons[i] = sdlCreateButton(b->gWindow,
										  b->gRenderer,
										  NULL,
										  NULL,
										  b->g->cTab[i].R,
										  b->g->cTab[i].G,
										  b->g->cTab[i].B,
										  buttonSide,
										  buttonSide,
										  SIDES_MARGINS + i * (buttonSide + BUTTON_MARGIN),
										  SCREEN_HEIGHT - SIDES_MARGINS - buttonSide,
										  &colorButtonAction);
	}

	return colorButtons;
}

void boardInitBanner(sdlBoard *b) {
	int w, h;

	TTF_SizeText(b->bannerFont, "Menu", &w, &h);
	b->bannerButtons[0] = sdlCreateButton(b->gWindow,
									 b->gRenderer,
									 "Menu",
									 b->bannerFont,
									 0xFF,
									 0xF8,
									 0xDC,
									 w + 5,
									 h + 5,
									 SIDES_MARGINS,
									 SIDES_MARGINS,
									 (void (*)(int *))menuButtonAction);

	b->bannerButtons[1] = sdlCreateButton(b->gWindow,
									 b->gRenderer,
									 "Save",
									 b->bannerFont,
									 0xFF,
									 0xF8,
									 0xDC, 
									 w + 5,
									 h + 5,
									 SCREEN_WIDTH - SIDES_MARGINS - w - 5,
									 SIDES_MARGINS,
									 (void (*)(int *))menuButtonAction);
	/* TODO : save function */

	b->bannerTitle = LTexture_New();
	LTexture_Init(b->bannerTitle, b->gWindow, b->gRenderer);
	LTexture_SetFont(b->bannerTitle, b->bannerFont);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	LTexture_LoadFromRenderedText(b->bannerTitle,"COLOR FLOOD", c);

	b->bannerTurnCounter = LTexture_New();
	LTexture_Init(b->bannerTurnCounter, b->gWindow, b->gRenderer);
	LTexture_SetFont(b->bannerTurnCounter, b->bannerFont);
	LTexture_LoadFromRenderedText(b->bannerTurnCounter,"Turn 0", c);

}

void boardUpdateTurn(sdlBoard *b) {
	/* should be enough space for a loooot of turns */
	char str[100];
	sprintf(str, "Turn %d", b->g->turnCount);

	LTexture_Delete(b->bannerTurnCounter);

	b->bannerTurnCounter = LTexture_New();
	LTexture_Init(b->bannerTurnCounter, b->gWindow, b->gRenderer);
	LTexture_SetFont(b->bannerTurnCounter, b->bannerFont);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	LTexture_LoadFromRenderedText(b->bannerTurnCounter, str, c);

}

void boardHandleEvents(sdlBoard *b, SDL_Event *e, int *playerColor) {
	int i;
	for(i=0; i<b->g->cNb; i++) {
		/* maybe make a function in button_wrapper to check if inside */
		if(e->type == SDL_MOUSEBUTTONUP) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			LButton *current = b->boardButtons[i];

			bool inside = true;

			if(x < current->mPosition.x) {
				inside = false;
			}
			else if(x > current->mPosition.x + LTexture_GetWidth(current->mBackground)) {
				inside = false;
			}
			else if(y < current->mPosition.y) {
				inside = false;
			}
			else if(y > current->mPosition.y + LTexture_GetHeight(current->mBackground)) {
				inside = false;
			}
			if(inside) {
				(*playerColor) = b->boardButtons[i]->mPosition.x;
			}
		}

		LButton_HandleEvent(b->boardButtons[i], e, playerColor);

		
	}
	
	LButton_HandleEvent(b->bannerButtons[0], e, (int *)&(b->gs));
	LButton_HandleEvent(b->bannerButtons[1], e, (int *)&(b->gs));
}

/* not working on a sdlBoard* to render both colors and banner buttons */
void boardRenderButtons(LButton **buttonsList, int buttonsCount) {
	int i;
	for(i=0; i<buttonsCount; i++) {
		LButton_Render(buttonsList[i]);
	}
}

void boardRenderBanner(sdlBoard *b) {
	boardUpdateTurn(b);
	LTexture_Render(b->bannerTitle,
					(SCREEN_WIDTH - LTexture_GetWidth(b->bannerTitle)) / 2,
					SIDES_MARGINS,
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);
	LTexture_Render(b->bannerTurnCounter,
					(SCREEN_WIDTH - LTexture_GetWidth(b->bannerTurnCounter)) / 2,
					SIDES_MARGINS + LTexture_GetHeight(b->bannerTitle),
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);
	boardRenderButtons(b->bannerButtons, 2);
}

void boardRenderTile(SDL_Renderer **gRenderer, int x, int y, size_t side, RGB color) {
	SDL_SetRenderDrawColor(*gRenderer, color.R, color.G, color.B, 0xFF);		
	SDL_Rect tile = {x, y, side, side};
	SDL_RenderFillRect(*gRenderer, &tile);
}

void boardRenderBoard(sdlBoard *b) {
	int availableVertical = SCREEN_HEIGHT - 3 * SIDES_MARGINS - buttonSide - LTexture_GetHeight(b->bannerTitle) - LTexture_GetHeight(b->bannerTurnCounter);
	int availableHorizontal = SCREEN_WIDTH - 2 * SIDES_MARGINS;
	int tileSide = ((availableVertical < availableHorizontal) ? availableVertical : availableHorizontal) / b->g->size;
	/* keep it centered despite rounding */
	int offset = (availableHorizontal - tileSide * b->g->size) / 2;
	int i,j,x,y;
	for(i=0; i<b->g->size; i++) {
		for(j=0; j<b->g->size; j++) {
			x = SIDES_MARGINS + i*tileSide + offset;
			y = SCREEN_HEIGHT - 2*SIDES_MARGINS - buttonSide - (b->g->size - j) * tileSide;
			boardRenderTile(b->gRenderer, x, y, tileSide, gridGetColor(b->g->grid, i, j));
		}
	}
}

void boardRenderGameOverAnimation(sdlBoard *b, int *directions, int *yBases) {
	int i, x, y;
	for(i=0; i<b->g->cNb; i++) {
		/* speeds accordings to the colors
		 * TODO : make this prettier and more readable 
		 */
		x = (b->boardButtons[i]->mPosition.x + directions[i] * (b->g->cTab[i].R + b->g->cTab[i].G) / 60);
		if( x >	(SCREEN_WIDTH - LTexture_GetWidth(b->boardButtons[i]->mBackground)) || x < 0) directions[i] *= -1;

		yBases[i] = (yBases[i] + (b->g->cTab[i].R + b->g->cTab[i].G) / 60) % 2147483647;
		y = SCREEN_HEIGHT - buttonSide - abs(sin((float)yBases[i] / SCREEN_WIDTH * 3.14159) * b->g->cTab[i].B);

		LButton_SetPosition(b->boardButtons[i], x, y);
	}

	boardRenderButtons(b->boardButtons, b->g->cNb);
}

void boardGameOverRoutine(sdlBoard *b, SDL_Event *e, GameState *gs) {
	LTexture *gameOverMessage = LTexture_New();
	LTexture_Init(gameOverMessage, b->gWindow, b->gRenderer);
	LTexture_SetFont(gameOverMessage, b->bannerFont);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	char str[100];
	sprintf(str,"Congratulation you have finished in %d turns!", b->g->turnCount);
	LTexture_LoadFromRenderedText(gameOverMessage, str, c);

	LTexture *continueMessage = LTexture_New();
	LTexture_Init(continueMessage, b->gWindow, b->gRenderer);
	LTexture_SetFont(continueMessage, b->bannerFont);
	LTexture_LoadFromRenderedText(continueMessage, "Clic to continue", c);

	int *directions = (int *)calloc(b->g->cNb, sizeof(int));
	int *yBases = (int *)calloc(b->g->cNb, sizeof(int));
	int i;
	for (i=0; i<b->g->cNb; i++) {
		directions[i] = 1;
		yBases[i] = b->boardButtons[i]->mPosition.y;
	}

	while(*gs == GAMESTATE_GAMEOVER) {
		while(SDL_PollEvent(e) != 0) {
			if(e->type == SDL_MOUSEBUTTONUP) {
				*gs = GAMESTATE_MENU;
			}
			else if(e->type == SDL_QUIT) {
				*gs = GAMESTATE_QUIT;
			}
		}
		SDL_SetRenderDrawColor(*(b->gRenderer), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(*(b->gRenderer));

		LTexture_Render(gameOverMessage, (SCREEN_WIDTH - LTexture_GetWidth(gameOverMessage)) / 2, SIDES_MARGINS, NULL, 0, NULL, SDL_FLIP_NONE);
		LTexture_Render(continueMessage, (SCREEN_WIDTH - LTexture_GetWidth(continueMessage)) / 2, SIDES_MARGINS + LTexture_GetHeight(gameOverMessage), NULL, 0, NULL, SDL_FLIP_NONE);
		boardRenderGameOverAnimation(b, directions, yBases);
		SDL_RenderPresent(*(b->gRenderer));
	}
			
	free(directions);
	free(yBases);
	LTexture_Delete(gameOverMessage);
	LTexture_Delete(continueMessage);
}

GameState boardRoutine(game *g, SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e) {
	int playerColor = -1;
	GameState gs = GAMESTATE_PLAYING;
	sdlBoard *b = boardInit(g, gWindow, gRenderer);
	
	while(gs == GAMESTATE_PLAYING) {
		SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(*gRenderer);

		while(SDL_PollEvent(e) != 0) {
			if(e->type == SDL_QUIT) {
				gs = GAMESTATE_QUIT;
			}
			else {
				boardHandleEvents(b, e, &playerColor);
			}
		}

		if(gs != GAMESTATE_QUIT) gs = b->gs;

		gamePlayTurnSDL(b->g, playerColor);

		boardRenderBanner(b);
		boardRenderButtons(b->boardButtons, g->cNb);
		boardRenderBoard(b);

		SDL_RenderPresent(*gRenderer);

		if(gameOver(b->g)) {
			gs = GAMESTATE_GAMEOVER;
			boardGameOverRoutine(b, e, &gs);
		}
	}
	boardDelete(b);

	return gs;
}

void colorButtonAction(int *playerColor) {
	/* x coodinate -> color index */
	int newColor = ((*playerColor) - SIDES_MARGINS) / (buttonSide + BUTTON_MARGIN);
	(*playerColor) = newColor;
}

void menuButtonAction(GameState *gs) {
	*gs = GAMESTATE_MENU;
}
