#include "game_load_rendering.h"

sdlPreview* previewInit(SDL_Window **gWindow, SDL_Renderer **gRenderer,game *g) {
	sdlPreview *newPreview = (sdlPreview *)calloc(1, sizeof(sdlPreview));
	newPreview->gWindow = gWindow;
	newPreview->gRenderer = gRenderer;
	newPreview->font = TTF_OpenFont("./src/sdl/fonts/CaviarDreams.ttf", 20);
	newPreview->g = g;
	newPreview->gs = GAMESTATE_LOAD;
	newPreview->savesCount = savesInit(&(newPreview->savesNames));
	newPreview->currentSave = (newPreview->savesCount > 0) ? 0 : -1;

	previewInitBanner(newPreview);
	previewInitFooter(newPreview);

	previewUpdateSaveName(newPreview);

	return newPreview;
}

void previewDelete(sdlPreview *p) {
	TTF_CloseFont(p->font);

	LTexture_Delete(p->bannerTitle);
	LTexture_Delete(p->bannerSaveName);
	
	LButton_Delete(p->bannerButtons[0]);
	LButton_Delete(p->bannerButtons[1]);

	savesFree(&(p->savesNames), p->savesCount);

	free(p);
}

void previewInitBanner(sdlPreview *p) {
	int w, h;

	TTF_SizeText(p->font, "Load", &w, &h);
	p->bannerButtons[0] = sdlCreateButton(p->gWindow,
									 p->gRenderer,
									 "Menu",
									 p->font,
									 0xFF,
									 0xF8,
									 0xDC,
									 w + 5,
									 h + 5,
									 SIDES_MARGINS,
									 SIDES_MARGINS,
									 (void (*)(int *))menuButtonAction);

	p->bannerButtons[1] = sdlCreateButton(p->gWindow,
									 p->gRenderer,
									 "Play",
									 p->font,
									 0xFF,
									 0xF8,
									 0xDC, 
									 w + 5,
									 h + 5,
									 SCREEN_WIDTH - SIDES_MARGINS - w - 5,
									 SIDES_MARGINS,
									 (void (*)(int *))playButtonAction);

	p->bannerTitle = LTexture_New();
	LTexture_Init(p->bannerTitle, p->gWindow, p->gRenderer);
	LTexture_SetFont(p->bannerTitle, p->font);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	LTexture_LoadFromRenderedText(p->bannerTitle,"LOAD", c);

	p->bannerSaveName = LTexture_New();
	LTexture_Init(p->bannerSaveName, p->gWindow, p->gRenderer);
	LTexture_SetFont(p->bannerSaveName, p->font);
	LTexture_LoadFromRenderedText(p->bannerSaveName, "Save Name", c);

}

void previewInitFooter(sdlPreview *p) {
	int w, h;

	TTF_SizeText(p->font, "Prev", &w, &h);

	p->footerButtons[0] = sdlCreateButton(p->gWindow,
									 p->gRenderer,
									 "Prev",
									 p->font,
									 0xFF,
									 0xF8,
									 0xDC, 
									 w + 5,
									 h + 5,
									 SIDES_MARGINS,
									 SCREEN_HEIGHT - SIDES_MARGINS - h - 5,
									 previousButtonAction);

	p->footerButtons[1] = sdlCreateButton(p->gWindow,
									 p->gRenderer,
									 "Supp",
									 p->font,
									 0xFF,
									 0xF8,
									 0xDC, 
									 w + 5,
									 h + 5,
									 (SCREEN_WIDTH - w - 5) / 2,
									 SCREEN_HEIGHT - SIDES_MARGINS - h - 5,
									 (void (*)(int *))deleteButtonAction);

	p->footerButtons[2] = sdlCreateButton(p->gWindow,
									 p->gRenderer,
									 "Next",
									 p->font,
									 0xFF,
									 0xF8,
									 0xDC, 
									 w + 5,
									 h + 5,
									 SCREEN_WIDTH - SIDES_MARGINS - w - 5,
									 SCREEN_HEIGHT - SIDES_MARGINS - h - 5,
									 nextButtonAction);


}

int savesInit(char ***savesNames) {

	int currArraySize = 1;
	/* array init */
	*savesNames = (char **)calloc(currArraySize, sizeof(char *));

	DIR *dir;
	struct dirent *ent;
	int savesCount = 0;
	if ((dir = opendir(SAVES_FOLDER)) != NULL) {
  		while ((ent = readdir(dir)) != NULL) {
			/* if regular file */
			if(ent->d_type == DT_REG) {
				/* resize array if no more room */
				if(savesCount >= currArraySize) {
					currArraySize *= 2;
					*savesNames = (char **)realloc(*savesNames, currArraySize * sizeof(char *));
				}
				/* alloc string for current save */
				(*savesNames)[savesCount] = (char *)calloc(30, sizeof(char));
    			sprintf((*savesNames)[savesCount], ent->d_name);
				savesCount++;
			}
  		}
  		closedir(dir);
	} 
	else {
		fprintf(stderr, "Loading saves: Could not open folder %s!\n",SAVES_FOLDER);
		savesCount = -1;
	}
	
	return savesCount;
}

