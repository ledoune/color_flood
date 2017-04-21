#include "solveur1.h"


Stack *stackNew(void){
    Stack *res = (Stack*)calloc(1,sizeof(Stack));
    res->g = NULL;
    res->color = -1;
    res->NbAttempts = 0;
    res->next = NULL;
    res->size = 0;
    return res;
}

Stack* cons(Stack* s, game* g, int c, int NbA)
{
  Stack *res = stackNew();
  res->g = g;
  res->color = c;
  res->NbAttempts = NbA;
  res->next = s;
  res->size = (s->size)+1;
  return res;
}

void stackFree(Stack *stack){
    free(stack);
}

int stackEmpty(Stack *stack){
    return (stack->size == 0);
}

int stackSize(Stack *stack) {
    return stack->size;
}

int stackPush(Stack *stack, game* g, int c, int NbA){
    Stack *pushed;
    if ((pushed = cons(stack, g, c, NbA)) == NULL)
        return -1;
    *stack = *pushed;
    return 0;
}

int stackPop(Stack *stack){
    if (stack == stackNew())
        return -1;
    stack->size--;
    *stack = *stack->next;
    return 0;
}

Stack* stackReverse(Stack* s) {
    Stack* res = stackNew();
    while (!stackEmpty(s)) {
        res = cons(res, s->g, s->color, s->NbAttempts);
        s=s->next;
    }
    return res;
}


/*********************************************/
/*********************************************/
/*********************************************/


bool solveurChoice(game* g, RGB c) {
    return (!rgbEqual(g->cPlayer, c));
}

bool solveurIsSolution(Stack* solution) {
    return gameOver(solution->g);
}

ensSol* solveurNewSolution(ensSol** oldSolutions, Stack** newSolution) {
    ensSol* Solutions = (ensSol*)calloc(1,sizeof(ensSol));
    /*if (oldSolutions->size > stackSize(newSolution)) {*/
        (Solutions)->sol = *newSolution;
        (Solutions)->next = *oldSolutions;
        (Solutions)->size = (*oldSolutions)->size +1;

    return Solutions;
}

void solveurPlayTurn(game* g, game* g2, int color) {
    gameCopy(g, g2);
    gridSetColor(g2->grid, g2->cTab[color], 0, 0);
    gridFloodFillColor(g2->grid, 0, 0);
    gridSetLabel(g2->grid, gridGetMaxLabel(g2->grid) + g2->turnCount, 0, 0);
    gridFloodFillLabel(g2->grid, 0, 0);
    g2->cPlayer = g2->cTab[color];
    g2->turnCount++;
}

void solv(game* g, Stack** solution, ensSol** oldSolutions, int* lim) {
    int color=0;
    if (!((*oldSolutions)->size == 0)) *lim = ((*oldSolutions)->sol)->NbAttempts;
    game* g2 = gameInit(g->size,g->cNb);
    while ((g->turnCount < *lim)&&(color<g->cNb)) {

        if (solveurChoice(g, g->cTab[color])) {
            solveurPlayTurn(g, g2, color);
            stackPush(*solution, g2, color, g2->turnCount);
            if (solveurIsSolution(*solution))  {
                *oldSolutions=solveurNewSolution(oldSolutions, solution);
                printf("Coucou %d, %d, %d\n", *lim, (*solution)->NbAttempts, g2->turnCount);
            }
            else solv(g2, solution, oldSolutions, lim);

            stackPop(*solution);
        }

        color++;
    }

}


void solveurPrint(Stack *solution) {
    int k=1;
    while (!stackEmpty(solution)) {
        printf("%deme coup : couleur %d\n",k,solution->color);
        k++;
        stackPop(solution);
    }
}

int main() {
    game* g = gameInit(10,6);
    int lim = 30;
    /*game** stock = (game**)calloc(1,sizeof(game*));
    stock[0] = g;
    int nbTries=0;*/
    ensSol* oldSolutions = (ensSol*)calloc(1,sizeof(ensSol));
    oldSolutions->sol = stackNew();
    oldSolutions->next = NULL;
    oldSolutions->size = 0;
    Stack* solution = stackNew();
    solv(g, &solution, &oldSolutions, &lim);

    solveurPrint(stackReverse(oldSolutions->sol));

    return 0;
}
