#include "button_wrapper.h"

LButton* LButton_New(void) {
	LButton *b = (LButton *)calloc(1, sizeof(LButton));
	
	b->mPosition.x = 0;
	b->mPosition.y = 0;
	b->mBackground = NULL;
	b->s = LBUTTON_NEUTRAL;
}

void LButton_Delete(LButton *b) {
	LTexture_Delete(b->mBackground);
	free(b);
}

void LButton_SetPosition(LButton*b, int x, int y) {
	b->mPosition.x = x;
	b->mPosition.y = y;
}

void LButton_SetBackground(LButton *b, LTexture *t) {
	b->mBackground = t;
}

void LButton_SetText(LButton *b, LTexture *t) {
	b->mText = t;
}

void LButton_SetAction(LButton *b, void (*ptr)(int *)) {
	b->triggerPtr = ptr;
}

void LButton_Render(LButton *b) {
	SDL_Rect frame = {b->mPosition.x - 1, b->mPosition.y - 1, LTexture_GetWidth(b->mBackground) + 2, LTexture_GetHeight(b->mBackground) + 2};

	switch(b->s) {
		case LBUTTON_HOVERED:
			SDL_SetRenderDrawColor(LTexture_GetRenderer(b->mBackground), 0xFF, 0x00, 0x00, 0xFF);
			break;

		case LBUTTON_PRESSED:
			SDL_SetRenderDrawColor(LTexture_GetRenderer(b->mBackground), 0x00, 0xFF, 0x00, 0xFF);
			break;

		case LBUTTON_NEUTRAL:
			SDL_SetRenderDrawColor(LTexture_GetRenderer(b->mBackground), 0x69, 0x69, 0x69, 0xFF);
			break;
	}

	SDL_RenderDrawRect(LTexture_GetRenderer(b->mBackground), &frame);
	LTexture_Render(b->mBackground, b->mPosition.x, b->mPosition.y, NULL, 0, NULL, SDL_FLIP_NONE);
	int textX = b->mPosition.x + (LTexture_GetWidth(b->mBackground) - LTexture_GetWidth(b->mText)) / 2;
	int textY = b->mPosition.y + (LTexture_GetHeight(b->mBackground) - LTexture_GetHeight(b->mText)) / 2;
	LTexture_Render(b->mText, textX, textY, NULL, 0, NULL, SDL_FLIP_NONE);
}

void LButton_HandleEvent(LButton *b, SDL_Event *e, int *gs) {
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if(x < b->mPosition.x) {
			inside = false;
		}
		else if(x > b->mPosition.x + LTexture_GetWidth(b->mBackground)) {
			inside = false;
		}
		else if(y < b->mPosition.y) {
			inside = false;
		}
		else if(y > b->mPosition.y + LTexture_GetHeight(b->mBackground)) {
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
					(*(b->triggerPtr))(gs);
					break;
			}
		}
	}
}

