#include <stdlib.h>
#include <stdio.h>

//앞뒤로 단어 3개씩 출력하기 위해 만들었다.
//computer-computer-computer 같이 문자열이 오는 경우를 대비하기 위해, 전체를 저장하게 되었음.
//처음 시작할 때, 앞에 3개의 NULL을 가지는 노드가 존재한다.
//double linked 방식의 queue를 사용하여 출력하기로 함.
typedef char* qElement;

typedef struct _qNode
{
	qElement value;
	struct _qNode* next;
}qNode;

typedef struct 
{
	qNode* strStart; //3칸 전의 위치를 나타낼 예정. front와 비슷한 역할
	qNode* cur; // 현재 문자열을 나타낸다.
	qNode* last; //마지막 노드
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
	//이걸 할당해둬야 addq가 매우 간편해진다.
	// 
	//앞의 세칸을 할당한다.
	queue->cur = temp;
	queue->last = temp;
}

void addq(spQueue* queue, qElement value)
{
	qNode* temp = QnodeInit(value);
	
	queue->last->next = temp;
	queue->last = queue->last->next;

	if (queue->cur->value == NULL) //초기 3개이면,
	{
		queue->cur = queue->last;
	}
}

void deleteq(spQueue* queue) // 딱히 꺼낼 필요는 없다.
{
	qNode* delNode = queue->strStart;
	queue->strStart = queue->strStart->next;

	if (!delNode->value) // 문자열 free 로 날려버린다.
	{
		free(delNode->value);
	}
	free(delNode); // 해당 값 제거.
}

void qsearch(spQueue* queue, const char* str)
{

}

void printStr(spQueue* queue)
{

}