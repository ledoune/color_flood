#ifndef _TEXTURE_WRAPPER_H
#define _TEXTURE_WRAPPER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct texture {
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
	/* in case text is needed */
	TTF_Font *font;
	/* window and renderer attached */
	SDL_Window **gWindow;
	SDL_Renderer **gRenderer;
} LTexture;

/* Contructeurs Destructeurs */
LTexture* LTexture_New(void);
void LTexture_Delete(LTexture *t);

/* attach a texture to a window and renderer */
void LTexture_Init(LTexture *t, SDL_Window **gWindow, SDL_Renderer **gRenderer);
void LTexture_SetFont(LTexture *t, TTF_Font *font);
/* reset mTexture, mWidth, mHeight */
void LTexture_Clear(LTexture *t);

/* Load font from a .ttf file */
bool LTexture_LoadFont(LTexture *t, const char *path, size_t size);
/* Load texture from a file (type in sdlInit) */
bool LTexture_LoadFromFile(LTexture *t, const char *path);
/* Load a text texture from the string in parameters */
bool LTexture_LoadFromRenderedText(LTexture *texture, const char *text, SDL_Color color);
/* to render geometry to texture */
bool LTexture_SetGeometryMode(LTexture *t, size_t width, size_t height);
void LTexture_SetAsRenderTarget(LTexture *t);

/* rendering parameters */
void LTexture_SetColor(LTexture *t, uint8_t red, uint8_t green, uint8_t blue);
void LTexture_SetBlendMode(LTexture *t, SDL_BlendMode blending);
void LTexture_SetAlpha(LTexture *t, uint8_t alpha);

/* default values : *t, x, y, NULL, 0, NULL, SDL_FLIP_NONE) */	
void LTexture_Render(LTexture *t, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

/* access info */
int LTexture_GetWidth(LTexture *t);
int LTexture_GetHeight(LTexture *t);
TTF_Font* LTexture_GetFont(LTexture *t);
SDL_Renderer* LTexture_GetRenderer(LTexture *t);
SDL_Window* LTexture_GetWindow(LTexture *t);

#endif
