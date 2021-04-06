#include <stdlib.h>
#include <stdio.h>
#include "Element.h"
// �迭 ����� ����Ʈ�� ������ �迭 ���̸� ������ �ǹǷ� Ȯ�强 �� ����/������ ��ȿ�����̴�.
// ����/ ���� ���� �迭��� ����Ʈ�� �ִ� �迭 ���� ��ŭ�� ������ �߰��� �����ؾ� �� ���� �ִ�
// ��ũ�� ����Ʈ�� �� ���, ���� ��� ��� �� ����� next �����Ͱ� ���� ����� next �����͸� ����Ű�� ����� �ȴ�.
// ���� �ڷ���� ���� ���� ����ϰ�, �޸��� ���� ���� ���� �����Ҵ��� Ȱ���� ����Ʈ�� ����Ѵ�.


//Linked List
// ��ũ�� ���� ������ ����
// 
//���� ������ ������ ������ �ٸ���.
//��ũ�� ����Ʈ�� ����� ��ġ�� �ݵ�� �������� Ȥ�� ������������ ������ ���̶�� ������ ����. �ּ��� �Ҵ��� Ư�� ��Ģ ������ ������ �� �ִ�.
//��, ���������� ���� ������������, ������ ���������� �ʴ´�.
//�ݸ� �������� �� ���� ���� ����� �ּҰ��� ������ �̸� �̿��� ����ų �� �ִ�.
//�̿� ����� ������ �����ϹǷ�, �������δ� ������ �����Ѵ�.
//1)singly linked list
// : �ڷᰡ �� �������θ� ����� ���
// : next�� ������, before �� ����.
typedef struct
{
	int length;
	Node_O* head; //1���� ���
	Node_O* tail; // insert �����, ��带 ��� ��ȸ�� �ʿ䰡 ������ ����.
				  // tail�� ������ ���� ����Ų��.
}SinglyLinkedList;

//��带 �̸� �ϳ� ����� �δ� �͵� ���� ������ �ȴ�.
//���� ��忡 ���̳�带 ������ �ʴ´ٰ� ��������.
//���� null �� ���� �ְ�, null�� �ƴ� ���� �ִ�.
//����尡 ���̳�尡 �ƴϹǷ�, �ڵ带 ������ ��, ��尡 null �� ��츦
//������ �����Ͽ� �����ؾ� �Ѵ�.
//��� ��尡 �����ϸ� �ݵ�� ù ������ head-> next �� �ǹǷ�, head �� ������� �ʾƵ� �Ǿ�
//�ڵ忡 ���� ���� ���⼺�� �پ��� �Ǿ� ������ ��������


void Init_SList(SinglyLinkedList* list);

void Insert_SList(SinglyLinkedList* list, element e);
int InsertAtIdx_SList(SinglyLinkedList* list, int index, element e);

element Delete_SList(SinglyLinkedList* list);
element DeleteAt_SList(SinglyLinkedList* list, int index);
int RemoveElement_SList(SinglyLinkedList* list, element data);

void Destruct_SList(SinglyLinkedList* list); //����Ʈ�� ��� ��Ҹ� ���� + ��嵵 ����

void Print_SList(SinglyLinkedList* list);
Node_O* Search_SList(SinglyLinkedList* list, element data); 

//����Ʈ�� �ʱ�ȭ�Ѵ�. ����, head, tail ���� �����Ѵ�.
void Init_SList(SinglyLinkedList* list)
{
	list->length = 0; //����Ʈ�� ���̸� 0���� ����
	list->head = NodeInit(0);//head�� ������ ���� ���. default �� �ǹ̷� 0�� �Ҵ�.
	list->tail = list->head; //���� �߰��� ��尡 �����Ƿ�, tail = head�� ����.
	//head�� ���� ��带 ����ϰ� �Ǿ� ���� destruct�� �����ϸ� head�� ��� �� �ʿ䰡 ���� �ȴ�.
}

//����Ʈ�� �� ���� element e �� �߰��Ѵ�.
void Insert_SList(SinglyLinkedList* list, element e)
{
	list->tail->next = NodeInit(e); // tail->next�� ��带 ���� ����.
	list->tail = list->tail->next;//tail->next�� ������ ���ο� ��带 �߰��߾���, �̰Ϳ��� tail�� �ű�� ����.
	//�������� �߰��ϴ� ������ ���, ���� ��带 ��� �� �ʿ䰡 �����Ƿ� �����ϴ�.
	list->length++; //���̸� 1 �ø���.
}

