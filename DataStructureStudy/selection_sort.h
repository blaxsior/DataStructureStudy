#include "swap.h"

void selection_sort(int* list, int length)
{
	int minIdx;

	for (int i = 0; i < length - 1; i++)// 0번째 값부터 length - 1 idx에 대해
	{
		minIdx = i;
		for (int j = i + 1; j < length; j++)// n-1 ... 1 번의 연산을 수행.
		{
			if (list[j] < list[minIdx])
			{
				minIdx = j;
			}//min 의 idx를 찾는 과정. minIdx의 값만 알면 된다.
		}
		if (i != minIdx)
		{
			swap(&list[i], &list[minIdx]);
		}
	}
}

// 값의 비교는 (n-1)*(1 + n-1)/2 = n^2 /2 - n/2 만큼 발생하므로,
// O(n^2)의 복잡도를 지닌다.

