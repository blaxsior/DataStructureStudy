#include <stdlib.h>
#include <stdio.h>
#include "Element.h"
// 배열 기반의 리스트는 고정된 배열 길이를 가지게 되므로 확장성 및 삽입/삭제가 비효율적이다.
// 삽입/ 삭제 마다 배열기반 리스트는 최대 배열 길이 만큼의 연산을 추가로 수행해야 할 수도 있다
// 링크드 리스트는 위 경우, 삭제 대상 노드 전 노드의 next 포인터가 다음 노드의 next 포인터를 가리키게 만들면 된다.
// 많은 자료들을 가질 것을 대비하고, 메모리의 낭비를 막기 위해 동적할당을 활용한 리스트를 사용한다.


//Linked List
// 링크를 가진 노드들의 순열
// 
//논리적 순서와 물리적 순서가 다르다.
//링크드 리스트의 노드의 위치가 반드시 오름차순 혹은 내림차순으로 존재할 것이라는 보장은 없다. 주소의 할당은 특정 규칙 내에서 랜덤일 수 있다.
//즉, 물리적으로 값이 연속적이지도, 순서가 존재하지도 않는다.
//반면 논리적으로 전 노드는 다음 노드의 주소값을 가지고 이를 이용해 가리킬 수 있다.
//이에 기반한 순서는 존재하므로, 논리적으로는 순서가 존재한다.
//1)singly linked list
// : 자료가 한 방향으로만 연결된 경우
// : next는 있으나, before 은 없다.
typedef struct
{
	int length;
	Node_O* head; //1방향 노드
	Node_O* tail; // insert 수행시, 노드를 모두 순회할 필요가 없도록 설정.
				  // tail은 마지막 값을 가리킨다.
}SinglyLinkedList;

//헤드를 미리 하나 만들어 두는 것도 좋은 전략이 된다.
//만약 헤드에 더미노드를 만들지 않는다고 가정하자.
//헤드는 null 일 수도 있고, null이 아닐 수도 있다.
//헤드노드가 더미노드가 아니므로, 코드를 구현할 때, 헤드가 null 인 경우를
//별개로 구분하여 구현해야 한다.
//헤드 노드가 존재하면 반드시 첫 시작은 head-> next 가 되므로, head 를 고려하지 않아도 되어
//코드에 헤드로 인한 복잡성이 줄어들게 되어 구현이 쉬워진다


void Init_SList(SinglyLinkedList* list);

void Insert_SList(SinglyLinkedList* list, element e);
int InsertAtIdx_SList(SinglyLinkedList* list, int index, element e);

element Delete_SList(SinglyLinkedList* list);
element DeleteAt_SList(SinglyLinkedList* list, int index);
int RemoveElement_SList(SinglyLinkedList* list, element data);

void Destruct_SList(SinglyLinkedList* list); //리스트내 모든 요소를 제거 + 헤드도 제거

void Print_SList(SinglyLinkedList* list);
Node_O* Search_SList(SinglyLinkedList* list, element data); 

//리스트를 초기화한다. 길이, head, tail 등을 설정한다.
void Init_SList(SinglyLinkedList* list)
{
	list->length = 0; //리스트의 길이를 0으로 설정
	list->head = NodeInit(0);//head는 어차피 더미 노드. default 의 의미로 0을 할당.
	list->tail = list->head; //새로 추가된 노드가 없으므로, tail = head로 설정.
	//head에 더미 노드를 사용하게 되어 이후 destruct를 제외하면 head를 고려 할 필요가 없게 된다.
}

//리스트의 맨 끝에 element e 를 추가한다.
void Insert_SList(SinglyLinkedList* list, element e)
{
	list->tail->next = NodeInit(e); // tail->next에 노드를 새로 생성.
	list->tail = list->tail->next;//tail->next에 이전에 새로운 노드를 추가했었고, 이것에게 tail을 옮기는 과정.
	//마지막에 추가하는 과정의 경우, 다음 노드를 고려 할 필요가 없으므로 간단하다.
	list->length++; //길이를 1 늘린다.
}

