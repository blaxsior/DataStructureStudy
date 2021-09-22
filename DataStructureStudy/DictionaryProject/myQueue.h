#include <stdlib.h>
#include <stdio.h>

//�յڷ� �ܾ� 3���� ����ϱ� ���� �������.
//computer-computer-computer ���� ���ڿ��� ���� ��츦 ����ϱ� ����, ��ü�� �����ϰ� �Ǿ���.
//ó�� ������ ��, �տ� 3���� NULL�� ������ ��尡 �����Ѵ�.
//double linked ����� queue�� ����Ͽ� ����ϱ�� ��.
typedef char* qElement;

typedef struct _qNode
{
	qElement value;
	struct _qNode* next;
}qNode;

typedef struct 
{
	qNode* strStart; //3ĭ ���� ��ġ�� ��Ÿ�� ����. front�� ����� ����
	qNode* cur; // ���� ���ڿ��� ��Ÿ����.
	qNode* last; //������ ���
}spQueue;

qNode* QnodeInit(qElement value)
{
	qNode* temp = (qNode*)malloc(sizeof(qNode));
	temp->next = NULL;
	temp->value = value;

	return temp;
}

void queueInit(spQueue* queue)
{
	qNode* temp = queue->strStart;
	temp = QnodeInit(NULL);
	temp->next = QnodeInit(NULL);
	temp = temp->next;
	temp->next = QnodeInit(NULL);
	temp = temp->next;
	//�̰� �Ҵ��ص־� addq�� �ſ� ����������.
	// 
	//���� ��ĭ�� �Ҵ��Ѵ�.
	queue->cur = temp;
	queue->last = temp;
}

void addq(spQueue* queue, qElement value)
{
	qNode* temp = QnodeInit(value);
	
	queue->last->next = temp;
	queue->last = queue->last->next;

	if (queue->cur->value == NULL) //�ʱ� 3���̸�,
	{
		queue->cur = queue->last;
	}
}

void deleteq(spQueue* queue) // ���� ���� �ʿ�� ����.
{
	qNode* delNode = queue->strStart;
	queue->strStart = queue->strStart->next;

	if (!delNode->value) // ���ڿ� free �� ����������.
	{
		free(delNode->value);
	}
	free(delNode); // �ش� �� ����.
}

void qsearch(spQueue* queue, const char* str)
{

}

void printStr(spQueue* queue)
{

}