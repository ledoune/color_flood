#include "sdl_utils.h"

bool sdlInit(SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr,"SDL could not initiate! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		/* texture filtering linear, cf doc */
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			fprintf(stderr,"Warning : Linear texture filtering not enabled!");
		}

		/* create window */
		*gWindow = SDL_CreateWindow("Coucou la fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(*gWindow == NULL) {
			fprintf(stderr,"Window could not be created! SDL Error : %s\n", SDL_GetError());
			success = false;
		}
		else {
			/* create renderer */
			*gRenderer = SDL_CreateRenderer(*gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(*gRenderer == NULL) {
				fprintf(stderr,"Renderer could not be created! SDL Error : %s\n", SDL_GetError());
				success = false;
			}
			else {
				/* initialize renderer color */
				SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				/* initialize image loading with png type */
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					fprintf(stderr,"SDL_image could not initialize! SDL_image Error : %s\n", IMG_GetError());
					success = false;
				}

				/* initialize SDL ttf */
				if(TTF_Init() == -1) {
					fprintf(stderr,"SDL_ttf could not initialize! SDL_ttf Error %s\n", TTF_GetError());
				}
			}
		}
	}
	return success;
}


void sdlClose(SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	SDL_DestroyRenderer(*gRenderer);
	SDL_DestroyWindow(*gWindow);
	*gWindow = NULL;
	*gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

LButton* sdlCreateButton(SDL_Window **gWindow, SDL_Renderer **gRenderer, const char *text, TTF_Font *font, uint8_t R, uint8_t G, uint8_t B, size_t width, size_t height, int posX, int posY, void (*ptr)(int *)) {
	
	LTexture *t = NULL;
	if(text != NULL) {
		t = LTexture_New();
		LTexture_Init(t, gWindow, gRenderer);
		LTexture_SetFont(t, font);
		SDL_Color c = {0, 0, 0};
		LTexture_LoadFromRenderedText(t, text, c);
	}

	LTexture *bk = LTexture_New();
	LTexture_Init(bk, gWindow, gRenderer);
	bool targetOK = true;
	if(!LTexture_SetGeometryMode(bk, width, height)) {
		fprintf(stderr,"Failed to create target texture for button %s!\n", text);
		targetOK = false;
	}
	LTexture_SetAsRenderTarget(bk);

	SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(*gRenderer);

	SDL_Rect background = {0, 0, width, height};
	SDL_SetRenderDrawColor(*gRenderer, R, G, B, 0xFF);
	SDL_RenderFillRect(*gRenderer, &background);

	SDL_SetRenderTarget(*gRenderer, NULL);


	LButton *b = LButton_New();
	LButton_SetPosition(b, posX, posY);
	LButton_SetText(b, t);
	LButton_SetBackground(b, bk);
	LButton_SetAction(b, ptr);

	return b;
}
