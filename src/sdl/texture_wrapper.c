#include "texture_wrapper.h"

LTexture* LTexture_New(void) {
	LTexture *t = (LTexture *)calloc(1, sizeof(LTexture));
	
	t->mTexture = NULL;
	t->mWidth = 0;
	t->mHeight = 0;
	t->font = NULL;
	t->gWindow = NULL;
	t->gRenderer = NULL;

	return t;
}

void LTexture_Delete(LTexture *t) {
	LTexture_Clear(t);
	if(t->font != NULL) {
		TTF_CloseFont(t->font);
		t->font = NULL;
	}
	t->gWindow = NULL;
	t->gRenderer = NULL;
	free(t);
}

void LTexture_Init(LTexture *t, SDL_Window **gWindow, SDL_Renderer **gRenderer) {
	t->gWindow = gWindow;
	t->gRenderer = gRenderer;
}

void LTexture_Clear(LTexture *t) {
	if(t->mTexture != NULL) {
		SDL_DestroyTexture(t->mTexture);
		t->mTexture = NULL;
		t->mWidth = 0;
		t->mHeight = 0;
	}
}

bool LTexture_LoadFont(LTexture *t, const char *path, size_t size) {
	bool success = true;

	t->font = TTF_OpenFont(path, size);
	if(t->font == NULL) {
		fprintf(stderr,"Failed to load the font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}

bool LTexture_LoadFromFile(LTexture *t, const char *path) {
	LTexture_Clear(t);

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL) {
		fprintf(stderr,"Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else {
		/* set the color 0x00FFFF transparent
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		*/

        newTexture = SDL_CreateTextureFromSurface(*(t->gRenderer), loadedSurface);
		if(newTexture == NULL) {
			fprintf(stderr,"Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else {
			t->mWidth = loadedSurface->w;
			t->mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	t->mTexture = newTexture;
	return t->mTexture != NULL;
}

bool LTexture_LoadFromRenderedText(LTexture* texture, const char *text, SDL_Color color) {
	LTexture_Clear(texture);

	SDL_Surface *textSurface = TTF_RenderText_Blended(texture->font, text, color);
	if(textSurface == NULL) {
		fprintf(stderr,"Unable to render text surface : SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		texture->mTexture = SDL_CreateTextureFromSurface(*(texture->gRenderer), textSurface);
		if(texture->mTexture == NULL) {
			fprintf(stderr,"Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			texture->mWidth = textSurface->w;
			texture->mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return texture->mTexture != NULL;
}	

bool LTexture_SetGeometryMode(LTexture *t, size_t width, size_t height) {
	if(t->gRenderer == NULL) {
		fprintf(stderr, "Unable to set texture as geometry target! Need to attach a renderer\n");
	}
	t->mTexture = SDL_CreateTexture(*(t->gRenderer), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if(t->mTexture == NULL) {
		fprintf(stderr,"Unable to create blank render target! SDL_Error : %s\n", SDL_GetError());
	}
	else {
		t->mWidth = width;
		t->mHeight = height;
		LTexture_SetAsRenderTarget(t);
	}

	return t->mTexture != NULL;
}

void LTexture_SetAsRenderTarget(LTexture *t) {
	/* verif gRenderer != NULL ? */
	SDL_SetRenderTarget(*(t->gRenderer),t->mTexture);
}

void LTexture_SetColor(LTexture *t, uint8_t red, uint8_t green, uint8_t blue) {
	SDL_SetTextureColorMod(t->mTexture, red, green, blue);
}

void LTexture_SetBlendMode(LTexture *t, SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(t->mTexture, blending);
}
		
void LTexture_SetAlpha(LTexture *t, uint8_t alpha) {
	SDL_SetTextureAlphaMod(t->mTexture, alpha);
}



void LTexture_Render(LTexture *t, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = {x, y, t->mWidth, t->mHeight};

	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(*(t->gRenderer), t->mTexture, clip, &renderQuad, angle, center, flip);

}

size_t LTexture_GetWidth(LTexture *t) {
	return t->mWidth;
}

size_t LTexture_GetHeight(LTexture *t) {
	return t->mHeight;
}

SDL_Renderer* LTexture_GetRenderer(LTexture *t) {
	return *(t->gRenderer);
}

SDL_Window* LTexture_GetWindow(LTexture *t) {
	return *(t->gWindow);
}
