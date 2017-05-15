#include "solver.h"

int printBest(game *g) {
	int *adjMatrix = solverComputeAdjMatrix(g);
	int *lblToColor = solverComputeLblToColorArray(g);
	int maxDepth = -1;
	stack solution = stackNew();
	stack best = stackNew();
	int *playerLabels = (int *)calloc(gridGetMaxLabel(g->grid), sizeof(int));
	playerLabels[0] = 1;

	if(g->size < 7) {
		solveBruteForce(adjMatrix, lblToColor, playerLabels, gridGetMaxLabel(g->grid), g->cNb, &maxDepth, 0, solution, &best, -1);
		printf("Solution by bruteforce: ");
	}
	else {
		solveHeuristic(adjMatrix, lblToColor, playerLabels, gridGetMaxLabel(g->grid), g->cNb, &maxDepth, 0, solution, &best, -1);
		printf("Solution by heuristic: ");
	}

	stackPrint(best);
	int solutionSize = stackSize(best);

	stackFree(&solution);
	stackFree(&best);

	free(adjMatrix);
	free(lblToColor);

	return solutionSize;
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
	while(i > -1 && playerLabels[i] != 0) i--;
	return i == -1;
}

void solveBruteForce(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack *best, int playedColor) {
	int *nextColors = (int *)calloc(colorRange, sizeof(int));
	int markedColors = 0, neighbourColor;
	/* play the turn and mark the next colors */
	int i, j, k;

	/* TODO: check if you can get rid of a color to prune the tree */
	/* TODO: add a total color played counter */
	/* TODO: to provide every solution of the optimal size, change the recursion tests && solution stockage (ie linked list) */
	/* TODO: find out why the solver doesn't always launch; probably doesn't find a color to play, but why ? */
	/* TODO: make the code prettier and organized */
	/* TODO: Double linked list instead of a "matrice creuse" */

	/************** PLAY THE COLOR && TAG NEIGHBOUR COLORS ********************/
	if(playedColor == -1) {
		/* if first turn, no color played, you want to tag colors next to lbl 1 */
		for(k=0; k<maxLabel; k++) {
			if(markedColors == colorRange - 1) break;
			neighbourColor = lblToColor[k];
			if(adjMatrix[k] == 1 && nextColors[neighbourColor] == 0 && playerLabels[k] == 0) {
				nextColors[neighbourColor] = 1;
				markedColors++;
			}
		}
	}
	else {
		for(i=0; i<maxLabel; i++) {
			/* if label connected to topright */
			if(playerLabels[i] == 1) {
				for(j=0; j<maxLabel; j++) {
					if(adjMatrix[i*maxLabel + j] == 1 && playerLabels[j] == 0) {
						/* if neighbour and not already connected */
						if(lblToColor[j] == playedColor) {
							playerLabels[j] = 1;
							/* mark neighbour colors of the new label */
							for(k=0; k<maxLabel; k++) {
								if(markedColors == colorRange - 1) break;
								neighbourColor = lblToColor[k];
								if(adjMatrix[j*maxLabel + k] == 1 && nextColors[neighbourColor] == 0 && playerLabels[k] == 0 && lblToColor[k] !=playedColor) {
									nextColors[neighbourColor] = 1;
									markedColors++;
								}
							}

						}
						else {
							if(nextColors[lblToColor[j]] == 0) {
								neighbourColor = lblToColor[j];
								nextColors[neighbourColor] = 1;
								markedColors++;
							}
						}
												
					}
				}
			}
		}
	}

	/************** ADD PLAYED COLOR TO CURRENT SOLUTION ********************/
	if(playedColor != -1) stackPush(&solution, playedColor);

	/************** IF GAME OVER SAVE SOLUTION IN BEST ********************/
	if(solverGameOver(playerLabels, maxLabel)) {
		*maxDepth = stackSize(solution);
		stackFree(best);
		/* NB stackCopy reverse the stack, so the first turns are on top */
		*best = stackCopy(solution);
	}
	else if((currDepth < *maxDepth - 1 && *maxDepth > colorRange) || *maxDepth == -1) {
	/************** ELSE KEEP GOING FOR EVERY MARKED COLOR ********************/
		int *newPlayerLabels = NULL;
		/* TEST: a lot of 0 1 3 0 1 0 2... in the solution, so maybe starting the recursion with a random color is good ?
		 * Don't know about the cost of generating a random number tho */
		int colorOffset = rand() % colorRange;
		for(i=0; i<colorRange; i++) {
			j = (i + colorOffset) % colorRange;
			if(nextColors[j] == 1) {
				newPlayerLabels = (int *)calloc(maxLabel, sizeof(int));
				memcpy(newPlayerLabels, playerLabels, maxLabel * sizeof(int));
				solveBruteForce(adjMatrix, lblToColor, newPlayerLabels, maxLabel, colorRange, maxDepth, currDepth + 1, solution, best, j);
			}
		}
	}
	/************** POP PLAYED COLOR & FREE TEMP ARRAYS ********************/
	if(currDepth > 0) stackPop(&solution);
	free(nextColors);
	free(playerLabels);
}

