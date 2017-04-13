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
			*gRenderer = SDL_CreateRenderer(*gWindow, -1, SDL_RENDERER_ACCELERATED);
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

/********************************************************************/


bool loadAllMedia(SDL_Surface **array) {
	bool success = true;
	char img_name[100];

	sprintf(img_name,"%s/%s",IMG_PATH,"press.bmp");
	array[KEY_PRESS_SURFACE_DEFAULT] = loadBMP(img_name);
	if( array[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf( "Failed to load default image!\n" );
		success = false;
	}

	sprintf(img_name,"%s/%s",IMG_PATH,"up.bmp");
	array[KEY_PRESS_SURFACE_UP] = loadBMP(img_name);
	if( array[KEY_PRESS_SURFACE_UP] == NULL) {
		printf( "Failed to load up image!\n" );
		success = false;
	}

	sprintf(img_name,"%s/%s",IMG_PATH,"down.bmp");
	array[KEY_PRESS_SURFACE_DOWN] = loadBMP(img_name);
	if( array[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf( "Failed to load down image!\n" );
		success = false;
	}
	
	sprintf(img_name,"%s/%s",IMG_PATH,"left.bmp");
	array[KEY_PRESS_SURFACE_LEFT] = loadBMP(img_name);
	if( array[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf( "Failed to load left image!\n" );
		success = false;
	}
	
	sprintf(img_name,"%s/%s",IMG_PATH,"right.bmp");
	array[KEY_PRESS_SURFACE_RIGHT] = loadBMP(img_name);
	if( array[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf( "Failed to load right image!\n" );
		success = false;
	}
	return success;
}

SDL_Surface* loadBMP(char *name) {
    SDL_Surface *sBmp = SDL_LoadBMP( name );
    if( sBmp == NULL ) {
        fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", name, SDL_GetError() );
    }
    return sBmp;
}

int handleArrowsEvents(SDL_Event *e) {
	int key;
	if(e->type == SDL_QUIT) key = -1;
	else if ( e->type == SDL_KEYDOWN ) {
		switch ( e->key.keysym.sym ) {
			case SDLK_UP:
				key = KEY_PRESS_SURFACE_UP;
				break;
			case SDLK_DOWN:
				key = KEY_PRESS_SURFACE_DOWN;
				break;
			case SDLK_LEFT:
				key = KEY_PRESS_SURFACE_LEFT;
				break;
			case SDLK_RIGHT:
				key = KEY_PRESS_SURFACE_RIGHT;
				break;
			default:
				key = KEY_PRESS_SURFACE_DEFAULT;
		}
	}
	return key;
}
