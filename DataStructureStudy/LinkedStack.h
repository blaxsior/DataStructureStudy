#include <stdlib.h>
#include <stdio.h>
#include "Element.h"

typedef struct {
	Node_O* top;
} LinkedStack;

void LStackInit(LinkedStack* stack)
{
	stack->top = NULL;
}

//스택의 가장 위에 element를 넣는다.
void LSPush(LinkedStack* stack, element elem)
{
	Node_O* tempNode = NodeInit(elem);

	tempNode->next = stack->top;
	stack->top = tempNode;
}

//스택의 가장 위에 쌓인 자료를 제거한다. 이때 stack->top 이 NULL이라면, false의 의미로 0을 반환한다.
element LSPop(LinkedStack* stack)
{
	if (stack->top == NULL) // top에 대한 NULL checking 필요.
	{
		printf("There is no element in this stack.\n");
		return 0;
	}
	else
	{
		Node_O* tempNode = stack->top->next;
		element returnValue = stack->top->item;
		free(stack->top);
		stack->top = tempNode;
		return returnValue;
	}
}