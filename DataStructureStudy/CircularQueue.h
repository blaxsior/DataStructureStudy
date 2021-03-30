#include "Element.h"
#include <stdio.h>
#define MAX_SIZE 4

element CirQueue[MAX_SIZE];
int front = 0;
int rear = 0;
//rear == front + 1 일때 꽉 찬 상태
//rear == front 일때 empty


int idxCalc(int idx)
{
	return (idx + 1) % MAX_SIZE;
}//다음 인덱스를 찾아준다.

int isEmptyCQ() //front == rear 일때 empty 상태
{
	return front == rear;
}

int isFullCQ() //front + 1 인덱스가 rear일때 full 상태
{
	return rear == idxCalc(front);
}

void addCQueue(element item)
{
	if (!isFullCQ()) // full 이 아닌 상황에만 add 를 수행한다.
	{
		CirQueue[front] = item;
		front = idxCalc(front);
	}
	else
	{
		printf("Queue is full\n");
	}
}

element delCQueue() 
{
	if (!isEmptyCQ()) //empty가 아니라면 수행
	{
		element delElem = CirQueue[rear];
		rear = idxCalc(rear);
		return delElem;
	}
	else
	{
		printf("queue is empty\n");
		return (element) { .value = 0, };
	}
}

//Example
//#include <stdio.h>
//#include "CircularQueue.h"
//
//int main()
//{
//	delCQueue();// can't get
//	addCQueue((element) { .value = 1 });
//	addCQueue((element) { .value = 2 });
//	addCQueue((element) { .value = 3 });//circular queue is full!!
//	addCQueue((element) { .value = 4 });
//
//	delCQueue();
//	delCQueue();
//
//	addCQueue((element) { .value = 5 });
//	addCQueue((element) { .value = 6 });
//
//	while (!isEmptyCQ())
//	{
//		printf("%d\n", delCQueue().value);
//	}//dequeue while Circular queue is not empty. 
//}