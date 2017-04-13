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

		LTexture *geom = LTexture_New();
		LTexture_Init(geom, &gWindow, &gRenderer);
		bool targetOK = true;
		if(!LTexture_SetGeometryMode(geom, SCREEN_WIDTH, SCREEN_HEIGHT)) {
			fprintf(stderr,"Failed to create target texture!\n");
			targetOK = false;
		}
		/* set geom as render target */
		LTexture_SetAsRenderTarget(geom);
		
		/* clear screen */
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		/* red rectangle filled middle screen in geom. side effect of LTexture_SetGeometryMode wich set gRenderer target to geom */
		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect);

		/* reset geom renderer */
		SDL_SetRenderTarget(LTexture_GetRenderer(geom), NULL);

		/* rotation variables */
		double angle = 0.0;
		SDL_Point screenCenter = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

		while(!quit && targetOK) {
			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT) {
					quit = true;
				}
			}

			angle += 2;
			if(angle > 360) angle-=360;
			
			/* clear screen */
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			LTexture_Render(geom, 0, 0, NULL, angle, &screenCenter, SDL_FLIP_NONE);

			LTexture_Render(t, (SCREEN_WIDTH - t->mWidth) / 2, (SCREEN_HEIGHT - t->mHeight) / 2, NULL, 0, NULL, SDL_FLIP_NONE);

			SDL_RenderPresent(gRenderer);
		}

		LTexture_Delete(t);
		LTexture_Delete(geom);

	}

	sdlClose(&gWindow, &gRenderer);

	return 0;
}
