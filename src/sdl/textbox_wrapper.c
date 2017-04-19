#include "textbox_wrapper.h"

LTextbox* LTextbox_New(SDL_Window **gWindow, SDL_Renderer **gRenderer, TTF_Font *font) {
	LTextbox *tb = (LTextbox *)calloc(1, sizeof(LTextbox));

	char *defaultStr = (char *)calloc(strlen("This is a text box") + 1, sizeof(char));
	sprintf(defaultStr, "This is a text box");
	tb->mText = defaultStr;
	tb->mTextLength = strlen("This is a text box");

	tb->mRenderedText = LTexture_New();
	LTexture_Init(tb->mRenderedText, gWindow, gRenderer);
	LTexture_SetFont(tb->mRenderedText, font);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	LTexture_LoadFromRenderedText(tb->mRenderedText, tb->mText, c);

	tb->mPosition.x = 1;
	tb->mPosition.y = 1;

	tb->ts = TEXTBOX_NEUTRAL;

	return tb;
}

void LTextbox_Delete(LTextbox *tb) {
	LTexture_Delete(tb->mRenderedText);
	free(tb->mText);
	free(tb);
}

void LTextbox_SetStr(LTextbox *tb, char *str, int length) {
	free(tb->mText);
	tb->mText = str;
	tb->mTextLength = length;
	textBoxUpdate(tb);
}

void LTextbox_SetPosition(LTextbox *tb, int x, int y) {
	tb->mPosition.x = x;
	tb->mPosition.y = y;
}

void LTextbox_HandleEvent(LTextbox *tb, SDL_Event *e) {
	if(e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if(x < tb->mPosition.x) {
			inside = false;
		}
		else if(x > tb->mPosition.x + LTexture_GetWidth(tb->mRenderedText)) {
			inside = false;	
		}
		else if(y < tb->mPosition.y) {
			inside = false;
		}
		else if(y > tb->mPosition.y + LTexture_GetHeight(tb->mRenderedText)) {
			inside = false;
		}

		if(!inside) {
			tb->ts = TEXTBOX_NEUTRAL;
		}
		else {
			tb->ts = TEXTBOX_SELECTED;
		}
	}
	/* backspace, return, and copy pasta */
	else if((tb->ts == TEXTBOX_SELECTED) && (e->type == SDL_KEYDOWN)) {
		if(e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_RETURN2) {
			tb->ts = TEXTBOX_NEUTRAL;
		}
		else if(e->key.keysym.sym == SDLK_BACKSPACE && tb->mTextLength > 0) {
			tb->mTextLength -= 1;
			tb->mText[tb->mTextLength] = '\0';
			if(tb->mTextLength == 0) {
				tb->mText[0] = ' ';
				tb->mTextLength = strlen(tb->mText);
			}
			
		}
		else if(e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
			SDL_SetClipboardText(tb->mText);
		}
		else if(e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
			tb->mText = SDL_GetClipboardText();
			tb->mTextLength = strlen(tb->mText);
		}
	}
	/* text input */
	else if((tb->ts == TEXTBOX_SELECTED) && (e->type == SDL_TEXTINPUT)) {
		if(!((e->text.text[0] == 'c' || e->text.text[0] == 'C') && (e->text.text[0] == 'v' || e->text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
			tb->mTextLength += strlen(e->text.text);
			char *newStr = (char *)calloc(tb->mTextLength + 1, sizeof(char));
			sprintf(newStr,"%s%s", tb->mText, e->text.text);
			free(tb->mText);
			tb->mText = newStr;
		}
	}

	textBoxUpdate(tb);
}

void LTextbox_Render(LTextbox *tb) {
	/* text */
	LTexture_Render(tb->mRenderedText,
					tb->mPosition.x,
					tb->mPosition.y,
					NULL,
					0,
					NULL,
					SDL_FLIP_NONE);

	if(tb->ts == TEXTBOX_NEUTRAL) {
		SDL_SetRenderDrawColor(*(tb->mRenderedText->gRenderer), 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(*(tb->mRenderedText->gRenderer), tb->mPosition.x, tb->mPosition.y + LTexture_GetHeight(tb->mRenderedText) + 1, tb->mPosition.x + LTexture_GetWidth(tb->mRenderedText), tb->mPosition.y + LTexture_GetHeight(tb->mRenderedText) + 1);
	}
	else {
		SDL_SetRenderDrawColor(*(tb->mRenderedText->gRenderer), 0x00, 0x00, 0xFF, 0xFF);
		SDL_Rect frame = {tb->mPosition.x - 1, tb->mPosition.y - 1, LTexture_GetWidth(tb->mRenderedText) + 2, LTexture_GetHeight(tb->mRenderedText) + 2};
		SDL_RenderDrawRect(*(tb->mRenderedText->gRenderer), &frame);
	}

}

void textBoxUpdate(LTextbox *tb) {
	/* recover pointers from previous text */
	SDL_Window **gWindow = tb->mRenderedText->gWindow;
	SDL_Renderer **gRenderer = tb->mRenderedText->gRenderer;
	TTF_Font *font = tb->mRenderedText->font;

	LTexture_Delete(tb->mRenderedText);
	tb->mRenderedText = LTexture_New();
	LTexture_Init(tb->mRenderedText, gWindow, gRenderer);
	LTexture_SetFont(tb->mRenderedText, font);
	SDL_Color c = {0x00, 0x00, 0x00, 0xFF};
	LTexture_LoadFromRenderedText(tb->mRenderedText, tb->mText, c);
}
