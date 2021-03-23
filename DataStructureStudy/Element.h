typedef struct {
	int value;
}element;


typedef struct _node
{
	element item;
	struct _node * next;
}Node;