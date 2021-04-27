#include "Element.h"
#include <assert.h>
//최대 heap과 최소 heap이 존재
//기본적으로 완전이진트리에 기반한다.
//완전이진트리이므로, 배열 기반으로 힙을 구성할 수 있다.


//1) insertion in Max heap
//	우선, 순서에 따라 마지막 순서에 넣는다.
//	최대 힙의 조건을 생각하면, 자기보다 큰 값이 아래에 있으면 안된다.
//	따라서 삽입한 자리에 대해 부모 노드와 값을 비교, 부모 노드의 값보다 크기가 크면 부모 노드와 위치를 바꾼다
//	위 과정을 루트 노드까지 반복한다.

#define MAX 30

element Heap[MAX];//MAX 크기의 Heap을 선언한다.
int maxIdx = -1; //아무런 값도 넣지 않았음. 나중에 이 인덱스에 1을 더하고 값을 넣을 예정이다.

//				0
//		1				2
//	3		4		5		6	
//

int getParent(int idx)
{
	return (idx - 1) / 2;
}

int getLC(int idx)
{
	return idx * 2 + 1;
}

int getRC(int idx)
{
	return idx * 2 + 2;
}


void insert_max_heap(element item)
{
	maxIdx++;
	assert(maxIdx < MAX);

	int idx = maxIdx;
	while ((idx != 0) && item > Heap[getParent(idx)])	//idx가 루트 노드가 아니고, 
	{													//현재 노드 기준으로 부모 노드보다 현재 노드의 값이 더 클 때
		Heap[idx] = Heap[getParent(idx)];				//max heap이므로, 부모노드의 값이 더 커야하는데 자식이 더 크니까 부모의 값을 자식의 값으로 옮긴다( 자식의 값은 item에 저장되어 있으므로, 마지막에 한번만 넣어도 OK)
		idx = getParent(idx);
	}

	Heap[idx] = item; //마지막에 나왔다는 의미? 현재 위치에 item이 위치하면 된다는 의미!
}
//O(log n) 이다.
// 2^(h-1) -1 < h <= 2^(h-1) 의 노드 개수
// log2(n+1) <= h <= 

element delete_max_heap() // MAX가 되는 값을 제거한다.
{
	int result = Heap[0];
	int temp = Heap[maxIdx--];
	int p = 0, c = 1; //루트노드와 루트노드의 자식노드
	while (c <= maxIdx)
	{
		if((c<=maxIdx)&&(Heap[c] < Heap[c+1])) c++;
		if (temp > Heap[c]) break;
		Heap[p] = Heap[c];
		p = c;
		c = getLC(c); //시작 자체가 left child에서 시작했으므로, 나중에 lc로 간다.
	}
	Heap[p] = temp;
	return result;
}
//1) 루트노드의 값을 max에 저장한다.
//2) Heap[maxIdx]의 값을 Heap[0]으로 이동시키고, maxIdx--;
//3) p = 0, c = 1로 설정한다
//4) c 에 대하여(왼쪽 child) c+1 의 값이 더 크면(오른쪽 노드), 


//search의 경우. 별 조건이 없으므로, 모든 노드를 전부 다 탐색해야 하므로, O(n) 의 시간이 걸린다
//Priority Queue를 구성해야 할 때, heap을 이용한다.
//FIFO 가 아니라, 우선순위에 따라 정보를 보내고 싶을 때 사용한다.
//기본적인 목적은 search에 없기 때문에, 이에 대해서는 잘 고려하지 않는다.
//heap은 노드보다 크다/ 작다의 조건만 있을 뿐, 그 이하의 값에 대해서는 보장하지 않으므로 

//긴급한 Job 혹은, 짧은 것 먼저 처리해서 평균적인 대기 시간을 줄이기 위해서 사용

//선형 자료구조를 사용하는 경우에는
//	1) 데이터를 넣는 경우 혹은 2) 데이터를 빼는 경우 둘중 하나는 O(n)을 가지게 된다.
// unordered -> delete, ordered -> insert

//그러나, priority Queue(Heap 기반) 의 경우, 두 경우 모두가 O(log n)의 시간을 가지므로 더 효율적인 상황이 나온다.
//따라서 1) 우선순위가 있고, 2) 자료를 넣고 빼는 경우(insert & delete) Heap 자료구조를 사용하자!