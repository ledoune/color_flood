#include "stack.h"

int main(void) {
	stack s1 = stackNew();
	int i;
	for(i=0; i<10; i++) stackPush(&s1, i);

	stack s2 = stackCopy(s1);

	stackPrint(s1);
	stackPrint(s2);

	printf("%d, %d, %d\n", stackSize(s1), stackPop(&s1), stackSize(s1));

	stackPrint(s1);
	stackPrint(s2);

	stackFree(&s1);
	stackFree(&s2);

	return 0;
}
