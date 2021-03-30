//typedef struct {
//	int value;
//}element;

typedef int element;

typedef struct _node0
{
	element item;
	struct _node0 * next;
}Node_O;
//Node one way

typedef struct _node1
{
	element item;
	struct _node1* before;
	struct _node1* next;
}Node_R;
//Node round trip

typedef Node_O Node;