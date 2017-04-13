#ifndef _SDL_UTILS_H
#define _SDL_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640
#define IMG_PATH "img"

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool sdlInit(SDL_Window **gWindow, SDL_Renderer **gRenderer);
void sdlClose(SDL_Window **gWindow, SDL_Renderer **gRenderer);

SDL_Surface* loadBMP(char *name);
bool loadAllMedia(SDL_Surface **array);

int handleArrowsEvents(SDL_Event *e);

#endif
