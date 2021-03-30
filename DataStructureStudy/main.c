#include <stdio.h>
#include "SinglyLinkedList.h"
#pragma warning(disable:4996)

void printTF(int boolVal)
{
	printf("%s\n", boolVal ? "TRUE" : "FALSE");
}

int main()
{
	SinglyLinkedList list1;
	Init_SList(&list1);
	int boolval = InsertAtIdx_SList(&list1, 0, 3);
	printTF(boolval);

	Insert_SList(&list1, 1);
	Insert_SList(&list1, 2);
	Insert_SList(&list1, 3);
	Insert_SList(&list1, 4);
	Insert_SList(&list1, 5);

	printf("length : %d\n", list1.length);
	
	Print_SList(&list1);
	printf("%d %d\n", list1.head->next->item, list1.tail->item);

	printTF(InsertAtIdx_SList(&list1, 5, 6));//index는 현재 0 ~ 4 까지만 유효
	printTF(InsertAtIdx_SList(&list1, 4, 6));//유효 범위에 존재

	Print_SList(&list1);
	printf("%d %d\n", list1.head->next->item, list1.tail->item);
	//여전히 값이 잘 유지된다.

	Node_O* node = Search_SList(&list1, 7);
	if (node == NULL)
	{
		printf("NULL value\n");
	}

	node = Search_SList(&list1, 3);
	if (node == NULL)
	{
		printf("NULL value\n");
	}
	else
	{
		printf("Found Value : %d\n", node->item);
	}

	int x = DeleteAt_SList(&list1, 3);
	
	printf("Deleted value :%d\n", x);
	printf("length : %d\n", list1.length);
	Print_SList(&list1);


	printf("%d\n", Delete_SList(&list1));
	printf("length : %d\n", list1.length);
	Print_SList(&list1);

	printf("delete 13 index : %d\n", RemoveElement_SList(&list1, 13));// -1 을 반환한다
	printf("delete 6 index : %d\n", RemoveElement_SList(&list1, 6));// index 0 이 반환될 것이다.

	printf("length : %d\n", list1.length);
	Print_SList(&list1);

	Destruct_SList(&list1);
}