#include "colors.h"
#include "grid.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	srand(time(NULL));
	printf("%d\n",rand() % 255);
	grid* g = gridInit(10);
	RGB *cTab = rgbArrayGenRand(6);
	rgbArrayPrint(cTab, 6);
	gridInitColors(g, cTab, 6);
	int i;
	for(i=0; i < (g->size * g->size); i++) {
		printf("%d : %d\n",i,rgbColorToInt(g->rgbGrid[i], cTab, 6));
	}
	assert(rgbEqual(cTab[0],cTab[0]) && !rgbEqual(cTab[1],cTab[0]));
	gridFree(g);
	free(cTab);

	return 0;
}
