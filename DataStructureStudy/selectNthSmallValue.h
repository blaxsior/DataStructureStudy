#include <string.h>
#include <stdlib.h>
#include "swap.h"

int selectNthSmallValue(int* list, int n, int k)
{
	int minIdx;
	int* innerList = (int*)malloc(sizeof(int) * n);
	memcpy(innerList, list, sizeof(int) * n);

	for (int i = 0; i < k; i++)
	{
		minIdx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (innerList[j] < innerList[minIdx])
			{
				minIdx = j;
			}
		}
		swap(&innerList[i], &innerList[minIdx]);
	}
	int result = innerList[k - 1];
	free(innerList);
	return result;
}
