#include "button_wrapper.h"

void test_trigger(void) {
	printf("button!\n");
}

int main(int argc, char *argv[]) {
	SDL_Window *gWindow = NULL;
	SDL_Renderer *gRenderer = NULL;

	if(!sdlInit(&gWindow, &gRenderer)) {
		fprintf(stderr, "Failed to initialize!\n");
	}
	else {
		bool quit = false;
		SDL_Event e;

		LTexture *t = LTexture_New();
		LTexture_Init(t, &gWindow, &gRenderer);
		LTexture_LoadFont(t, "/usr/share/fonts/TTF/ttf-inconsolata-g.ttf", 24);
		SDL_Color c = {0, 0, 0};
		LTexture_LoadFromRenderedText(t, "Coucou le texte", c);

		LTexture *bk = LTexture_New();
		LTexture_Init(bk, &gWindow, &gRenderer);
		bool targetOK = true;
		if(!LTexture_SetGeometryMode(bk, LTexture_GetWidth(t) + 20, LTexture_GetHeight(t)) + 20) {
			fprintf(stderr,"Failed to create target texture!\n");
			targetOK = false;
		}
		LTexture_SetAsRenderTarget(bk);

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		SDL_Rect background = {0, 0, LTexture_GetWidth(t) + 20, LTexture_GetHeight(t) + 20};
		/*
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xF8, 0xDC, 0xFF);
		*/
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &background);

		SDL_SetRenderTarget(gRenderer, NULL);


		LButton *b = LButton_New();
		LButton_SetPosition(b, (SCREEN_WIDTH - bk->mWidth) / 2, (SCREEN_HEIGHT - bk->mHeight) / 2);
		LButton_SetText(b, t);
		LButton_SetBackground(b, bk);
		LButton_SetAction(b, &test_trigger);

		while(!quit) {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT) {
					quit = true;
				}
				else {
					LButton_HandleEvent(b, &e);
				}
			}

			LButton_Render(b);

			SDL_RenderPresent(gRenderer);
		}

		LButton_Delete(b);
	}

	sdlClose(&gWindow, &gRenderer);

	return 0;
}
