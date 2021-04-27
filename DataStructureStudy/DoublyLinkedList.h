#include <stdlib.h>
#include "Element.h"

//Singly Linked List �� ���� element�� ���� ����� ������ ������ �־, �������� ��ȸ�� �ܹ������θ� �����ߴ�.
//����, � ������ ���� �������� ������ �ٽ� ���� ���� ���, ó������ �ٽ� ��ȸ�� �����Ͽ� �˾Ƴ��߸� �ߴ�.
//Doubly Linked List�� ���, ���� ��ũ �Ӹ� �ƴ϶� ���� ��ũ�� ���� ���� ���� ������ �����Ƿ� ����� ������ �����ϴ�.
//�ڵ��� ���⼺�� ���̱� ���� head ��忡 dummy ��带 �Ҵ�����.

typedef struct
{
	int length;  //������ ��� ������ ��Ÿ����. ���������� �ٲٸ� �ȵȴ�!
	Node_R* head;
}DoublyLinkedList;

void DListPrint(DoublyLinkedList* list);
void DListInsert(DoublyLinkedList* list, element elem);
void DListDelete(DoublyLinkedList* list)