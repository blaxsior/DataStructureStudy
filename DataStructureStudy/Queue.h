#include "Element.h"
#include <stdlib.h>

typedef struct
{
	Node* front;
	Node* rear;
}Queue;

void QueueInit(Queue* queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}

int isQueueEmpty(Queue* queue)
{
	return (queue->front == NULL);
}

//���Ž� C �δ� �۵� �ȵ�.
void AddQueue(Queue* queue, Element item)
{
	if (queue->front == NULL)
	{
		queue->front = NodeInit(item);
		queue->rear = queue->front;
		return;
	}
	queue->rear->next = NodeInit(item);
	queue->rear = queue->rear->next;
}

Element DelQueue(Queue* queue)
{
	if (queue->front == NULL)
	{
//		return (Element) { .key = -1 }; //���� ��Ȳ������ NULL Element�� �ǹ�
		return NULL;
	}

	Node* delNode = queue->front;
	queue->front = queue->front->next;
	Element elem = delNode->item;
	free(delNode);
	return elem;
}