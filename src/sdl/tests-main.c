#include "sdl_utils.h"

/*
int main( int argc, char* args[] ) {
    SDL_Window* window = NULL;
    SDL_Surface* sScreen= NULL;
    SDL_Surface* saKeys [ KEY_PRESS_SURFACE_TOTAL ];
	SDL_Surface* sCurrent = NULL;

    if(!init(&window, &sScreen)) {
        fprintf(stderr, "Failed to initialize\n");
    }
    else {
        if(!loadAllMedia(saKeys)) {
            fprintf(stderr, "Failed to load media\n");
        }
      	else {
			int arrows_ret = 0;
			SDL_Event e;
			sCurrent = saKeys[ KEY_PRESS_SURFACE_DEFAULT ];
			while(arrows_ret >= 0) {
				while(SDL_PollEvent(&e) != 0) {
					arrows_ret = handleArrowsEvents(&e);	
					sCurrent = saKeys[arrows_ret];
					SDL_BlitSurface( sCurrent, NULL, sScreen, NULL );
					SDL_UpdateWindowSurface(window);
				}
			}
        }
	}

    quit(saKeys, window);
    return 0;
}
*/

int main(int argc, char *args[]) {
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;
	
	if(!sdlInit(&gWindow, &gRenderer)) {
		printf("Failed ot initialize!\n");
	}
	else {
		bool quit = false;
		SDL_Event e;

		while(!quit) {
			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT) {
					quit = true;
				}
			}

			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			
			SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect);

			SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect(gRenderer, &outlineRect);

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
			int i;
			for(i = 0; i < SCREEN_HEIGHT; i+=4) {
				SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
			}

			SDL_RenderPresent(gRenderer);
		}
	}

	sdlClose(&gWindow, &gRenderer);

	return 0;
}