void savesFree(char ***savesNames, int savesCount) {
	int i;
	for(i=0; i<savesCount; i++) {
		free((*savesNames)[i]);
	}
	free(*savesNames);
}


void previewHandleEvents(sdlPreview *p, SDL_Event *e) {
	/* banner buttons */
	LButton_HandleEvent(p->bannerButtons[0], e, (int *)&(p->gs));
	LButton_HandleEvent(p->bannerButtons[1], e, (int *)&(p->gs));
	/* footer buttons */
	LButton_HandleEvent(p->footerButtons[0], e, &(p->currentSave));
	LButton_HandleEvent(p->footerButtons[1], e, (int *)&(p->gs));
	LButton_HandleEvent(p->footerButtons[2], e, &(p->currentSave));
}

void computeCurrentSaveNumber(sdlPreview *p) {
	if(p->currentSave < 0) {
		p->currentSave = p->savesCount - 1;
	}
	else if(p->currentSave >= p->savesCount) {
		p->currentSave = 0;
	}
	else if(p->savesCount == -1) {
		p->currentSave = -1;
	}
}

void previewRenderBanner(sdlPreview *p) {
	previewUpdateSaveName(p);
	LTexture_Render(p->bannerTitle,
					(SCREEN_WIDTH - LTexture_GetWidth(p->bannerTitle)) / 2,
					SIDES_MARGINS,
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);
	LTexture_Render(p->bannerSaveName,
					(SCREEN_WIDTH - LTexture_GetWidth(p->bannerSaveName)) / 2,
					SIDES_MARGINS + LTexture_GetHeight(p->bannerTitle),
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);
	boardRenderButtons(p->bannerButtons, 2);
}

void previewRenderFooter(sdlPreview *p) {
	boardRenderButtons(p->footerButtons, 3);
}


void previewRenderBoard(sdlPreview *p) {
	int w, h;
	TTF_SizeText(p->font, "Prev", &w, &h);

	int availableVertical = SCREEN_HEIGHT - 4 * SIDES_MARGINS - h - 5 - LTexture_GetHeight(p->bannerTitle) - LTexture_GetHeight(p->bannerSaveName);
	int availableHorizontal = SCREEN_WIDTH - 2 * SIDES_MARGINS;
	int tileSide = ((availableVertical < availableHorizontal) ? availableVertical : availableHorizontal) / p->g->size;
	/* keep it centered despite rounding */
	int offset = (availableHorizontal - tileSide * p->g->size) / 2;
	int i,j,x,y;
	for(i=0; i<p->g->size; i++) {
		for(j=0; j<p->g->size; j++) {
			x = SIDES_MARGINS + i*tileSide + offset;
			y = SCREEN_HEIGHT - 2*SIDES_MARGINS - h - 5 - (p->g->size - j) * tileSide;
			boardRenderTile(p->gRenderer, x, y, tileSide, gridGetColor(p->g->grid, i, j));
		}
	}
}

void previewUpdateSaveName(sdlPreview *p) {
	if(p->currentSave >= 0) {
		LTexture_Delete(p->bannerSaveName);

		p->bannerSaveName = LTexture_New();
		LTexture_Init(p->bannerSaveName, p->gWindow, p->gRenderer);
		LTexture_SetFont(p->bannerSaveName, p->font);
		SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
		LTexture_LoadFromRenderedText(p->bannerSaveName, p->savesNames[p->currentSave], c);
	}
}

GameState previewRoutine(game **g, SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e) {
	GameState gs = GAMESTATE_LOAD;
	/* TODO : make the order of the parameters consistent */ 
	sdlPreview *p = previewInit(gWindow, gRenderer, *g);
	
	while(gs == GAMESTATE_LOAD) {
		SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(*gRenderer);

		while(SDL_PollEvent(e) != 0) {
			if(e->type == SDL_QUIT) {
				gs = GAMESTATE_QUIT;
			}
			else {
				previewHandleEvents(p, e);
			}
		}

		if(p->gs == GAMESTATE_DELETE) p->gs = GAMESTATE_LOAD;
		if(gs != GAMESTATE_QUIT) gs = p->gs;

		computeCurrentSaveNumber(p);

		previewRenderBanner(p);
		previewRenderFooter(p);
		if(p->savesCount > 0) {
			p->g = gameImport(p->savesNames[p->currentSave]);
			*g = p->g;
			previewRenderBoard(p);
		}

		SDL_RenderPresent(*gRenderer);
	}
	previewDelete(p);
	
	if(gs == GAMESTATE_MENU) {
		gameFree(*g);
		*g = NULL;
	}

	return gs;
}


/* same as in game_board_rendering, so we use it.
 * maybe the function should be moved to game_states.h
void menuButtonAction(GameState *gs) {
	*gs = GAMESTATE_MENU;
}
*/

void playButtonAction(GameState *gs) {
	*gs = GAMESTATE_PLAYING;
}

void nextButtonAction(int *currentSave) {
	*currentSave += 1;
}

void previousButtonAction(int *currentSave) {
	*currentSave -= 1;
}

void deleteButtonAction(GameState *gs) {
	*gs= GAMESTATE_DELETE;
}
