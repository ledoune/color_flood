#include "sdl_utils.h"

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
