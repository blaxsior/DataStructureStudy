#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//그래프
//연결되어 있는 객체간의 관계를 표현하는 자료구조
//사이 관계를 화살표 등으로 나타낼 수 있다
//트리 역시도 그래프의 일종이다.

//오일러 행로(Euler Walk)
//위치를 정점(vertex), 다리를 간선(edge)인 그래프로 표현했을 때, 모든 정점에 연결된 간선의 수가 짝수이면 경로가 존재한다.
//각 간선을 한번만 지나서, 어떻게 시작점으로 돌아올 수 있을까?
//반드시 경로에 대해서 한번 나갔다가, 한번 들어와야한다. 예컨대, 2번의 간선을 지나게 되는데, 간선의 개수가 짝수개가 아니면 한번만 지나서 도달할 수는 없다.
//반대로 간선의 개수가 짝수개면 경로가 존재한다.

//그래프 G = (V, E) 
//V(G) : 정점(vertex)들의 집합
//E(G) : 간선(edge)들의 집합

//v0 와 v1 사이에 edge 가 존재하면, 둘은 인접(adjacent) 정점이다.

//종류

//1) undirected graph
//(v0,v1) = (v1, v0)
//v0 에서 v1로 가는데 방향이 존재하지 않는 경우
//친구 관계

//2) directed graph, digraph
//<V0,V1> != <V1,V0>
//도로망 / 인터넷 하이퍼 링크 등 

//정점의 차수(degree)
//undirected : v의 차수 : v 와 연결된 edge의 수 혹은 adjacent vertex의 수
//				모든 정점의 차수의 합 : |E| * 2     (모든 edge는 양측에 대해 2번 계산된다.)

//directed : 진입 차수(in-degree), 진출차수(out-degree)로 나뉜다.
//			A로 들어오는 edge가 2개, 나가는 edge가 1개 이면, in-degree = 2, out-degree = 1

//경로(path)
//간선으로 연결된 정점 열
//경로의 길이(length) : 경로사읭 간선수

//	종류: 단순경로(simple path) : 경로 상 vertex가 모두 다르다 
//			사이클(cycle) : 경로 상 vertex가 모두 같다.

//연결 그래프(connected graph) : 그래프 내부의 모든 vertex 에 대하여 path가 존재한다

//연결 요소(connected component) : 그래프 내에 존재하는 최대 연결부분 그래프(maximal connected subgraph)

//트리 -> connected 이지만 , cycle 없는 그래프라고 할 수 있음

//강력 연결 그래프(strongly connected graph) : 모든 쌍의 정점들 사이에 상호 방향 경로가 존재한다.(v1,v2)
//강력 연결 요소(strongly connected component : 그래프 내에서 강하게 최대로 연결된 최대부분 그래프


//완전 그래프 (complete graph) : edge 의 수가 최대인 그래프
//	무방향 그래프 edge 수 : vC2 ( |v| 개의 점 중 2개를 골라 연결하되, (v1,v2)는 (v2,v1)과 구분되지 않음)
//	방향 그래프 edge   수 : vP2 ( |v| 개의 점 중 2개를 골라 연결한다. 양방향은 서로 구분된다)

//2분할 그래프(bipartite graph) : 정점이 두 집합으로 나뉘고, 동일 집합 내의 정점 사이에는 간선이 없는 그래프(p 10 참고)

//부분 그래프 : 그래프의 일부분만 나타낸 그래프

#define MAX 100
#define MAX_VERTICES 10
//그래프의 표현 방법 

//[1] 인접 행렬(adjacency matrix) : n * n 배열 adj[][] 
//방식 int adj[i][j] = 0 / 1
// vertex i 와 vertex j 가 붙어 있으면, 1을 넣는다

//무방향 그래프의 경우 좌우 대각선 기준 그래프가 그려지고, 방향 그래프는 비대칭 그래프가 그려진다.
//vertex ^ 2 의 공간이 필요하게 된다. (무방향 그래프의 경우, 사실은 vertex ^ 2 / 2 
//결국에는 O(n^2)의 공간이 필요하다.

//무방향 그래프의 차수 : 해당 행의 1의 개수
//방향 그래프의 행 ->진출차수 | 열 -> 진입 차수


int graph[MAX][MAX];

//무방향 그래프에서의 엣지 삽입
void insert_edge(int v, int w)
{
	graph[v][w] = 1;
	graph[w][v] = 1;
}

