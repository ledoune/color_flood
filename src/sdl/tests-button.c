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

		LButton *b = LButton_New();
		LButton_SetPosition(b, (SCREEN_WIDTH - t->mWidth) / 2, (SCREEN_HEIGHT - t->mHeight) / 2);
		LButton_SetLTexture(b, t);
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
