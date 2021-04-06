#include "LinkedStack.h"

int main()
{
	LinkedStack stack;
	LStackInit(&stack);
	LSPop(&stack);
	LSPush(&stack, 10);
	LSPush(&stack, 11);
	LSPush(&stack, 12);
	LSPush(&stack, 13);
	LSPush(&stack, 14);
	LSPush(&stack, 15);
	LSPush(&stack, 16);


	while (stack.top != NULL)
	{
		printf("%d\n", LSPop(&stack));
	}

	return 0;
}