void solveHeuristic(const int *adjMatrix, const int *lblToColor, int *playerLabels, const int maxLabel, const int colorRange, int *maxDepth, int currDepth, stack solution, stack *best, int playedColor) {
	int *nextColors = (int *)calloc(colorRange, sizeof(int));
	int *countedLabels = (int *)calloc(maxLabel, sizeof(int));
	int neighbourColor;
	/* play the turn and mark the next colors */
	int i, j, k;

	/************** PLAY THE COLOR && TAG NEIGHBOUR COLORS ********************/
	if(playedColor == -1) {
		/* if first turn, no color played, you want to tag colors next to lbl 1 */
		for(k=0; k<maxLabel; k++) {
			neighbourColor = lblToColor[k];
			if(adjMatrix[k] == 1 && playerLabels[k] == 0) {
				nextColors[neighbourColor] += 1;
			}
		}
	}
	else {
		for(i=0; i<maxLabel; i++) {
			/* if label connected to topright */
			if(playerLabels[i] == 1) {
				for(j=0; j<maxLabel; j++) {
					if(adjMatrix[i*maxLabel + j] == 1 && playerLabels[j] == 0) {
						/* if neighbour and right color and not already connected */
						if(lblToColor[j] == playedColor) {
							playerLabels[j] = 1;
							/* mark neighbour colors of the new label */
							for(k=0; k<maxLabel; k++) {
								neighbourColor = lblToColor[k];
								if(adjMatrix[j*maxLabel + k] == 1 && playerLabels[k] == 0 && countedLabels[k] == 0 && lblToColor[k] != playedColor) {
									nextColors[neighbourColor] += 1;
									countedLabels[k] = 1;
								}
							}
						}
						else {
							if(countedLabels[j] == 0) {
								neighbourColor = lblToColor[j];
								nextColors[neighbourColor] += 1;
								countedLabels[j] = 1;
							}
						}
					}
				}
			}
		}
	}

	/************** ADD PLAYED COLOR TO CURRENT SOLUTION ********************/
	if(playedColor != -1) stackPush(&solution, playedColor);

	/************** IF GAME OVER SAVE SOLUTION IN BEST ********************/
	if(solverGameOver(playerLabels, maxLabel)) {
		*maxDepth = stackSize(solution);
		stackFree(best);
		/* NB stackCopy reverse the stack, so the first turns are on top */
		*best = stackCopy(solution);
	}
	else if((currDepth < *maxDepth - 1 && *maxDepth > colorRange) || *maxDepth == -1) {
	/************** ELSE KEEP GOING FOR EVERY MARKED COLOR ********************/
		int *newPlayerLabels = NULL;
		int maxNeighbourLabel = 0;

		for(i=1; i<colorRange; i++) {
			if(nextColors[i] > nextColors[maxNeighbourLabel]) {
				maxNeighbourLabel = i;
			}
		}
		newPlayerLabels = (int *)calloc(maxLabel, sizeof(int));
		memcpy(newPlayerLabels, playerLabels, maxLabel * sizeof(int));
		solveHeuristic(adjMatrix, lblToColor, newPlayerLabels, maxLabel, colorRange, maxDepth, currDepth + 1, solution, best, maxNeighbourLabel);

	}
	/************** POP PLAYED COLOR & FREE TEMP ARRAYS ********************/
	if(currDepth > 0) stackPop(&solution);
	free(countedLabels);
	free(nextColors);
	free(playerLabels);
}
