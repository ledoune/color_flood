#include "rgb.h"


void rgbPrint(RGB c) {
	printf("%02x%02x%02x\n",c.R,c.G,c.B);
}

void rgbArrayPrint(RGB *tab, int size) {
	int i;
	for(i=0; i<size; i++) {
		printf("%d : ",i);
		rgbPrint(tab[i]);
	}
}

RGB rgbGenRand() {
	RGB c = {
		.R = rand() % 256,
		.G = rand() % 256, 
		.B = rand() % 256,
	};
	return c;
}

RGB* rgbArrayGenRand(int nb) {
	RGB* tab = (RGB *)malloc(sizeof(RGB)*nb);
	if(!tab) exit(1);
	int i;
	for (i=0; i<nb; i++) {
		tab[i]=rgbGenRand();
	}
	return tab;
}

bool rgbArrayHasDuplicate(RGB *tab, int size) {
	bool res = false;
	int i,j;
	for(i=0; i<size-1; i++) {
		for(j=i+1; j<size; j++) {
			res = rgbEqual(tab[i],tab[j]);
			if(res) break;
		}
		if(res) break;
	}
	return res;
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