//[2] 리스트 표현법
typedef struct node* node_pointer;

typedef struct node {
	int vertex;
	node_pointer link;
};

node_pointer adj[MAX_VERTICES] = { NULL };

int n = 0;

//필요한 공간
//무방향 : |E| * 2 + n -> O(n + e)
//방향 : |E| + n	   -> O(n + e)

void insert_edgeL(int v, int w)
{
	node_pointer temp;
	temp = (node_pointer)malloc(sizeof(struct node));
	temp->link = NULL;
	temp->vertex = w;
	temp->link = adj[v];
	adj[v] = temp;
}


//가중치 그래프 (weighted graph): 가중치를 도입.

//[1]메트릭스 방식	: 값을 넣을때, 1이 아니라, 가중치를 넣는다.
//[2]리스트 방식	: 가중치 [int (weight)]를 추가로 자료구조에 정의하여 사용한다.



//그래프 탐색(graph search)
//그래프의 한 정점에서 시작하여 연결된 모든 정점들을 차례대로 방문하는 방법

//[1]깊이 우선 탐색(depth frist search, DFS)
//한 정점 v 에서 시작
//인접 정점을 따라 계속 진행
//스택 또는 재귀 함수 이용하여 구현 가능

//이미 가봤던 vertex들을 기록해야 한다.

int visited[MAX_VERTICES];

void dfs(int v)
{
	node_pointer w;
	printf("%d", v);
	visited[v] = 1;//TRUE 의 의미
	for (w = adj[v]; w != NULL; w = w->link)
	{
		if (!visited[w->vertex]) //아직 w->vertex의 위치를 방문하지 않은 경우,
		{
			dfs(w->vertex); //vertex 위치에서 다시 시작한다.
		}
	}
}

//[2]너비 우선 탐색(breath first search, BFS)
//한 정점 v 에서 시작
//인접 정점을 따라 계속 진행
//큐를 이용하여 진행

typedef struct nod
{
	int value;
	struct nod* link;
}qNode;

typedef struct _queue
{
	qNode* front;
	qNode* rear;
}Queue;

Queue queue;

void qInit()
{
	queue.front = NULL;
	queue.rear = NULL;
}

void addq(int v)
{
	qNode* temp = (qNode*)malloc(sizeof(qNode));
	temp->value = v;
	temp->link = NULL;
	if (queue.rear == NULL)
	{
		queue.rear = temp;
		queue.front = queue.rear;
		return;
	}
	queue.rear->link = temp;
	queue.rear = temp;

}

int is_queue_empty()
{
	return (queue.front == NULL);
}

int deleteq()
{
	if (is_queue_empty())
	{
		return NULL;
	}
	qNode* delNode = queue.front;
	queue.front = queue.front->link;//front에서 하나 빼고, 뒤로 이동
	int result = delNode->value;
	free(delNode);

	return result;
}

void bfs(int v)
{
	node_pointer w;
	printf("%d", v);
	visited[v] = 1;//True 의미
	addq(v);
	while (!is_queue_empty()) {
		v = deleteq();
		for (w = adj[v]; w != NULL; w = w->link)
		{
			if (!visited[w->vertex])
			{
				printf("%d ", w->vertex);
				visited[w->vertex] = 1;
				addq(w->vertex);//방문하고 queue에 넣는다.
			}
		}
	}
}


//둘다 list : O(|V|+|E|), array : O(|V|^2)의 시간이 걸린다.
//list ? 방문한 곳을 재방문하지는 않아도, 확인하기 때문에, edge의 수에 비례하는 시간이 걸리고, 각각의 vertex에 대해 check 들어가니까, |V| + |E|의 시간이 걸린다.
//array : 리스트와는 달리, 방문 여부를 알기 위해서 배열 전체에 접근해야 한다. 따라서, 배열의 크기인 |V|^2 만큼 접근한다

//Finding Connected Component
//연결되어 있는 부분은 결국 dfs 쓰나 bfs 쓰나 반드시 지나가게 되므로, bfs 또는 dfs를 써서 확인 가능하다.

void connect()
{
	for (int i = 0; i < n; i++)
	{
		if (!visited[i]) {
			dfs(i);
			printf("\n");
		}
	}
	//connected 되어있는 components 찾을 수 있음
}

