#include "Queue.h"

//Tree

//1개 이상의 노드의 유한 집합.
//루트 노드가 하나, 나머지는 분리집합으로 구성되며, 각각도 하나의 트리(서브트리)에 속한다
//그래프와는 달리 사이클이 없다,

//차수(degree) : sub tree 의 개수
//루트(root) : 최상위에 있는 노드.
//리프(leaf, terminal) : 차수가 0 인 노드
//인터널(internal) : 리프 노드가 아닌 노드.

//부모(parent) : D의 부모 노드
//자식(children) : D를 부모 노드로 하는 노드들
//조상(ancestor) : D의 부모 노드를 계속 거슬러 올라가는 동안 있는 노드들.
//자손(descendants) : D 의 자손들.

//레벨(level) : parent level + 1 (루트의 level 을 1로 정한다)
//높이(height) : 트리에 속한 노드의 최대 레벨

//표현 방식
// 
//List 표현
//하나의 노드에 여러개의 링크를 달아서 사용한다.
//사실 실제로 적용 될 링크의 개수를 알 수 없어서 효율적이지 못하다.

//Left-child-right-sibling 표현

//Binary Tree 방식
//Child의 개수를 2개로 정해놓고 수행.


//노드들의 유한집합으로, 공집합이거나 루트와 왼쪽 서브트리, 오른쪽 서브트리 두개의 분리된 이진트리로 구성된다.
//모든 노드는 최대 2개의 자식 노드를 가질 수 있다.

//성질

//트리 안의 노드의 개수를 n, 트리의 높이를 h 라 하면, 
//	1) 간선의 개수 = n - 1 (모든 노드는 parent를 가지고 있고, root 만 없다.)
//	2) 높이 h 인 최소 노드 수 : n = h
//	3) 높이 h 인 최대 노드 수 : 2^h - 1

//	4) 노드 개수가 n 인 최대 높이 : h = n (자식1개만 가지고 계속 연결)
//	5) 노드 개수가 n 인 최소 높이 : n < 2^h - 1, log2 (n+1) < h, h = floor(log2 (n+1))

//Binary tree 는 방식에 따라 같은 개수의 노드를 가져도 다른 모습을 지니게 된다.

//포화이진트리(full BT) : binary tree의 높이가 h 일때, 해당 높이에 대해 모든 노드가 꽉 찬 상태
//n = 2^h - 1 

//완전이진트리(complete BT) : binary tree의 높이가 h 일때, level h - 1 까지는 노드가 꽉 차있고, level h 에 대해서는 왼쪽부터 순서대로 차있는 경우
// 2^(h-1) - 1 < n < 2^h - 1

// Array 방식으로 full BT 표현하기
// full binary tree 에 대해서는 노드마다 숫자를 할당할 수 있다. 왼쪽부터 값을 센다.
//parent(i) : i/2
//left_child(i) = 2i
//right_child(i) = 2i + 1

//	장점 : 인덱스 기반으로 연산을 수행하여, 연산이 빠르다
//	단점 : 데이터의 양이 작다면, 비효율적으로 메모리를 사용하게 된다.
//			삽입 및 삭제가 어렵다.(데이터를 이동시키는 과정이 매우 어려워진다)
//			complete BT 형태만 사용한다(한 줄로 늘어서는 방식은 사용하지 않는다.)


//idx를 1부터 시작한다는 가정하에 parent나 left_child 가 저렇게 나오는 것이다
//0부터 시작하면 다른 값을 가지게 된다.
//

#define MAX_SIZE 7 // 2 ^ 3 - 1 = 7 로, 높이가 3 인 full BT(포화 이진 트리) 를 의미한다.

//index는 루트가 0 으로 시작한다.
typedef char item;

item fullBT[MAX_SIZE];

int getParent(int idx)
{
	return  (idx - 1) / 2;
}
//1 과 2 가 0 이 되려면, 이렇게 구성해야 한다.
int getLeftChild(int idx)
{
	return 2 * idx + 1;
}
// 1 의 자식 노드는 3, 4 가 있다.
// 1 이 3 이 되려면 2 * 1 + 1 이 필요하다.

int getRightChild(int idx)
{
	return 2 * idx + 2;
}

//linked 방식으로 트리를 구현할 수도 있다.



typedef struct btNode
{
	struct btNode* left_child;
	struct btNode* right_child;
	item data;
}BTNode;

//기본적으로 BTNode 의 left / right는 처음에 NULL로 초기화 해야한다.

typedef BTNode* tree_pointer;

//BT traversal
//순회 방식은 3가지가 있음

//중위(inorder) : LVR(왼쪽부터 방문하고 오른쪽을 방문한다)
//전위(preorder) : VLR(루트를 먼저 보고, 왼쪽 오른쪽)
//후위(postorder) : LRV(왼쪽 오른쪽 보고, 마지막에 루트)
// 재귀를 사용한다. 개념적으로 스택의 개념을 사용하는 것과 같다.

void inorderTraverse(tree_pointer ptr)
{
	if (ptr)// 종료 조건? 자기 자신이 NULL 이면 종료
	{
		inorderTraverse(ptr->left_child);
		printf("%d", ptr->data);
		inorderTraverse(ptr->right_child);
	}
}
//LVR
// infix 방식 방문
//	A/B*C+D/E


void preorderTraverse(tree_pointer ptr)
{
	if (ptr)
	{
		printf("%d", ptr->data);
		preorderTraverse(ptr->left_child);
		preorderTraverse(ptr->right_child);
	}
}
//VLR
// prefix 방식 방문
//	+*/ABC/DE


void postorderTraverse(tree_pointer ptr)
{
	if (ptr)
	{
		postorderTraverse(ptr->left_child);
		postorderTraverse(ptr->right_child);
		printf("%d", ptr->data);
	}
}
//LRV
//	postfix 방식 방문
//	AB/C*DE/+

//레벨 순서 순회
//Queue 의 개념을 사용한다
//맨 처음에 자신, left / right child 를 넣고 과정을 반복한다.
void level_orderTraverse(tree_pointer ptr)
{
	Queue queue;
	AddQueue(&queue, ptr);
	tree_pointer temp;
	while (!isQueueEmpty(&queue))
	{
		temp = DelQueue(&queue);
		printf("%d", temp->data);
		if (temp->left_child) AddQueue(&queue, temp->left_child);
		if (temp->right_child) AddQueue(&queue, temp->right_child);
	}
}

int bt_equal(tree_pointer p1, tree_pointer p2)
{
	if (!p1 && !p2) return 1; // 둘다 null
	else if (p1 && p2) //둘다 null 아님
	{
		if ((p1->data == p2->data) && bt_equal(p1->left_child, p2->left_child) && bt_equal(p1->right_child, p2->right_child))
			return 1;
		else
			return 0;
	}
	else
		return 0;	//둘중 하나만 null -> 반드시 다른 트리

}