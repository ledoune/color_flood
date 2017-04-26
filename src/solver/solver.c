#include <stdlib.h>
#include "stack.h"
#include "../game/game.h"

void solve(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack best, int playedColor);
int* solverComputeAdjMatrix(game *g);
int* solverComputeLblToColorArray(game *g);

int main(void) {

	srand(time(NULL));

	game *g = gameInit(8, 6);
	gamePrint(g);

	int *adjMatrix = solverComputeAdjMatrix(g);
	int *lblToColor = solverComputeLblToColorArray(g);
	int maxDepth = -1;
	stack solution = stackNew();
	stack best = stackNew();
	int *playerLabels = (int *)calloc(gridGetMaxLabel(g->grid), sizeof(int));
	playerLabels[0] = 1;

	solve(adjMatrix, lblToColor, playerLabels, g->grid->maxLabel, g->cNb, &maxDepth, 0, solution, best, -1);

	printf("best: ");
	stackPrint(best);

	stackFree(&solution);
	stackFree(&best);

	free(adjMatrix);
	free(lblToColor);

	gameFree(g);
}

void processNeighbours(game *g, int x, int y, int *adjMatrix) {
	/* labels shifted by -1 because they start at 1 (0 stands for non labelled) */
	int maxLabel = gridGetMaxLabel(g->grid);
	int originLabel = gridGetLabel(g->grid, x, y) - 1;
	int neighbourLabel;
	if(x > 0) {
		neighbourLabel = gridGetLabel(g->grid, x-1, y);
		adjMatrix[originLabel*maxLabel + neighbourLabel-1] = 1;
	}
	if(x < g->size - 1) {
		neighbourLabel = gridGetLabel(g->grid, x+1, y);
		adjMatrix[originLabel*maxLabel + neighbourLabel-1] = 1;
	}
	if(y > 0) {
		neighbourLabel = gridGetLabel(g->grid, x, y-1);
		adjMatrix[originLabel*maxLabel + neighbourLabel-1] = 1;
	}
	if(y < g->size - 1) {
		neighbourLabel = gridGetLabel(g->grid, x, y+1);
		adjMatrix[originLabel*maxLabel + neighbourLabel-1] = 1;
	}
}

int* solverComputeAdjMatrix(game *g) {
	/* a connected component is considered its own neighbour if it's bigger than 1 tile
	 * not sure that the info is useful, might have to be removed for faster solving */
	int maxLabel = gridGetMaxLabel(g->grid);
	int *adjMatrix = (int *)calloc(maxLabel * maxLabel, sizeof(int));
	int i,j;

	for(i=0; i<g->size; i++) {
		for(j=0; j<g->size; j++) {
			processNeighbours(g, i, j, adjMatrix);
		}	
	}

	return adjMatrix;
}

int* solverComputeLblToColorArray(game *g) {
	int *lblToColor = (int *)calloc(gridGetMaxLabel(g->grid), sizeof(int));
	int i, j;

	for(i=0; i<g->size; i++) {
		for(j=0; j<g->size; j++) {
			lblToColor[gridGetLabel(g->grid, i, j) - 1] = rgbColorToInt(gridGetColor(g->grid, i, j), g->cTab, g->cNb);
		}
	}

	return lblToColor;
}

bool solverGameOver(const int *playerLabels, const int maxLabel) {
	/* check from the end as they are the less likely to be marked already */
	int i = maxLabel - 1;
	while(playerLabels[i] != 0 && i > -1) i--;
	return i == -1;
}

void solve(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack best, int playedColor) {
	int *nextColors = (int *)calloc(colorRange, sizeof(int));
	int markedColors = 0, neighbourColor;
	/* play the turn and mark the next colors */
	int i, j, k;
	/* TODO: check if you can get rid of a color */
	for(i=0; i<maxLabel; i++) {
		/* if label connected to topright */
		if(playerLabels[i] == 1) {
			for(j=0; j<maxLabel; j++) {
				/* if neighbour and (right color or first call) and not already connected */
				if(adjMatrix[i*maxLabel + j] == 1 && (lblToColor[j] == playedColor || playedColor == -1) && playerLabels[j] == 0) {
					if(playedColor != -1) playerLabels[j] = 1;
					/* mark neighbour colors of the new label */
					for(k=0; k<maxLabel; k++) {
						if(markedColors == colorRange - 1) break;
						neighbourColor = lblToColor[k];
						if(adjMatrix[j*maxLabel + k] == 1 && neighbourColor != playedColor && nextColors[neighbourColor] == 0 && playerLabels[k] == 0) {
							nextColors[neighbourColor] = 1;
							markedColors++;
						}
					}
				}
			}
		}
	}
	if(playedColor != -1) stackPush(&solution, playedColor);
	/* check if it is a solution and save if it's the case */
	if(solverGameOver(playerLabels, maxLabel)) {
		*maxDepth = stackSize(solution);
		stackFree(&best);
		best = stackCopy(solution);
		printf("best: ");
		stackPrint(best);
	}
	else if((currDepth < *maxDepth - 1 && *maxDepth > colorRange) || *maxDepth == -1) {
		int *newPlayerLabels = NULL;
		for(i=0; i<colorRange; i++) {
			if(nextColors[i] == 1) {
				newPlayerLabels = (int *)calloc(maxLabel, sizeof(int));
				memcpy(newPlayerLabels, playerLabels, maxLabel * sizeof(int));
				solve(adjMatrix, lblToColor, newPlayerLabels, maxLabel, colorRange, maxDepth, currDepth + 1, solution, best, i);
			}
		}
	}
	if(currDepth > 0) stackPop(&solution);
	free(nextColors);
	free(playerLabels);
}
