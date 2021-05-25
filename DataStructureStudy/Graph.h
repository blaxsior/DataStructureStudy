#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//�׷���
//����Ǿ� �ִ� ��ü���� ���踦 ǥ���ϴ� �ڷᱸ��
//���� ���踦 ȭ��ǥ ������ ��Ÿ�� �� �ִ�
//Ʈ�� ���õ� �׷����� �����̴�.

//���Ϸ� ���(Euler Walk)
//��ġ�� ����(vertex), �ٸ��� ����(edge)�� �׷����� ǥ������ ��, ��� ������ ����� ������ ���� ¦���̸� ��ΰ� �����Ѵ�.
//�� ������ �ѹ��� ������, ��� ���������� ���ƿ� �� ������?
//�ݵ�� ��ο� ���ؼ� �ѹ� �����ٰ�, �ѹ� ���;��Ѵ�. ������, 2���� ������ ������ �Ǵµ�, ������ ������ ¦������ �ƴϸ� �ѹ��� ������ ������ ���� ����.
//�ݴ�� ������ ������ ¦������ ��ΰ� �����Ѵ�.

//�׷��� G = (V, E) 
//V(G) : ����(vertex)���� ����
//E(G) : ����(edge)���� ����

//v0 �� v1 ���̿� edge �� �����ϸ�, ���� ����(adjacent) �����̴�.

//����

//1) undirected graph
//(v0,v1) = (v1, v0)
//v0 ���� v1�� ���µ� ������ �������� �ʴ� ���
//ģ�� ����

//2) directed graph, digraph
//<V0,V1> != <V1,V0>
//���θ� / ���ͳ� ������ ��ũ �� 

//������ ����(degree)
//undirected : v�� ���� : v �� ����� edge�� �� Ȥ�� adjacent vertex�� ��
//				��� ������ ������ �� : |E| * 2     (��� edge�� ������ ���� 2�� ���ȴ�.)

//directed : ���� ����(in-degree), ��������(out-degree)�� ������.
//			A�� ������ edge�� 2��, ������ edge�� 1�� �̸�, in-degree = 2, out-degree = 1

//���(path)
//�������� ����� ���� ��
//����� ����(length) : ��λ�� ������

//	����: �ܼ����(simple path) : ��� �� vertex�� ��� �ٸ��� 
//			����Ŭ(cycle) : ��� �� vertex�� ��� ����.

//���� �׷���(connected graph) : �׷��� ������ ��� vertex �� ���Ͽ� path�� �����Ѵ�

//���� ���(connected component) : �׷��� ���� �����ϴ� �ִ� ����κ� �׷���(maximal connected subgraph)

//Ʈ�� -> connected ������ , cycle ���� �׷������ �� �� ����

//���� ���� �׷���(strongly connected graph) : ��� ���� ������ ���̿� ��ȣ ���� ��ΰ� �����Ѵ�.(v1,v2)
//���� ���� ���(strongly connected component : �׷��� ������ ���ϰ� �ִ�� ����� �ִ�κ� �׷���


//���� �׷��� (complete graph) : edge �� ���� �ִ��� �׷���
//	������ �׷��� edge �� : vC2 ( |v| ���� �� �� 2���� ��� �����ϵ�, (v1,v2)�� (v2,v1)�� ���е��� ����)
//	���� �׷��� edge   �� : vP2 ( |v| ���� �� �� 2���� ��� �����Ѵ�. ������� ���� ���еȴ�)

//2���� �׷���(bipartite graph) : ������ �� �������� ������, ���� ���� ���� ���� ���̿��� ������ ���� �׷���(p 10 ����)

//�κ� �׷��� : �׷����� �Ϻκи� ��Ÿ�� �׷���

#define MAX 100
#define MAX_VERTICES 10
//�׷����� ǥ�� ��� 

//[1] ���� ���(adjacency matrix) : n * n �迭 adj[][] 
//��� int adj[i][j] = 0 / 1
// vertex i �� vertex j �� �پ� ������, 1�� �ִ´�

//������ �׷����� ��� �¿� �밢�� ���� �׷����� �׷�����, ���� �׷����� ���Ī �׷����� �׷�����.
//vertex ^ 2 �� ������ �ʿ��ϰ� �ȴ�. (������ �׷����� ���, ����� vertex ^ 2 / 2 
//�ᱹ���� O(n^2)�� ������ �ʿ��ϴ�.

//������ �׷����� ���� : �ش� ���� 1�� ����
//���� �׷����� �� ->�������� | �� -> ���� ����


