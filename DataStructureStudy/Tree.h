#include "Queue.h"

//Tree

//1�� �̻��� ����� ���� ����.
//��Ʈ ��尡 �ϳ�, �������� �и��������� �����Ǹ�, ������ �ϳ��� Ʈ��(����Ʈ��)�� ���Ѵ�
//�׷����ʹ� �޸� ����Ŭ�� ����,

//����(degree) : sub tree �� ����
//��Ʈ(root) : �ֻ����� �ִ� ���.
//����(leaf, terminal) : ������ 0 �� ���
//���ͳ�(internal) : ���� ��尡 �ƴ� ���.

//�θ�(parent) : D�� �θ� ���
//�ڽ�(children) : D�� �θ� ���� �ϴ� ����
//����(ancestor) : D�� �θ� ��带 ��� �Ž��� �ö󰡴� ���� �ִ� ����.
//�ڼ�(descendants) : D �� �ڼյ�.

//����(level) : parent level + 1 (��Ʈ�� level �� 1�� ���Ѵ�)
//����(height) : Ʈ���� ���� ����� �ִ� ����

//ǥ�� ���
// 
//List ǥ��
//�ϳ��� ��忡 �������� ��ũ�� �޾Ƽ� ����Ѵ�.
//��� ������ ���� �� ��ũ�� ������ �� �� ��� ȿ�������� ���ϴ�.

//Left-child-right-sibling ǥ��

//Binary Tree ���
//Child�� ������ 2���� ���س��� ����.


//������ ������������, �������̰ų� ��Ʈ�� ���� ����Ʈ��, ������ ����Ʈ�� �ΰ��� �и��� ����Ʈ���� �����ȴ�.
//��� ���� �ִ� 2���� �ڽ� ��带 ���� �� �ִ�.

//����

//Ʈ�� ���� ����� ������ n, Ʈ���� ���̸� h �� �ϸ�, 
//	1) ������ ���� = n - 1 (��� ���� parent�� ������ �ְ�, root �� ����.)
//	2) ���� h �� �ּ� ��� �� : n = h
//	3) ���� h �� �ִ� ��� �� : 2^h - 1

//	4) ��� ������ n �� �ִ� ���� : h = n (�ڽ�1���� ������ ��� ����)
//	5) ��� ������ n �� �ּ� ���� : n < 2^h - 1, log2 (n+1) < h, h = floor(log2 (n+1))

//Binary tree �� ��Ŀ� ���� ���� ������ ��带 ������ �ٸ� ����� ���ϰ� �ȴ�.

//��ȭ����Ʈ��(full BT) : binary tree�� ���̰� h �϶�, �ش� ���̿� ���� ��� ��尡 �� �� ����
//n = 2^h - 1 

//��������Ʈ��(complete BT) : binary tree�� ���̰� h �϶�, level h - 1 ������ ��尡 �� ���ְ�, level h �� ���ؼ��� ���ʺ��� ������� ���ִ� ���
// 2^(h-1) - 1 < n < 2^h - 1

// Array ������� full BT ǥ���ϱ�
// full binary tree �� ���ؼ��� ��帶�� ���ڸ� �Ҵ��� �� �ִ�. ���ʺ��� ���� ����.
//parent(i) : i/2
//left_child(i) = 2i
//right_child(i) = 2i + 1

//	���� : �ε��� ������� ������ �����Ͽ�, ������ ������
//	���� : �������� ���� �۴ٸ�, ��ȿ�������� �޸𸮸� ����ϰ� �ȴ�.
//			���� �� ������ ��ƴ�.(�����͸� �̵���Ű�� ������ �ſ� ���������)
//			complete BT ���¸� ����Ѵ�(�� �ٷ� �þ�� ����� ������� �ʴ´�.)


//idx�� 1���� �����Ѵٴ� �����Ͽ� parent�� left_child �� ������ ������ ���̴�
//0���� �����ϸ� �ٸ� ���� ������ �ȴ�.
//

#define MAX_SIZE 7 // 2 ^ 3 - 1 = 7 ��, ���̰� 3 �� full BT(��ȭ ���� Ʈ��) �� �ǹ��Ѵ�.

//index�� ��Ʈ�� 0 ���� �����Ѵ�.
typedef char item;

item fullBT[MAX_SIZE];

int getParent(int idx)
{
	return  (idx - 1) / 2;
}
//1 �� 2 �� 0 �� �Ƿ���, �̷��� �����ؾ� �Ѵ�.
int getLeftChild(int idx)
{
	return 2 * idx + 1;
}
// 1 �� �ڽ� ���� 3, 4 �� �ִ�.
// 1 �� 3 �� �Ƿ��� 2 * 1 + 1 �� �ʿ��ϴ�.

int getRightChild(int idx)
{
	return 2 * idx + 2;
}

//linked ������� Ʈ���� ������ ���� �ִ�.



typedef struct btNode
{
	struct btNode* left_child;
	struct btNode* right_child;
	item data;
}BTNode;

//�⺻������ BTNode �� left / right�� ó���� NULL�� �ʱ�ȭ �ؾ��Ѵ�.

typedef BTNode* tree_pointer;

//BT traversal
//��ȸ ����� 3������ ����

//����(inorder) : LVR(���ʺ��� �湮�ϰ� �������� �湮�Ѵ�)
//����(preorder) : VLR(��Ʈ�� ���� ����, ���� ������)
//����(postorder) : LRV(���� ������ ����, �������� ��Ʈ)
// ��͸� ����Ѵ�. ���������� ������ ������ ����ϴ� �Ͱ� ����.

void inorderTraverse(tree_pointer ptr)
{
	if (ptr)// ���� ����? �ڱ� �ڽ��� NULL �̸� ����
	{
		inorderTraverse(ptr->left_child);
		printf("%d", ptr->data);
		inorderTraverse(ptr->right_child);
	}
}
//LVR
// infix ��� �湮
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
// prefix ��� �湮
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
//	postfix ��� �湮
//	AB/C*DE/+

//���� ���� ��ȸ
//Queue �� ������ ����Ѵ�
//�� ó���� �ڽ�, left / right child �� �ְ� ������ �ݺ��Ѵ�.
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
	if (!p1 && !p2) return 1; // �Ѵ� null
	else if (p1 && p2) //�Ѵ� null �ƴ�
	{
		if ((p1->data == p2->data) && bt_equal(p1->left_child, p2->left_child) && bt_equal(p1->right_child, p2->right_child))
			return 1;
		else
			return 0;
	}
	else
		return 0;	//���� �ϳ��� null -> �ݵ�� �ٸ� Ʈ��

}