//리스트 내 index번째 위치에 element e를 추가한다.
//만약 index가 list->length 를 초과하는 범위의 값이라면, FALSE(0)을 반환한다. 같은 경우도 안된다.
//아니라면 값을 저장하고, TRUE(1)을 반환한다.
//기본적으로 index에 해당하는 노드를 앞에서부터 찾아야 한다. O(N) 의 복잡성을 지니게 된다.
//맨 뒤에 값을 넣고 싶다면 Insert_SList를 사용하시길 바랍니다.
int InsertAtIdx_SList(SinglyLinkedList* list, int index, element e)
{
	if (index >= list->length || index < 0) // 
	{
		return 0; // FASLE의 의미로, 0을 반환.
	}

	int innerIdx = 0;
	Node_O* target = list->head->next;//head-> next부터 시작, while문을 돌려가면서 index에 해당하는 값을 지니게 된다.
	Node_O* before = list->head;

	while (innerIdx != index)//index는 0 <= index < length 의 범위 내에 반드시 존재.
	{
		before = target;
		target = target->next;
		innerIdx++;
	}

	before->next = NodeInit(e); //새로운 노드를 before 다음, index 위치로 만든다.
	before->next->next = target; // 새로 만들어진 노드의 next를 target 으로 정한다.
	list->length++;
	return 1;
}

//스택의 pop과 같은 방식. tail의 값을 제거하고, 해당 값을 반환한다.
//단방향 리스트라, 아무리 tail이어도 이전 값에 대해 바로 접근할 수 없어 마지막 인덱스까지 찾아가야 한다.
//delete 함수 내에서 성능상 유리한 점은 없다.
//내부적으로 DeleteAt_SList로 구현된다.
element Delete_SList(SinglyLinkedList* list)
{
	return DeleteAt_SList(list, list->length - 1);
}

//index 위치의 노드를 제거하고, 해당 노드의 값을 반환한다.
element DeleteAt_SList(SinglyLinkedList* list, int index)
{
	if (index > list->length || index < 0) // 
	{
		printf("해당 인덱스를 가진 노드는 없습니다.\n");
		return 0; // FASLE의 의미로, 0을 반환.
	}

	int innerIdx = 0;
	Node_O* target = list->head->next;//head-> next부터 시작, while문을 돌려가면서 index에 해당하는 값을 지니게 된다.
	Node_O* before = list->head;

	while (innerIdx != index)//index는 0 <= index < length 의 범위 내에 반드시 존재.
	{
		before = target;
		target = target->next;
		innerIdx++;
	}
	element returnValue = target->item;
	before->next = target->next;//before의 다음 값을 target의 다음 값으로 설정한다.
	list->length--;//원소의 개수가 감소한다.
	free(target);//target을 제거한다.
	return returnValue;// 값을 반환한다.
}


//item을 제거하고, index를 반환한다. item에 대응하는 노드가 존재하지 않으면, -1 을 반환한다.
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



//내부 요소들을 모두 출력한다
void Print_SList(SinglyLinkedList* list)
{
	Node_O* node = list->head;

	while (node->next != NULL) // 처음 노드는 head, node->next != NULL 임을 검증 한 후, 함수를 출력한다.
	{
		node = node->next;
		printf("%d ", node->item);
	}
	putchar('\n');
}

//만약 data를 지니고 있는 node를 발견하면 해당 노드를 반환합니다.
//아닌 경우, NULL을 반환합니다.
//여러 노드가 data의 값을 가진다면, 인덱스가 가장 빠른 노드를 반환합니다.
//맨 처음부터 순차탐색을 실행합니다.
Node_O* Search_SList(SinglyLinkedList* list, element data)
{
	Node_O* node = list->head;

	while (node->next != NULL)
	{
		node = node->next;
		if (node->item == data)
		{
			return node; // 조건에 맞는 경우 해당 노드를 반환합니다.
		}
	}
	return NULL;//위 조건에서 걸리지 않았다는 의미는 리스트 내에 값이 없다는 의미이므로, NULL을 반환합니다.
}

//head는 dummy 노드이고, malloc으로 동적할당되어있어, heap에 쌓이게 된다.
//따라서 더이상 리스트를 사용하지 않는 경우, head를 남겨 둘 필요가 없다.
//head부터 시작하여 리스트 내 모든 노드를 free 함수를 통해 제거한다.
void Destruct_SList(SinglyLinkedList* list)
{
	Node_O* delNode = list->head;
	Node_O* temp; // 내부에서만 사용된다

	while (delNode != NULL)
	{
		temp = delNode->next;
		free(delNode);
		delNode = temp;
	}

	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	//혹시모를 오류에 대비하여 head와 tail을 NULL로 초기화한다.
	printf("Destruct\n");
}