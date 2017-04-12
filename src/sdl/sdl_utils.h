#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
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

bool init(SDL_Window **gWindow, SDL_Surface **gScreenSurface);
void quit(SDL_Surface **array, SDL_Window *window);

SDL_Surface* loadBMP(char *name);
bool loadAllMedia(SDL_Surface **array);

int handleArrowsEvents(SDL_Event *e);

#endif
