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

//������ ���� ���� element�� �ִ´�.
void LSPush(LinkedStack* stack, element elem)
{
	Node_O* tempNode = NodeInit(elem);

	tempNode->next = stack->top;
	stack->top = tempNode;
}

//������ ���� ���� ���� �ڷḦ �����Ѵ�. �̶� stack->top �� NULL�̶��, false�� �ǹ̷� 0�� ��ȯ�Ѵ�.
element LSPop(LinkedStack* stack)
{
	if (stack->top == NULL) // top�� ���� NULL checking �ʿ�.
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