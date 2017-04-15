#ifndef _BUTTON_WRAPPER_H
#define _BUTTON_WRAPPER_H

#include "sdl_utils.h"
#include "texture_wrapper.h"

enum LButtonState {
	LBUTTON_NEUTRAL,
	LBUTTON_HOVERED,
	LBUTTON_PRESSED
};

typedef struct button {
	/* top left position */
	SDL_Point mPosition;
	LTexture *mBackground;
	LTexture *mText;
	/*
	 * LTexture *mClickedTexture;
	 * LTexture *mHoveredTexture;
	 */
	enum LButtonState s;
	void (*triggerPtr)(void);
} LButton;

/* Contructor Destructor */
LButton* LButton_New(void);
void LButton_Delete(LButton *b);

/* set attributes */
void LButton_SetPosition(LButton *b, int x, int y);
void LButton_SetBackground(LButton *b, LTexture *t);
void LButton_SetText(LButton *b, LTexture *t);
void LButton_SetAction(LButton *b, void (*ptr)(void));

/* handle mouse */
void LButton_HandleEvent(LButton *b, SDL_Event *e);

/* render button */
void LButton_Render(LButton *b);

#endif
