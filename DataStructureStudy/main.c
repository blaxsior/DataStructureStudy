#include <stdio.h>
#include "selection_sort.h"
#define Length(arr) (sizeof(arr)/ sizeof(arr[0])) // 배열에만 사용
int main()
{

	int arr[] = { 51,4,11,8,5,3,6,97,43,17 };
	selection_sort(arr, Length(arr));
	
	for (int i = 0; i < Length(arr); i++)
	{
		printf("%d ", arr[i]);
	}
}