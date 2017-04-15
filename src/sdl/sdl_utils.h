#ifndef _SDL_UTILS_H
#define _SDL_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "texture_wrapper.h"
#include "button_wrapper.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640
#define IMG_PATH "img"

bool sdlInit(SDL_Window **gWindow, SDL_Renderer **gRenderer);
void sdlClose(SDL_Window **gWindow, SDL_Renderer **gRenderer);

LButton* sdlCreateButton(SDL_Window **gWindow, SDL_Renderer **gRenderer, const char *text, TTF_Font *font, uint8_t R, uint8_t G, uint8_t B, size_t width, size_t height, int posX, int posY, void (*ptr)(int *));


#endif
