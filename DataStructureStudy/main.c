#include <stdio.h>
#include "CircularQueue.h"

int main()
{
	delCQueue();// can't get
	addCQueue((element) { .value = 1 });
	addCQueue((element) { .value = 2 });
	addCQueue((element) { .value = 3 });//circular queue is full!!
	addCQueue((element) { .value = 4 });
	
	delCQueue();
	delCQueue();

	addCQueue((element) { .value = 5 });
	addCQueue((element) { .value = 6 });

	while (!isEmptyCQ())
	{
		printf("%d\n", delCQueue().value);
	}//dequeue while Circular queue is not empty. 
}