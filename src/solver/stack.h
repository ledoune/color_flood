#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node* next;
};

typedef struct node* stack;

/*constructor destructor */
stack stackNew(void);
void stackFree(stack *s);

stack stackCopy(stack s);

/* push pop */
void stackPush(stack *s, int data);
int stackPop(stack *s);

int stackSize(stack s);

void stackPrint(stack s);

/* empty test */
bool stackIsEmpty(stack s);

#endif
