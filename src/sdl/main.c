#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool init(SDL_Window **gWindow, SDL_Surface **gScreenSurface);
bool loadBMP(SDL_Surface** gImage, char *name);
void quit(SDL_Surface **image, SDL_Window **window);

int main( int argc, char* args[] ) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* bmpSurface = NULL;

    if(!init(&window, &screenSurface)) {
        fprintf(stderr, "Failed to initialize\n");
    }
    else {
        if(!loadBMP(&bmpSurface, "hello_world.bmp")) {
            fprintf(stderr, "Failed to load bmp\n");
        }
        else {
            SDL_BlitSurface( bmpSurface, NULL, screenSurface, NULL );
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }

    quit(&bmpSurface, &window);
    return 0;
}

bool init(SDL_Window **gWindow, SDL_Surface **gScreenSurface) {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        *gWindow = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( *gWindow == NULL ) {
            fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            *gScreenSurface = SDL_GetWindowSurface( *gWindow );
        }
    }
    return success;
}

bool loadBMP(SDL_Surface** gImage, char *name) {
    bool success = true;
    *gImage = SDL_LoadBMP( name );
    if( *gImage == NULL ) {
        fprintf(stderr, "Unable to load image %s! SDL Error: %s\n", name, SDL_GetError() );
        success = false;
    }
    return success;
}

void quit(SDL_Surface **image, SDL_Window **window) {
    SDL_FreeSurface( *image );
    image = NULL;

    SDL_DestroyWindow( *window );
    window = NULL;

    SDL_Quit();

}
