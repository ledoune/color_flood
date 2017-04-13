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
