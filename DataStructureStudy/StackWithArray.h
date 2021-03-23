#define Boolean int
#define MAX_SIZE 100 // �����ؼ� ������ ���� ���� ����.

typedef struct {
	int key;
}element;

element stack[MAX_SIZE];
int top = -1;

Boolean IsEmpty()
{
	return (top == -1);
}

Boolean IsFull()
{
	return top >= (MAX_SIZE - 1);
}// top >= MAX_SIZE - 1 �̸�, 0 �� �ƴ� ���� ��ȯ, �ƴϸ� 0�� ��ȯ.

void push(element elem)
{
	if (!IsFull()) // ������ �� ���� �ʾҴٸ�.
	{
		stack[top] = elem;
		top++;
	}
}

element pop()
{
	if (!IsEmpty()) // �� �� ��Ȳ�� �ƴϸ� pop ����. �ƴϸ� �ƹ��͵� ����.
	{
		return stack[top--];
		// ���� ���� �ʿ�� ����, ���ϸ� ���� �ʱ�ȭ �ϸ� �ȴ�.
	}
}

// ������ ��� : function call
// �Լ� ȣ�� ��, ���� �Լ��� ȣ��Ǹ� �ý��� ���ÿ� function�� ���� ������ push, �ش� function�� return �� �� ���� �ش� ������ pop ����.