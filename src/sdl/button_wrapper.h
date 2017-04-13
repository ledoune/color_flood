#include "sdl_utils.h"
#include "texture_wrapper.h"

typedef struct button {
	/* top left position */
	SDL_Point mPosition;
	LTexture *mNeutralTexture;
	LTexture *mHoveredTexture;
	/*
	 * LTexture *mClickedTexture;
	 */
} LButton;

/* Contructor Destructor */
LButton* LButton_New(void);
void LButton_Delete(LButton *b);

/* set attributes */
void LButton_SetPosition(int x, int y);
void LButton_SetLTexture(LButton *b, LTexture *t);

/* handle mouse */
void LButton_HandleEvent(LButton *b, SDL_Event *e);

/* render button */
void LButton_Render(LButton *b);


