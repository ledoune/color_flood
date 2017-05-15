#ifndef _GAME_LOAD_RENDERING_H
#define _GAME_LOAD_RENDERING_H

#define _DEFAULT_SOURCE
#include<dirent.h>

#include "../game/game.h"
#include "sdl_utils.h"
#include "game_states.h"
#include "game_board_rendering.h"

typedef struct sdlPreview {
	SDL_Window **gWindow;
	SDL_Renderer **gRenderer;
	TTF_Font *font;
	game *g;
	GameState gs;
	LTexture *bannerTitle;
	LTexture *bannerSaveName;
	LButton *bannerButtons[2];
	LButton *footerButtons[3];
	int savesCount;
	char **savesNames;
	int currentSave;
} sdlPreview;

/* TODO : wrapper for a banner as it is used multiple times */

/* contructor destructor */
sdlPreview *previewInit(SDL_Window **gWindow, SDL_Renderer **gRenderer, game *g);
void previewDelete(sdlPreview *b);

/* initiators */
void previewInitBanner(sdlPreview *p);
void previewInitFooter(sdlPreview *p);
/* get the names of the saves in SAVES_FOLDER @src/game/game.h */
int savesInit(char ***savesNames);
void savesFree(char ***savesNames, int savesCount);

/* event handler */
void previewHandleEvents(sdlPreview *p, SDL_Event *e);
/* keep p->currentSave bounded */
void computeCurrentSaveNumber(sdlPreview *p);

/* renderers */
void previewRenderBanner(sdlPreview *p);
void previewRenderFooter(sdlPreview *p);
void previewRenderBoard(sdlPreview *p);
void previewUpdateSaveName(sdlPreview *p);

/* routine for controller */
GameState previewRoutine(game **g, SDL_Window **gWindow, SDL_Renderer **gRenderer, SDL_Event *e);

/* banner buttons actions */
void menuButtonAction(GameState *gs);
void playButtonAction(GameState *gs);
/* nav buttons actions */
void nextButtonAction(int *currentSave);
void previousButtonAction(int *currentSave);
void deleteButtonAction(GameState *gs);

#endif
