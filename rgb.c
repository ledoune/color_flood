#include "rgb.h"


RGB rgbNew(int R, int G, int B) {
	RGB c = {
		.R = R % 256,
		.G = G % 256,
		.B = B % 256,
	};
	return c;
}

RGB* rgbImport(FILE *fp, int cNb) {

	char buffer[256];
	RGB *cTab = (RGB *)malloc(sizeof(RGB) * cNb);
	int R, G, B;

	int i;
	for(i=0; i < cNb; i++) {
		fgets(buffer, sizeof(buffer), fp);
		if(sscanf(buffer, "%d %d %d", &R, &G, &B) != 3) {
			printf("Not a valid save file\n");
			exit(1);
		}
		cTab[i] = rgbNew(R,G,B);
	}
	return cTab;
}

void rgbExport(FILE *fp, RGB *cTab, int cNb) {
	int i;
	for(i=0; i < cNb; i++) {
		fprintf(fp, "%d %d %d\n", cTab[i].R, cTab[i].G, cTab[i].B);
	}
}

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
	assert(nb > 0);
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
