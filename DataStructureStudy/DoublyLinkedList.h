#include <stdlib.h>
#include "Element.h"

//Singly Linked List 의 노드는 element와 다음 노드의 정보를 가지고 있어서, 데이터의 순회가 단방향으로만 가능했다.
//따라서, 어떤 순간에 이전 데이터의 정보를 다시 보고 싶은 경우, 처음부터 다시 순회를 시작하여 알아내야만 했다.
//Doubly Linked List의 경우, 다음 링크 뿐만 아니라 이전 링크에 대한 정보 역시 가지고 있으므로 양방향 접근이 가능하다.
//코드의 복잡성을 줄이기 위해 head 노드에 dummy 노드를 할당하자.

typedef struct
{
	int length;  //내부의 노드 개수를 나타낸다. 개별적으로 바꾸면 안된다!
	Node_R* head;
}DoublyLinkedList;

void DListPrint(DoublyLinkedList* list);
void DListInsert(DoublyLinkedList* list, element elem);
void DListDelete(DoublyLinkedList* list)