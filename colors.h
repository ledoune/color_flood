#ifndef COLORS_H
#define COLORS_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct t_RGB {
	char R;
	char G;
	char B;
} RGB;

RGB rgbGenRand();
RGB* rgbArrayGenRand(int nb);
bool rgbEqual(RGB c1, RGB c2);
int rgbColorToInt(RGB c, RGB* tab, int size);
void rgbArrayFree(RGB *tab);

#endif
