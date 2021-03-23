#define Boolean int
#define MAX_SIZE 100 // 변경해서 스택의 길이 변경 가능.

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
}// top >= MAX_SIZE - 1 이면, 0 이 아닌 값을 반환, 아니면 0을 반환.

void push(element elem)
{
	if (!IsFull()) // 스택이 꽉 차지 않았다면.
	{
		stack[top] = elem;
		top++;
	}
}

element pop()
{
	if (!IsEmpty()) // 텅 빈 상황이 아니면 pop 수행. 아니면 아무것도 안함.
	{
		return stack[top--];
		// 값을 지울 필요는 없고, 원하면 값을 초기화 하면 된다.
	}
}

// 스택의 용례 : function call
// 함수 호출 중, 내부 함수가 호출되면 시스템 스택에 function에 관한 정보가 push, 해당 function이 return 될 때 마다 해당 정보를 pop 수행.