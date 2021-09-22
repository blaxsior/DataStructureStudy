#pragma once
#include <stdio.h>
#include <stdlib.h>
#define QSize 8 // �ִ� ���� 7���̰� ���� ���� 1ĭ ���

typedef char* qElement;

qElement cQueue[QSize];
int front;
int rear;
int cur;
/*******************************/

void cQInit();
int cQIdx(int x);
int cQEmpty();
int cQFull();
int cQcanUse();
void cQprt(int end);
void cQadd(qElement str);
void cQdel();

/*******************************/

void cQInit()
{
	front = 0;
	rear = 0;
	cur = 0;
	for (int i = 0; i < 3; i++)
	{
		cQadd(NULL);
	}
}

int cQIdx(int x) // ���� �ڸ� �˾Ƴ��� �Լ�
{
	return (x + 1) % QSize;
}

int cQEmpty() // �� ����� ����
{
	return (front == rear);
	printf("empty\n");
}

int cQFull() // �� á�� ����
{
	return (front == cQIdx(rear));
}

int cQcanUse()
{
	return cQueue[cur] != NULL;
}

void cQprt(int end)
{
	if (cQcanUse())
	{
		if(cQueue[cQIdx(front)]) printf("... "); //NULL�̸� ��� ����
		for (int i = cQIdx(front); i != cQIdx(rear); i = cQIdx(i))
		{
			if (cQueue[i] != NULL)
			{
				printf("%s ", cQueue[i]);
			}
		}
		if(!end) printf("...");
		putchar('\n');
	}
}

void cQadd(qElement str)
{
	if (!cQFull())
	{
		rear = cQIdx(rear);
		cQueue[rear] = str;
		if (cur != cQIdx(front + 3))
		{
			cur = cQIdx(cur);
			// cur�� front���� 3ĭ �տ� �־�� ��.
			// �� Ư¡�� �����ϱ� ���� �ڵ�
		}
	//	printf("%d %d %d\n", front, cur, rear);
	}
	else {
		printf("full\n");
	}
}

void cQdel() //
{
	if (!cQEmpty())
	{
		front = cQIdx(front);
		free(cQueue[front]);
		cQueue[front] = NULL;
		if (cur != cQIdx(rear))
		{
			cur = cQIdx(cur);
			//cur �� rear�� ���� idx�ڸ���� ����, ������ ������ �о��ٴ� �ǹ�.
			//add ���� delete�� ����Ǵ� ��츦 �Ǵ��Ѵ�.
			//cur�� ������ �� �д� ���� ������.
		}
	//	printf("%d %d %d\n", front, cur, rear);
	}
	else {
		printf("empty\n");
	}
}
