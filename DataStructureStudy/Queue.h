#include "Element.h"
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
	Node* front;
	Node* rear;
}Queue;

int isQueueEmpty(Queue* queue)
{
	return (queue->front == NULL);
}

//레거시 C 로는 작동 안됨.
void AddQueue(Queue* queue, element item)
{
	if (queue->front == NULL)
	{
		queue->front = &(Node) { .item = item, .next = NULL };
		queue->rear = queue->front;
	}
	queue->rear->next = &(Node) { .item = item, .next = NULL };

}

element DelQueue(Queue* queue)
{
	if (queue->front == NULL)
	{
		return (element) { .key = -1; }; //지금 상황에서는 NULL Element를 의미
	}

	Node* delNode = queue->front;

	queue->front = queue->front->next;
}