#include "colors.h"


RGB rgbGenRand() {
	RGB c = {
		.R = rand() * 255 / RAND_MAX,
		.G = rand() * 255 / RAND_MAX, 
		.B = rand() * 255 / RAND_MAX,
	};
	return c;
}

RGB* rgbArrayGenRand(int nb) {
	RGB* tab = (RGB *)malloc(sizeof(RGB)*nb);
	int i;
	for (i=0; i<nb; i++) {
		tab[i]=rgbGenRand();
	}
	return tab;
}

bool rgbEqual(RGB c1, RGB c2) {
	return(c1.R == c2.R && c1.G == c2.G && c1.B == c2.B);
}

int rgbColorToInt(RGB c, RGB *tab, int size) {
	int i;
	for(i=0; i<size; i++) {
		if (rgbEqual(c, tab[i])) break; 
	}
	return i;
}

void rgbArrayFree(RGB *tab) {
	free(tab);
}
