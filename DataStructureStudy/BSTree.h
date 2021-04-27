#include "Queue.h"
#include <stdio.h>
typedef  Node_R* BST_pointer;
// Binary Search Tree
// ��� ���� �� ���������� �ɾ�, �ڷ��� Ž���� ȿ�������� �� �� �ִ�.
// Ž���� O(log n) �̴�

// ��� ���Ҵ� ������ Ű(key)�� ������.
// ���� ����Ʈ�� Ű < ��Ʈ�� Ű < ������ ����Ʈ�� Ű
// ���ʰ� ������ ����Ʈ���� ����Ž��Ʈ���� ���Ѵ�.

//
//
//			20
//	10				22
//9		11				25

//�̷� ������ �����ϸ�, Ž���Ϸ��� key�� ����� key�� ���Ͽ� ���� Ȥ�� ���������� Ž���Ѵ�.

// 11�� ã�� ���? -> 10���� �̵�-> 11�� �̵�
// 21�� ã�� ���? -> ���������� �̵�(20���� ũ��) -> �������� �̵�(22���� �۴�)

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
	if (node == NULL) return NULL;//NULL������
	
	if (node->item == key) return node;
	if (key < node->item)
		return rec_search(node->Llink, key);
	else
		return rec_search(node->Rlink, key);

}

//���� h �� ��, ���� Ž�� Ʈ���� �ɸ��� �ð� : O(h) = O(log n) (average)

BST_pointer insert_node(BST_pointer node, int key)
{
	if (node == NULL) return RNodeInit(key); // NULL�̸� ���⿡ ������ �ȴ�!

	if (key > node->item) node->Rlink =  insert_node(node->Rlink, key);
	else if (key < node->item) node->Llink =  insert_node(node->Llink, key);
	// key == node->item�� ���, ���� �����ϹǷ� �ƹ��� �ൿ�� ���� �ʰ� �׳� �����ش�.
	return node;
}
//search�� ����� ���� �����ϳ�, null�� ������ ����ٰ� node�� �ϳ� ������ �ִ´�.

//������ ����
BST_pointer delete_node(BST_pointer node, int key)
{
	if (node == NULL) return node;
	//NULL�� �ƴ� ���
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
		
		//���� �ϳ��� �׳� ��ũ��, ���� �� �ʿ䵵 ����.
		while (temp->Rlink != NULL) //���ʿ��� ���� ū���� �����Ѵ�
		{
			temp = temp->Rlink;
		}
		node->item = temp->item; //node�� temp�� ��ü�Ѵ�.
		node->Llink = delete_node(node->Llink, temp->item); //
		//���� ��忡�� ����� ���� child���� ���� ū ����� temp�� item�� ����,
		//�����ؾ� �� ���� temp�� �ȴ�.
		//�̶�, temp�� ��ȯ�ϱ� ���� temp�� left ���� temp�� parent�� ��带 right���� �����ؾ� �Ǵµ�,
		//�̴� ������ delete_node�� �̿��ؼ� ��ȯ�Ѵ�.
	}
	return node;
}
//���ʿ��� ���� ū �� Ȥ�� �����ʿ��� ���� ���� �Ͱ� ������ ���� ��ü�� ����, 
//������ ���, �����Ǵ� ����� ���� child�� �����Ǵ� ����� �θ� ����� ������ ���� �����Ѵ�
//�������� ���� �̿� �ݴ�ȴ�.



//n���� ���Ҹ� ���� ����Ʈ���� ���� h ?
//��� : h = O(log n)
//worst case : h = O(n) -> ���� ������ �� �� �������θ� ��� �̾����� ���

//search, insert, delete, deletemin ->
//O(h)	=O(log n)	-> average 
//		=O(n)		-> worst case

//balanced tree�� -> worst case������ O(log n)�� ���⵵�� ����Ǵ� Ʈ����.
//�������θ� ġ��ġ�� ������ �ʰ� ���� ��忡 ���Ͽ� ���������� �����.
//ex AVL Ʈ��, 2-3 Ʈ��. red-black Ʈ��

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