int graph[MAX][MAX];

//������ �׷��������� ���� ����
void insert_edge(int v, int w)
{
	graph[v][w] = 1;
	graph[w][v] = 1;
}

//[2] ����Ʈ ǥ����
typedef struct node* node_pointer;

typedef struct node {
	int vertex;
	node_pointer link;
};

node_pointer adj[MAX_VERTICES] = { NULL };

int n = 0;

//�ʿ��� ����
//������ : |E| * 2 + n -> O(n + e)
//���� : |E| + n	   -> O(n + e)

void insert_edgeL(int v, int w)
{
	node_pointer temp;
	temp = (node_pointer)malloc(sizeof(struct node));
	temp->link = NULL;
	temp->vertex = w;
	temp->link = adj[v];
	adj[v] = temp;
}


//����ġ �׷��� (weighted graph): ����ġ�� ����.

//[1]��Ʈ���� ���	: ���� ������, 1�� �ƴ϶�, ����ġ�� �ִ´�.
//[2]����Ʈ ���	: ����ġ [int (weight)]�� �߰��� �ڷᱸ���� �����Ͽ� ����Ѵ�.



//�׷��� Ž��(graph search)
//�׷����� �� �������� �����Ͽ� ����� ��� �������� ���ʴ�� �湮�ϴ� ���

//[1]���� �켱 Ž��(depth frist search, DFS)
//�� ���� v ���� ����
//���� ������ ���� ��� ����
//���� �Ǵ� ��� �Լ� �̿��Ͽ� ���� ����

//�̹� ���ô� vertex���� ����ؾ� �Ѵ�.

int visited[MAX_VERTICES];

void dfs(int v)
{
	node_pointer w;
	printf("%d", v);
	visited[v] = 1;//TRUE �� �ǹ�
	for (w = adj[v]; w != NULL; w = w->link)
	{
		if (!visited[w->vertex]) //���� w->vertex�� ��ġ�� �湮���� ���� ���,
		{
			dfs(w->vertex); //vertex ��ġ���� �ٽ� �����Ѵ�.
		}
	}
}

//[2]�ʺ� �켱 Ž��(breath first search, BFS)
//�� ���� v ���� ����
//���� ������ ���� ��� ����
//ť�� �̿��Ͽ� ����

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
	queue.front = queue.front->link;//front���� �ϳ� ����, �ڷ� �̵�
	int result = delNode->value;
	free(delNode);

	return result;
}

void bfs(int v)
{
	node_pointer w;
	printf("%d", v);
	visited[v] = 1;//True �ǹ�
	addq(v);
	while (!is_queue_empty()) {
		v = deleteq();
		for (w = adj[v]; w != NULL; w = w->link)
		{
			if (!visited[w->vertex])
			{
				printf("%d ", w->vertex);
				visited[w->vertex] = 1;
				addq(w->vertex);//�湮�ϰ� queue�� �ִ´�.
			}
		}
	}
}


//�Ѵ� list : O(|V|+|E|), array : O(|V|^2)�� �ð��� �ɸ���.
//list ? �湮�� ���� ��湮������ �ʾƵ�, Ȯ���ϱ� ������, edge�� ���� ����ϴ� �ð��� �ɸ���, ������ vertex�� ���� check ���ϱ�, |V| + |E|�� �ð��� �ɸ���.
//array : ����Ʈ�ʹ� �޸�, �湮 ���θ� �˱� ���ؼ� �迭 ��ü�� �����ؾ� �Ѵ�. ����, �迭�� ũ���� |V|^2 ��ŭ �����Ѵ�

//Finding Connected Component
//����Ǿ� �ִ� �κ��� �ᱹ dfs ���� bfs ���� �ݵ�� �������� �ǹǷ�, bfs �Ǵ� dfs�� �Ἥ Ȯ�� �����ϴ�.

void connect()
{
	for (int i = 0; i < n; i++)
	{
		if (!visited[i]) {
			dfs(i);
			printf("\n");
		}
	}
	//connected �Ǿ��ִ� components ã�� �� ����
}

//Spanning Tree
//G�� ��� ������ �����ϴ� Ʈ��
//|V| = 4 �̸�, |E|�� �ּ� 3�� �ʿ�.

//DFS, BFS�� ���ؼ� Ž���� ���� ������ �߰��Ѵ�.
//(1) ���̿켱 ���� Ʈ�� : DFS�� ã�� spanning tree
//(2) �ʺ�켱 ���� Ʈ�� : BFS�� ã�� spanning tree
//->graph search �ѹ� �ϸ� ã�� �� ����.

