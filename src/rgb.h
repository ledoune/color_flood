#ifndef RGB_H
#define RGB_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef struct t_RGB {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} RGB;

void rgbPrint(RGB c);
void rgbArrayPrint(RGB *tab, int size);
RGB rgbGenRand();
RGB* rgbArrayGenRand(int nb);
bool rgbEqual(RGB c1, RGB c2);
int rgbColorToInt(RGB c, RGB* tab, int size);
void rgbArrayFree(RGB *tab);
bool rgbArrayHasDuplicate(RGB *tab, int size);

#endif
