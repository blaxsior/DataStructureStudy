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

//���Ž� C �δ� �۵� �ȵ�.
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
		return (element) { .key = -1; }; //���� ��Ȳ������ NULL Element�� �ǹ�
	}

	Node* delNode = queue->front;

	queue->front = queue->front->next;
}