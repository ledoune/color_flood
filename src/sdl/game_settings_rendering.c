#include "game_settings_rendering.h"

settingsScreen* settingsInit(int *boardSize, int *colorAmount, SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	TTF_Font *settingsFont = TTF_OpenFont("./src/sdl/fonts/CaviarDreams.ttf", 20);

	settingsScreen *s = (settingsScreen *)calloc(1, sizeof(settingsScreen));

	/* text textures init */
	s->banner = LTexture_New();
	LTexture_Init(s->banner, gWindow, gRenderer);
	LTexture_SetFont(s->banner, settingsFont);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	LTexture_LoadFromRenderedText(s->banner, "SETTINGS", c);

	s->mSizeQuery = LTexture_New();
	LTexture_Init(s->mSizeQuery, gWindow, gRenderer);
	LTexture_SetFont(s->mSizeQuery, settingsFont);
	LTexture_LoadFromRenderedText(s->mSizeQuery, "Board side: ", c);

	s->mColorQuery = LTexture_New();
	LTexture_Init(s->mColorQuery, gWindow, gRenderer);
	LTexture_SetFont(s->mColorQuery, settingsFont);
	LTexture_LoadFromRenderedText(s->mColorQuery, "Number of colors: ", c);

	/* textboxes init */
	char *sizeStr = (char *)calloc(4, sizeof(char));
	sprintf(sizeStr, "%3d", *boardSize);
	s->mSizeInput = LTextbox_New(gWindow, gRenderer, settingsFont);
	LTextbox_SetStr(s->mSizeInput, sizeStr, 4);
	LTextbox_SetPosition(s->mSizeInput, 
						 SIDE_MARGIN + LTexture_GetWidth(s->mSizeQuery), 
						 SIDE_MARGIN + LTexture_GetHeight(s->banner) + TEXT_MARGIN);

	char *colorStr = (char *)calloc(4, sizeof(char));
	sprintf(colorStr, "%3d", *colorAmount);
	s->mColorInput = LTextbox_New(gWindow, gRenderer, settingsFont);
	LTextbox_SetStr(s->mColorInput, colorStr, 4);
	LTextbox_SetPosition(s->mColorInput, 
						 SIDE_MARGIN + LTexture_GetWidth(s->mColorQuery),
						 s->mSizeInput->mPosition.y + LTexture_GetHeight(s->mSizeQuery) + TEXT_MARGIN);

	int w,h;
	TTF_SizeText(settingsFont, "Menu", &w, &h);
	s->menuButton = sdlCreateButton(gWindow,
									gRenderer,
									"Menu",
									settingsFont,
									0xFF,
									0xF8,
									0xDC,
									w + 5,
									h + 5,
									SIDE_MARGIN,
									SIDE_MARGIN,
									(void (*)(int *))settingsMenuAction);

	s->boardSize = boardSize;
	s->colorAmount = colorAmount;
	s->gs = GAMESTATE_SETTINGS;

	return s;
}

void settingsDelete(settingsScreen *s) {
	TTF_CloseFont(s->banner->font);

	LTexture_Delete(s->banner);
	LTexture_Delete(s->mSizeQuery);
	LTexture_Delete(s->mColorQuery);

	LButton_Delete(s->menuButton);

	LTextbox_Delete(s->mSizeInput);
	LTextbox_Delete(s->mColorInput);

	free(s);
}

void settingsHandleEvent(settingsScreen *s, SDL_Event *e) {
	
	LTextbox_HandleEvent(s->mSizeInput, e);
	LTextbox_HandleEvent(s->mColorInput, e);

	LButton_HandleEvent(s->menuButton, e, (int *)&(s->gs));
}

void settingsProcessInput(settingsScreen *s) {
	if(s->mSizeInput->ts == TEXTBOX_NEUTRAL) {
		int tmpSize = atoi(s->mSizeInput->mText);
		if(tmpSize < 3) {
			tmpSize = 3;
		}
		else if(tmpSize > 100) {
			tmpSize = 100;
		}
		char *newSize = (char *)calloc(4, sizeof(char));
		sprintf(newSize, "%3d", tmpSize);
		LTextbox_SetStr(s->mSizeInput, newSize, 4);
		*(s->boardSize) = tmpSize;
	}
	
	textBoxUpdate(s->mSizeInput);

	if(s->mColorInput->ts == TEXTBOX_NEUTRAL) {
		int tmpColor = atoi(s->mColorInput->mText);
		if(tmpColor < 3) {
			tmpColor = 3;
		}
		else if(tmpColor > 20) {
			tmpColor = 20;
		}
		char *newColor = (char *)calloc(4, sizeof(char));
		sprintf(newColor, "%3d", tmpColor);
		LTextbox_SetStr(s->mColorInput, newColor, 4);
		*(s->colorAmount) = tmpColor;
	}
	
	textBoxUpdate(s->mColorInput);
}

void settingsRender(settingsScreen *s) {
	LTexture_Render(s->banner, 
					(SCREEN_WIDTH - LTexture_GetWidth(s->banner)) / 2,
				   	SIDE_MARGIN,
				   	NULL,
				   	0,
				   	NULL,
				   	SDL_FLIP_NONE);

	LTexture_Render(s->mSizeQuery,
					SIDE_MARGIN,
					s->mSizeInput->mPosition.y,
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);

	LTexture_Render(s->mColorQuery,
					SIDE_MARGIN,
					s->mColorInput->mPosition.y,
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);

	LTextbox_Render(s->mSizeInput);
	LTextbox_Render(s->mColorInput);

	LButton_Render(s->menuButton);
}

GameState settingsRoutine(SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e, int *boardSize, int *colorAmount) {
	settingsScreen *s = settingsInit(boardSize, colorAmount, gWindow, gRenderer);

	SDL_StartTextInput();

	while(s->gs == GAMESTATE_SETTINGS) {
		SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(*gRenderer);

		while(SDL_PollEvent(e) != 0) {
			if(e->type == SDL_QUIT) {
				s->gs = GAMESTATE_QUIT;
			}
			else {
				settingsHandleEvent(s, e);
			}
		}

		settingsProcessInput(s);
		settingsRender(s);

		SDL_RenderPresent(*gRenderer);
	}

	GameState gs = s->gs;
	SDL_StopTextInput();
	settingsDelete(s);

	return gs;
}

void settingsMenuAction(GameState *gs) {
	*gs = GAMESTATE_MENU;
}
