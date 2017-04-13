#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <math.h>

Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{ // function from lazyFoo.net
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{ // function from lazyFoo.net
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[ ( y * surface->w ) + x ] = pixel;
}

void floodfill(SDL_Surface *surface, int x, int y)
{
    Uint32 color = 0xFFFFFF; //get_pixel32(surface, x, y);
    Uint32 fillcolor = 0xFFFFFF;
    put_pixel32(surface, x, y, fillcolor);

    //SDL_Delay(1);
    //SDL_Flip(surface);

    if(x>1) // left
    {
        if(get_pixel32(surface, x-1, y)!=color)
        {
            floodfill(surface, x-1, y);
        }
    }

    if(x<260-1) // Right
    {
        if(get_pixel32(surface, x+1, y)!=color)
        {
            floodfill(surface, x+1, y);
        }
    }

    if(y>1) // Up
    {
        if(get_pixel32(surface, x,  y-1)!=color)
        {
            floodfill(surface, x,  y-1);
        }
    }

    if(y<260-1) // Down
    {
        if(get_pixel32(surface, x,  y+1)!=color)
        {
            floodfill(surface, x,  y+1);
        }
    }
}

int main(int argc, char *argv[]) {
    // Program modified from infoc.eet.bme.hu
    SDL_Event event;
    SDL_Surface *screen;
    int elozox, elozoy, click, quit, rajzoltam;

    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO);
    screen=SDL_SetVideoMode(260, 260, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("SDL FloodFill Example", "SDL FloodFill Example");

    /* az esemenyvezerelt hurok */
    quit = 0;
    click = 0;
    elozox = 0;
    elozoy = 0;
    while (!quit) {
        SDL_WaitEvent(&event);

        rajzoltam = 0;

        switch (event.type) {
            /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = 1;
                    elozox = event.button.x;
                    elozoy = event.button.y;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    //boxColor(screen, 0, 0, 359, 359, 0x000000FF);
                    floodfill(screen, event.button.x, event.button.y);
                    //put_pixel32(screen, event.button.x, event.button.y, 0xFFFFFF );
                    rajzoltam = 1;
                }
                break;
            /* egergomb elengedese */
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = 0;
                }
                break;
            /* eger mozdulat */
            case SDL_MOUSEMOTION:
                if (click) {
                    lineColor(screen, elozox, elozoy,
                                        event.motion.x, event.motion.y, 0xFFFFFFFF);
                    rajzoltam = 1;
                }
                /* a kovetkezo mozdulat esemenyhez */
                elozox = event.motion.x;
                elozoy = event.motion.y;
                break;
            case SDL_KEYDOWN:
                boxColor(screen, 0, 0, 359, 359, 0x000000FF);
                rajzoltam = 1;
                break;
            /* ablak bezarasa */
            case SDL_QUIT:
                quit=1;
                break;
        }

        if (rajzoltam)
            SDL_Flip(screen);
    }

    SDL_Quit();

    return 0;
}
