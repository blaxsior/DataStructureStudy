#include "Queue.h"
#include <stdio.h>
typedef  Node_R* BST_pointer;
// Binary Search Tree
// 노드 관계 상 제약조건을 걸어, 자료의 탐색을 효율적으로 할 수 있다.
// 탐색은 O(log n) 이다

// 모든 원소는 유일한 키(key)를 가진다.
// 왼쪽 서브트리 키 < 루트의 키 < 오른쪽 서브트리 키
// 왼쪽과 오른쪽 서브트리도 이진탐색트리에 속한다.

//
//
//			20
//	10				22
//9		11				25

//이런 식으로 구성하면, 탐색하려는 key와 노드의 key를 비교하여 왼쪽 혹은 오른쪽으로 탐색한다.

// 11을 찾는 경우? -> 10으로 이동-> 11로 이동
// 21을 찾는 경우? -> 오른쪽으로 이동(20보다 크다) -> 왼쪽으로 이동(22보다 작다)

BST_pointer search(BST_pointer node, int key)
{
	while (node)
	{
		if (key == node->item) return node;
		if (key < node->item)
			node =  node->Llink;
		else
			node =  node->Rlink;
	}
	return NULL;
}

BST_pointer rec_search(BST_pointer node, int key)
{
	if (node == NULL) return NULL;//NULL돌려줌
	
	if (node->item == key) return node;
	if (key < node->item)
		return rec_search(node->Llink, key);
	else
		return rec_search(node->Rlink, key);

}

//높이 h 일 때, 이진 탐색 트리에 걸리는 시간 : O(h) = O(log n) (average)

BST_pointer insert_node(BST_pointer node, int key)
{
	if (node == NULL) return RNodeInit(key); // NULL이면 여기에 넣으면 된다!

	if (key > node->item) node->Rlink =  insert_node(node->Rlink, key);
	else if (key < node->item) node->Llink =  insert_node(node->Llink, key);
	// key == node->item인 경우, 값이 동일하므로 아무런 행동도 하지 않고 그냥 돌려준다.
	return node;
}
//search와 방식이 거의 유사하나, null이 나오면 여기다가 node를 하나 생성해 넣는다.

//실제로 삭제
BST_pointer delete_node(BST_pointer node, int key)
{
	if (node == NULL) return node;
	//NULL이 아닌 경우
	if (node->item > key)	node->Llink = delete_node(node->Llink, key);
	else if (node->item < key)	node->Rlink = delete_node(node->Rlink, key);
	else //
	{
		BST_pointer temp = node->Llink;

		if (node->Llink == NULL && node->Rlink == NULL)
		{
			free(node);
			return NULL;
		}
		if (node->Llink == NULL)
		{
			temp = node->Rlink;
			free(node);
			return temp;
		}
		if (node->Rlink == NULL)
		{
			temp = node->Llink;
			free(node);
			return temp;
		}
		
		//둘중 하나가 그냥 링크면, 삭제 할 필요도 없음.
		while (temp->Rlink != NULL) //왼쪽에서 가장 큰놈을 선택한다
		{
			temp = temp->Rlink;
		}
		node->item = temp->item; //node와 temp를 교체한다.
		node->Llink = delete_node(node->Llink, temp->item); //
		//원래 노드에는 노드의 좌측 child에서 가장 큰 노드인 temp의 item이 들어갔고,
		//삭제해야 할 노드는 temp가 된다.
		//이때, temp를 반환하기 전에 temp의 left 노드와 temp의 parent의 노드를 right노드로 연결해야 되는데,
		//이는 동일한 delete_node를 이용해서 반환한다.
	}
	return node;
}
//왼쪽에서 가장 큰 것 혹은 오른쪽에서 가장 작은 것과 삭제할 값을 교체한 다음, 
//왼쪽의 경우, 삭제되는 노드의 왼쪽 child를 삭제되는 노드의 부모 노드의 오른쪽 노드와 연결한다
//오른쪽의 경우는 이에 반대된다.



//n개의 원소를 가진 이진트리의 높이 h ?
//평균 : h = O(log n)
//worst case : h = O(n) -> 왼쪽 오른쪽 중 한 방향으로만 계속 이어지는 경우

//search, insert, delete, deletemin ->
//O(h)	=O(log n)	-> average 
//		=O(n)		-> worst case

//balanced tree들 -> worst case에서도 O(log n)의 복잡도가 보장되는 트리들.
//한쪽으로만 치우치게 만들지 않고 양쪽 노드에 대하여 균형잡히게 만든다.
//ex AVL 트리, 2-3 트리. red-black 트리

void level_orderTraverseBST(BST_pointer ptr)
{
	Queue queue;
	QueueInit(&queue);
	AddQueue(&queue, ptr);
	BST_pointer temp;
	while (!isQueueEmpty(&queue))
	{
		temp = DelQueue(&queue);
		printf("%d ", temp->item);
		if (temp->Llink) AddQueue(&queue, temp->Llink);
		if (temp->Rlink) AddQueue(&queue, temp->Rlink);
	}
}