#include "texture_wrapper.h"
#include "sdl_utils.h"

int main(int argc, char *argv[]) {
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;

	if(!sdlInit(&gWindow, &gRenderer)) {
		fprintf(stderr,"Failed to initialize!\n");
	}
	else {
		bool quit = false;
		SDL_Event e;

		LTexture *t = LTexture_New();
		LTexture_Init(t, &gWindow, &gRenderer);
		LTexture_LoadFont(t, "/usr/share/fonts/TTF/DejaVuSansMono.ttf", 24);
		SDL_Color c = {0, 0, 0};
		LTexture_LoadFromRenderedText(t,"Coucou le texte", c);


		while(!quit) {
			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT) {
					quit = true;
				}
			}

			/* red rectangle filled middle screen */
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);
			
			SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect);

			LTexture_Render(t, (SCREEN_WIDTH - t->mWidth) / 2, (SCREEN_HEIGHT - t->mHeight) / 2, NULL, 0, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(gRenderer);
		}

		LTexture_Delete(t);

	}

	sdlClose(&gWindow, &gRenderer);

	return 0;
}
