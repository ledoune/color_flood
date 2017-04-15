#include "button_wrapper.h"

LButton* LButton_New(void) {
	LButton *b = (LButton *)calloc(1, sizeof(LButton));
	
	b->mPosition.x = 0;
	b->mPosition.y = 0;
	b->mTexture = NULL;
	b->s = LBUTTON_NEUTRAL;
}

void LButton_Delete(LButton *b) {
	LTexture_Delete(b->mTexture);
	free(b);
}

void LButton_SetPosition(LButton*b, int x, int y) {
	b->mPosition.x = x;
	b->mPosition.y = y;
}

void LButton_SetLTexture(LButton *b, LTexture *t) {
	b->mTexture = t;
}

void LButton_SetAction(LButton *b, void (*ptr)(void)) {
	b->triggerPtr = ptr;
}

void LButton_Render(LButton *b) {
	SDL_Rect frame = {b->mPosition.x - 1, b->mPosition.y - 1, LTexture_GetWidth(b->mTexture), LTexture_GetHeight(b->mTexture)};

	switch(b->s) {
		case LBUTTON_HOVERED:
			SDL_SetRenderDrawColor(LTexture_GetRenderer(b->mTexture), 0xFF, 0x00, 0x00, 0xFF);
			break;

		case LBUTTON_PRESSED:
			SDL_SetRenderDrawColor(LTexture_GetRenderer(b->mTexture), 0x00, 0xFF, 0x00, 0xFF);
			break;

		case LBUTTON_NEUTRAL:
			SDL_SetRenderDrawColor(LTexture_GetRenderer(b->mTexture), 0x69, 0x69, 0x69, 0xFF);
			break;
	}

	SDL_RenderDrawRect(LTexture_GetRenderer(b->mTexture), &frame);
	LTexture_Render(b->mTexture, b->mPosition.x, b->mPosition.y, NULL, 0, NULL, SDL_FLIP_NONE);
}

void LButton_HandleEvent(LButton *b, SDL_Event* e) {
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if(x < b->mPosition.x) {
			inside = false;
		}
		else if(x > b->mPosition.x + LTexture_GetWidth(b->mTexture)) {
			inside = false;
		}
		else if(y < b->mPosition.y) {
			inside = false;
		}
		else if(y > b->mPosition.y + LTexture_GetHeight(b->mTexture)) {
			inside = false;
		}

		if(!inside) {
			b->s = LBUTTON_NEUTRAL;
		}
		else {
			switch(e->type) {
				case SDL_MOUSEMOTION:
					b->s = LBUTTON_HOVERED;
					break;
			
				case SDL_MOUSEBUTTONDOWN:
					b->s = LBUTTON_PRESSED;
					break;

				case SDL_MOUSEBUTTONUP:
					/* TODO TRIGGER BUTTON ACTION */
					(*(b->triggerPtr))();
					break;
			}
		}
	}
}

