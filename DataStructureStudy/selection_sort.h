#include "swap.h"

void selection_sort(int* list, int length)
{
	int minIdx;

	for (int i = 0; i < length - 1; i++)// 0��° ������ length - 1 idx�� ����
	{
		minIdx = i;
		for (int j = i + 1; j < length; j++)// n-1 ... 1 ���� ������ ����.
		{
			if (list[j] < list[minIdx])
			{
				minIdx = j;
			}//min �� idx�� ã�� ����. minIdx�� ���� �˸� �ȴ�.
		}
		if (i != minIdx)
		{
			swap(&list[i], &list[minIdx]);
		}
	}
}

// ���� �񱳴� (n-1)*(1 + n-1)/2 = n^2 /2 - n/2 ��ŭ �߻��ϹǷ�,
// O(n^2)�� ���⵵�� ���Ѵ�.