//Spanning Tree
//G의 모든 정점을 포함하는 트리
//|V| = 4 이면, |E|는 최소 3개 필요.

//DFS, BFS를 통해서 탐색중 사용된 간선을 추가한다.
//(1) 깊이우선 신장 트리 : DFS로 찾는 spanning tree
//(2) 너비우선 신장 트리 : BFS로 찾는 spanning tree
//->graph search 한번 하면 찾을 수 있음.

//MST(최소비용신장트리, minimum cost spanning tree)
//간선의 가중치 합이 최소인 신장트리
//
//사용되는 알고리즘 -> Greedy algorithm : 매 순간마다 가장 좋다고 생각되는 것들을 선택하여 최종적인 해답에 도달한다.

//kruskal 방식.
//n개의 vertex 중, n-1개의 간선을 찾되, 사이클을 형성하지 않도록 순서대로 찾는다.
//set을 사용하는 언어를 사용하면, 효울적으로 만들 수 있다( set은 O(1) )
//
//T = {}
//While(|T| < n - 1 && |E| != NULL) {
//E에서 최소 비용의 간선을 선택;
//E에서 발견한 최소비용 간선(v.w) 삭제
//if((v,w)가 T에서 사이클 형성 안하면)
// (v,w)를 T에 추가한다.
// }
// if(|T| < n-1)
//		spanning 트리 없다.
//

//O(|E|log|E|)의 복잡도를 가진다. (sorting에 |E|log|E| + 각 edge를 순환 |E| - 1)
//Edge의 숫자에 영향을 받는다. 간선이 적으면 효율적인 알고리즘.

//Prim 방식
//루트노드에서 시작, 해당 노드에서 갈 수 있는 weight가 최소인 노드를 선택한다.
//해당 트리에 대하여, 접근할 수 있는 값들 중에 비용이 최소인 노드를 구하고, 해당 노드를 트리에 추가하는 과정을 계속 반복한다.

//T = {}
//TV = {0} -> 정점 0에서 시작하겠다.
//While(|T| < n - 1){
//u는 TV에 속하고, v는 TV에 속하지 않는 최저비용 간선 (u,v)에 대하여,
// if (간선 존재 안함)
//	break
//v를 TV추가, (u,v) T에 추가
//}
//if(|T| < n-1)
//	spanning tree 존재 안함
//


//O(|V|^2)의 복잡도를 가진다
//정점이 적을 수록 유리한 알고리즘이다.


//단일 출발점/ 모든 도착지 찾기
//Dikstra algorithm 다익스트라 알고리즘
//found[i] = True : i까지의 최단경로를 발견 -> 집합 S, 최단 경로가 확인된 경로들을 추가한다,
//i 번째 vertex까지 최단경로임이 확인되었다는 의미

//distance[i] : 0 에서 S 내의 정점만을 거친 i의 최소거리

//found[i] = false for all i
//distance[i] = cost[0][i] for all i -> 0에서 i로 가는 경로를 처음에 설정해둔다!
//found[0] = true -> 0번째 vertex부터 시작한다.

//repeat
//	found[u] = false && distance[u] is minimum -> 처음 접근한 점에 대하여 distance가 기존보다 minimum이면,
//	found[u] = true(S에 u를 포함한다)
// 모든u 에 인접한 w(found[w]= false) 에 대하여
//	distance[w] = min(distance[w], distance[u]+cost[u][w]), 
//  (S에 포함되지 않은 모든 점에 대하여 조정 들어간다.)

//기본적인 복잡도
// |V| * 2|V| = O(V^2)

//인접 리스트 방식으로 수행 + priority queue(min heap)
//모든 간선이 한번씩 갱신됨 : O(|E|)
//최소 distance 정점 찾기: O(log|E|)
// |E| * log|E| <= |E| * log|V|^2 = O(|E|log|V|)

//All pair shortest path
//모든 쌍의 최단 경로를 만든다
//A-1 -> A0 -> A1 -> A2 -> ... -> An-1로 가는 거리를 업데이트
//시작(A-1)에서부터 시작하여 (00) (01) .... (kk) 까지에 대하여
//(00),(00)  ... (k0)(0k) 으로 가는 경로로 나타내고, 
//(kk) 와 (k0) ~ (0k) 중 더 작은 값을 (kk) 에 대해 업데이트를 수행한다.
//이런식으로 계속 구하면, 모든 경로에 대한 shortest path를 알 수 있다.