//����Ʈ �� index��° ��ġ�� element e�� �߰��Ѵ�.
//���� index�� list->length �� �ʰ��ϴ� ������ ���̶��, FALSE(0)�� ��ȯ�Ѵ�. ���� ��쵵 �ȵȴ�.
//�ƴ϶�� ���� �����ϰ�, TRUE(1)�� ��ȯ�Ѵ�.
//�⺻������ index�� �ش��ϴ� ��带 �տ������� ã�ƾ� �Ѵ�. O(N) �� ���⼺�� ���ϰ� �ȴ�.
//�� �ڿ� ���� �ְ� �ʹٸ� Insert_SList�� ����Ͻñ� �ٶ��ϴ�.
int InsertAtIdx_SList(SinglyLinkedList* list, int index, element e)
{
	if (index >= list->length || index < 0) // 
	{
		return 0; // FASLE�� �ǹ̷�, 0�� ��ȯ.
	}

	int innerIdx = 0;
	Node_O* target = list->head->next;//head-> next���� ����, while���� �������鼭 index�� �ش��ϴ� ���� ���ϰ� �ȴ�.
	Node_O* before = list->head;

	while (innerIdx != index)//index�� 0 <= index < length �� ���� ���� �ݵ�� ����.
	{
		before = target;
		target = target->next;
		innerIdx++;
	}

	before->next = NodeInit(e); //���ο� ��带 before ����, index ��ġ�� �����.
	before->next->next = target; // ���� ������� ����� next�� target ���� ���Ѵ�.
	list->length++;
	return 1;
}

//������ pop�� ���� ���. tail�� ���� �����ϰ�, �ش� ���� ��ȯ�Ѵ�.
//�ܹ��� ����Ʈ��, �ƹ��� tail�̾ ���� ���� ���� �ٷ� ������ �� ���� ������ �ε������� ã�ư��� �Ѵ�.
//delete �Լ� ������ ���ɻ� ������ ���� ����.
//���������� DeleteAt_SList�� �����ȴ�.
element Delete_SList(SinglyLinkedList* list)
{
	return DeleteAt_SList(list, list->length - 1);
}

//index ��ġ�� ��带 �����ϰ�, �ش� ����� ���� ��ȯ�Ѵ�.
element DeleteAt_SList(SinglyLinkedList* list, int index)
{
	if (index > list->length || index < 0) // 
	{
		printf("�ش� �ε����� ���� ���� �����ϴ�.\n");
		return 0; // FASLE�� �ǹ̷�, 0�� ��ȯ.
	}

	int innerIdx = 0;
	Node_O* target = list->head->next;//head-> next���� ����, while���� �������鼭 index�� �ش��ϴ� ���� ���ϰ� �ȴ�.
	Node_O* before = list->head;

	while (innerIdx != index)//index�� 0 <= index < length �� ���� ���� �ݵ�� ����.
	{
		before = target;
		target = target->next;
		innerIdx++;
	}
	element returnValue = target->item;
	before->next = target->next;//before�� ���� ���� target�� ���� ������ �����Ѵ�.
	list->length--;//������ ������ �����Ѵ�.
	free(target);//target�� �����Ѵ�.
	return returnValue;// ���� ��ȯ�Ѵ�.
}


//item�� �����ϰ�, index�� ��ȯ�Ѵ�. item�� �����ϴ� ��尡 �������� ������, -1 �� ��ȯ�Ѵ�.
int RemoveElement_SList(SinglyLinkedList* list, element data)
{
	Node_O* target = list->head->next;
	Node_O* before = list->head;
	int idx = 0;
	while (target != NULL)
	{
		if (target->item == data)
		{
			before->next = target->next;
			free(target);
			list->length--;
			return idx;
		}
		before = target;
		target = target->next;
		idx++;
	}
	return -1;
}



//���� ��ҵ��� ��� ����Ѵ�
void Print_SList(SinglyLinkedList* list)
{
	Node_O* node = list->head;

	while (node->next != NULL) // ó�� ���� head, node->next != NULL ���� ���� �� ��, �Լ��� ����Ѵ�.
	{
		node = node->next;
		printf("%d ", node->item);
	}
	putchar('\n');
}

//���� data�� ���ϰ� �ִ� node�� �߰��ϸ� �ش� ��带 ��ȯ�մϴ�.
//�ƴ� ���, NULL�� ��ȯ�մϴ�.
//���� ��尡 data�� ���� �����ٸ�, �ε����� ���� ���� ��带 ��ȯ�մϴ�.
//�� ó������ ����Ž���� �����մϴ�.
Node_O* Search_SList(SinglyLinkedList* list, element data)
{
	Node_O* node = list->head;

	while (node->next != NULL)
	{
		node = node->next;
		if (node->item == data)
		{
			return node; // ���ǿ� �´� ��� �ش� ��带 ��ȯ�մϴ�.
		}
	}
	return NULL;//�� ���ǿ��� �ɸ��� �ʾҴٴ� �ǹ̴� ����Ʈ ���� ���� ���ٴ� �ǹ��̹Ƿ�, NULL�� ��ȯ�մϴ�.
}

//head�� dummy ����̰�, malloc���� �����Ҵ�Ǿ��־�, heap�� ���̰� �ȴ�.
//���� ���̻� ����Ʈ�� ������� �ʴ� ���, head�� ���� �� �ʿ䰡 ����.
//head���� �����Ͽ� ����Ʈ �� ��� ��带 free �Լ��� ���� �����Ѵ�.
void Destruct_SList(SinglyLinkedList* list)
{
	Node_O* delNode = list->head;
	Node_O* temp; // ���ο����� ���ȴ�

	while (delNode != NULL)
	{
		temp = delNode->next;
		free(delNode);
		delNode = temp;
	}

	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	//Ȥ�ø� ������ ����Ͽ� head�� tail�� NULL�� �ʱ�ȭ�Ѵ�.
	printf("Destruct\n");
}