//MST(�ּҺ�����Ʈ��, minimum cost spanning tree)
//������ ����ġ ���� �ּ��� ����Ʈ��
//
//���Ǵ� �˰��� -> Greedy algorithm : �� �������� ���� ���ٰ� �����Ǵ� �͵��� �����Ͽ� �������� �ش信 �����Ѵ�.

//kruskal ���.
//n���� vertex ��, n-1���� ������ ã��, ����Ŭ�� �������� �ʵ��� ������� ã�´�.
//set�� ����ϴ� �� ����ϸ�, ȿ�������� ���� �� �ִ�( set�� O(1) )
//
//T = {}
//While(|T| < n - 1 && |E| != NULL) {
//E���� �ּ� ����� ������ ����;
//E���� �߰��� �ּҺ�� ����(v.w) ����
//if((v,w)�� T���� ����Ŭ ���� ���ϸ�)
// (v,w)�� T�� �߰��Ѵ�.
// }
// if(|T| < n-1)
//		spanning Ʈ�� ����.
//

//O(|E|log|E|)�� ���⵵�� ������. (sorting�� |E|log|E| + �� edge�� ��ȯ |E| - 1)
//Edge�� ���ڿ� ������ �޴´�. ������ ������ ȿ������ �˰���.

//Prim ���
//��Ʈ��忡�� ����, �ش� ��忡�� �� �� �ִ� weight�� �ּ��� ��带 �����Ѵ�.
//�ش� Ʈ���� ���Ͽ�, ������ �� �ִ� ���� �߿� ����� �ּ��� ��带 ���ϰ�, �ش� ��带 Ʈ���� �߰��ϴ� ������ ��� �ݺ��Ѵ�.

//T = {}
//TV = {0} -> ���� 0���� �����ϰڴ�.
//While(|T| < n - 1){
//u�� TV�� ���ϰ�, v�� TV�� ������ �ʴ� ������� ���� (u,v)�� ���Ͽ�,
// if (���� ���� ����)
//	break
//v�� TV�߰�, (u,v) T�� �߰�
//}
//if(|T| < n-1)
//	spanning tree ���� ����
//


//O(|V|^2)�� ���⵵�� ������
//������ ���� ���� ������ �˰����̴�.


//���� �����/ ��� ������ ã��
//Dikstra algorithm ���ͽ�Ʈ�� �˰���
//found[i] = True : i������ �ִܰ�θ� �߰� -> ���� S, �ִ� ��ΰ� Ȯ�ε� ��ε��� �߰��Ѵ�,
//i ��° vertex���� �ִܰ������ Ȯ�εǾ��ٴ� �ǹ�

//distance[i] : 0 ���� S ���� �������� ��ģ i�� �ּҰŸ�

//found[i] = false for all i
//distance[i] = cost[0][i] for all i -> 0���� i�� ���� ��θ� ó���� �����صд�!
//found[0] = true -> 0��° vertex���� �����Ѵ�.

//repeat
//	found[u] = false && distance[u] is minimum -> ó�� ������ ���� ���Ͽ� distance�� �������� minimum�̸�,
//	found[u] = true(S�� u�� �����Ѵ�)
// ���u �� ������ w(found[w]= false) �� ���Ͽ�
//	distance[w] = min(distance[w], distance[u]+cost[u][w]), 
//  (S�� ���Ե��� ���� ��� ���� ���Ͽ� ���� ����.)

//�⺻���� ���⵵
// |V| * 2|V| = O(V^2)

//���� ����Ʈ ������� ���� + priority queue(min heap)
//��� ������ �ѹ��� ���ŵ� : O(|E|)
//�ּ� distance ���� ã��: O(log|E|)
// |E| * log|E| <= |E| * log|V|^2 = O(|E|log|V|)

//All pair shortest path
//��� ���� �ִ� ��θ� �����
//A-1 -> A0 -> A1 -> A2 -> ... -> An-1�� ���� �Ÿ��� ������Ʈ
//����(A-1)�������� �����Ͽ� (00) (01) .... (kk) ������ ���Ͽ�
//(00),(00)  ... (k0)(0k) ���� ���� ��η� ��Ÿ����, 
//(kk) �� (k0) ~ (0k) �� �� ���� ���� (kk) �� ���� ������Ʈ�� �����Ѵ�.
//�̷������� ��� ���ϸ�, ��� ��ο� ���� shortest path�� �� �� �ִ�.