#include "sdl_utils.h"

bool init(SDL_Window **gWindow, SDL_Surface **gScreenSurface) {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        *gWindow = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( *gWindow == NULL ) {
            fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            *gScreenSurface = SDL_GetWindowSurface( *gWindow );
        }
    }
    return success;
}

void quit(SDL_Surface **array, SDL_Window *window) {
	int i;
	for(i=0; i<KEY_PRESS_SURFACE_TOTAL; i++) {
		SDL_FreeSurface(array[i]);
		array[i] = NULL;
	}

    SDL_DestroyWindow( window );
    window = NULL;

    SDL_Quit();

}

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
