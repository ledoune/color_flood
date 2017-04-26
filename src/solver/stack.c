#include "stack.h"

stack stackNew(void) {
    return NULL;
}

void stackFree(stack *s) {
	while(!stackIsEmpty(*s)) {
		stackPop(s);
	}
}

stack stackCopy(stack s) {
	stack tmp = s;
	stack copy = stackNew();

	while(tmp != NULL) {
		stackPush(&copy, tmp->data);
		tmp = tmp->next;
	}

	return copy;
}
 
void stackPush(stack *s, int data) {
    stack tmp = (stack)calloc(1, sizeof(struct node));
    if(tmp == NULL) {
		fprintf(stderr, "Stack push: failled to create a new node!\n");
		exit(1);
	}
    tmp->data = data;
    tmp->next = *s;
    *s = tmp;
}

int stackPop(stack *s) {
	if(*s == NULL) {
		fprintf(stderr, "Stack pop: empty stack!\n");
		exit(1);
	}
    stack tmp = *s;
    int data = (*s)->data;
    *s = (*s)->next;
    free(tmp);
	return data;
}

int stackSize(stack s) {
	int i = 0;
	stack tmp = s;
	while(tmp != NULL) {
		tmp = tmp->next;
		i++;
	}
	return i;
}

void stackPrint(stack s) {
	while(!stackIsEmpty(s)) {
		printf("%d ",s->data);
		s = s->next;
	}
	printf("\n");
}

bool stackIsEmpty(stack s) {
    return s == NULL ? true : false;
}
