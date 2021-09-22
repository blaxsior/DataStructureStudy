#pragma once
#include <stdio.h>
#include <stdlib.h>
#define QSize 8 // 최대 원소 7개이고 구분 위해 1칸 비움

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

int cQIdx(int x) // 다음 자리 알아내는 함수
{
	return (x + 1) % QSize;
}

int cQEmpty() // 텅 비었나 여부
{
	return (front == rear);
	printf("empty\n");
}

int cQFull() // 꽉 찼나 여부
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
		if(cQueue[cQIdx(front)]) printf("... "); //NULL이면 출력 안함
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
			// cur은 front보다 3칸 앞에 있어야 함.
			// 이 특징을 구현하기 위한 코드
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
			//cur 이 rear의 다음 idx자리라는 것은, 파일을 끝까지 읽었다는 의미.
			//add 없이 delete만 수행되는 경우를 판단한다.
			//cur을 끝까지 다 읽는 순간 끝난다.
		}
	//	printf("%d %d %d\n", front, cur, rear);
	}
	else {
		printf("empty\n");
	}
}
