#ifndef _TEXTBOX_WRAPPER_H
#define _TEXTBOX_WRAPPER_H

#include "texture_wrapper.h"

typedef enum textboxState {
	TEXTBOX_NEUTRAL,
	TEXTBOX_SELECTED
} textboxState;

typedef struct textbox {
	char *mText;
	int mTextLength;
	LTexture *mRenderedText;
	SDL_Point mPosition;
	textboxState ts;
} LTextbox;

/* constructor destructor */
LTextbox* LTextbox_New(SDL_Window **gWindow, SDL_Renderer **gRenderer, TTF_Font *font);
void LTextbox_Delete(LTextbox *tb);

/* set attributes */
void LTextbox_SetStr(LTextbox *tb, char *str, int length);
void LTextbox_SetPosition(LTextbox *tb, int x, int y);

/* handle mouse and keyboard */
void LTextbox_HandleEvent(LTextbox *tb, SDL_Event *e);

/* render */
void LTextbox_Render(LTextbox *tb);

/* updater for texture */
void textBoxUpdate(LTextbox *tb);

#endif
