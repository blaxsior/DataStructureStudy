//typedef struct {
//	int value;
//}element;

typedef tree_pointer element;

typedef struct _node0
{
	element item;
	struct _node0 * next;
}Node_O;
//Node one way

typedef struct _node1
{
	element item;
	struct _node1* Llink;
	struct _node1* Rlink;
}Node_R;
//Node round trip

typedef Node_O Node;

//단방향 노드의 기본 값을 지정하고 새로 만들어진 노드를 반환한다.
Node_O* NodeInit(element item)
{
	Node_O* node = (Node_O*)malloc(sizeof(Node_O));
	node->item = item;
	node->next = NULL;
	return node;
}

//양방향 노드의 기본 값을 지정하고 새로 만들어진 노드를 반환한다.
Node_R* RNodeInit(element item)
{
	Node_R* node = (Node_R*)malloc(sizeof(Node_R));
	node->item = item;
	node->Llink = NULL;
	node->Rlink = NULL;

	return node;
}