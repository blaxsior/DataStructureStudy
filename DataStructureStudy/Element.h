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

//�ܹ��� ����� �⺻ ���� �����ϰ� ���� ������� ��带 ��ȯ�Ѵ�.
Node_O* NodeInit(element item)
{
	Node_O* node = (Node_O*)malloc(sizeof(Node_O));
	node->item = item;
	node->next = NULL;
	return node;
}

//����� ����� �⺻ ���� �����ϰ� ���� ������� ��带 ��ȯ�Ѵ�.
Node_R* RNodeInit(element item)
{
	Node_R* node = (Node_R*)malloc(sizeof(Node_R));
	node->item = item;
	node->Llink = NULL;
	node->Rlink = NULL;

	return node;
}