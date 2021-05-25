

//정렬 : 자료를 특정 키 값에 따라 오름차순으로 정리
//정렬 알고리즘의 성능 : key 값 비교 회수를 분석한다.
//정렬 알고리즘의 안정성(stability): 동일 key 값 가지는 데이터의 상대적 순서가 바뀌지 않는다.
//내부 정렬 : 모든 데이터가 메인 메모리 내에 있는 상태
//외부 정렬 : 데이터의 양의 방대, 모든 데이터를 메인 메모리로 들이는 대신 외부기억 장치에 저장되어 있는 상태로 정렬한다.

//정렬 알고리즘

//(1) Bubble Sort
//인접한 2개 key를 비교, 순서대로 되어 있지 않으면 서로 교환한다.

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void bubble_sort(int arr[], int count)
{
	int isSwap = 1;
	//중간에 안바뀌는 경우, 수행 안한다.
	for (int i = count-1; isSwap != 0; i--)
	{
		isSwap = 0;
		for (int j = 0; j < i; j++)
		{
			if (arr[j + 1] > arr[j])
			{
				swap(&arr[j + 1], &arr[j]);
				isSwap = 1;
			}
		}
	}
}//worst case O(n^2)

//(2) Insertion Sort
//정렬되어있는 부분에 새로운 key를 계속 삽입한다.

void insertion_sort(int arr[], int count)
{
	for (int i = 1; i < count; i++) {
		int next = arr[i];
		int j;
		for (j = i - 1; j >= 0 && next < arr[j]; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = next;
	}
}
//worst case : O(n^2)
//이미 정렬된 경우 : O(n)
//장점: 알고리즘이 간단하다.
//안정성(stability)이 있다.
//정렬된 리스트에서는 효율적이다.

//(#) optimal Sorting Tree
//최적 정렬 가능 시간을 결정트리를 사용하여 분석
//ex [K0,K1,K2]를 정렬
//최대 3번 비교

//decision tree 높이:
//	가능한 정렬 결과 수 n!
//높이 h인 이진트리 리프 수 L <=2^h
//~ O(nlog n)
//어떤 키 값을 비교하는 알고리즘도 nlog n 이상의 계산이 요구된다.


//(4) Merge Sort
//리스트를 분할, 분할된 리스트 들에 대해 정렬을 수행하고,
//해당 리스트들도 Merge Sort. 이후, 해당 값들을 결합한다.

//Merge: 정렬된 두 리스트를 합한다.
//분할 및 정렬된 값들에 대해, 규칙에 따라 하나씩 새로운 공간에 넣는다
// 2578	#1346		1
//#2578	 346		12
// 578	#346		123
// 578	#46			1234 ...

void merge(int arr[], int left, int mid, int right)
{
	int sorted[100]; // 임시
	int i = left, j = mid + 1, k = 0;

	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j]) sorted[k++] = arr[i++];
		else                  sorted[k++] = arr[j++];
	}
	if (i > mid) for (int n = j; n <= right; n++) sorted[k++] = arr[n];
	else         for (int n = j; n <= mid; n++) sorted[k++] = arr[n];
	int idx = 0;
	for (int i = left; i <= right; i++)
	{
		arr[i] = sorted[idx++];
	}
}

void merge_sort(int arr[], int left, int right)
{
	if (left < right) {
		int mid = (left + right) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

//시간복잡도 : O(nlog n)
//T(n) = n + 2T(n/2) / 2n + 4T(n/4) ...
//	   = kn + 2^kT(n/2^k)
// k = log n 으로 변환하면
// nlog n + nT(1)
// => O(nlog n)

//(5) Quick Sort
//pivot key를 이용하여 리스트를 분할한다
//recursive -> 두번의 quick sort를 수행한다.
//1번 비교할 때 마다 하나의 데이터를 처리한다

int partition(int arr[], int left, int right)
{
	int i = left, j = right + 1;
	int pivot = arr[left];
	while (i < j) {
		while (arr[++i] < pivot);
		while (arr[--j] > pivot);
		if (i < j) swap(&arr[i], &arr[j]);
	}
	swap(&arr[left], &arr[j]);
	return j;
}

void quick_sort(int arr[], int left, int right)
{
	if (left < right) {
		int j = partition(arr, left, right);

		quick_sort(arr, left, j - 1);
		quick_sort(arr, j + 1, right);
	}
}

//Average Case: merge sort와 비슷하게 구성, O(nlog n)

//worst case: 항상 데이터를 1 vs 나머지로 분할한다
//T(n) = n + T(n-1) + T(n-2) + ... = O(n^2)

//거의 정렬된 리스트에 대해서는 매우 비효율적이다.

//(6) Max heap 구조를 이용한 정렬 방식
//1. max heap 구성(insert n)
//2. delete_max 수행(n번)

//worst case: O(nlog n)
// insert/ delete 모두 worst case에 O(log n) 이다.

void adjust(int list[], int root, int n)
{
	//delete_MAX와 비슷한 부분의 코드
	//leaf 노드가 아닌 부분에 대해 코드 수행
	//heap 자료구조 공부하면서 다시 보기.
	int temp = list[root], child = 2 * root;
	while (child <= n) {
		if ((child < n) && (list[child] < list[child + 1])) child++;//더 큰 자식노드 찾기
		if (temp > list[child])
			break;
		else {
			list[child / 2] = list[child];//자식 노드부분까지 찾아본다.
			child = child * 2;
		}
	}
	list[child / 2] = temp;
}

void heap_sort(int list[], int n)
{
	//max heap으로 변경하는 과정
	for (int i = n / 2; i > 0; i--)
	{
		adjust(list, i, n);
	}

	//delete_max에 의한 정렬
	for (int i = n - 1; i > 0; i--)
	{
		swap(&list[1], &list[i + 1]);
		adjust(list, 1, i);
	}
}

//(7) Radix Sort

//키 값을 비교하지 않고 해싱과 같은 방식을 통해 키 값에 따라 직접 버켓에 매핑하는 방식.
//여러개의 키 값에 따라 차례대로 수행한다.

//매핑에 걸리는 시간 : O(n)
//인덱스에 random access가 가능하므로, 이런 것이 가능했다.
// d 자리 10진수? -> O(dn) d 가 작은 상수라면, O(n)정도라고 볼 수 있다

//단점 : 키의 길이가 동일한 길이의 정수나 문자열이어야 한다.