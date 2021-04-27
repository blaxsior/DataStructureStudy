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

//레거시 C 로는 작동 안됨.
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
//		return (Element) { .key = -1 }; //지금 상황에서는 NULL Element를 의미
		return NULL;
	}

	Node* delNode = queue->front;
	queue->front = queue->front->next;
	Element elem = delNode->item;
	free(delNode);
	return elem;
}