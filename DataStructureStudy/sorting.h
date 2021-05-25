

//���� : �ڷḦ Ư�� Ű ���� ���� ������������ ����
//���� �˰����� ���� : key �� �� ȸ���� �м��Ѵ�.
//���� �˰����� ������(stability): ���� key �� ������ �������� ����� ������ �ٲ��� �ʴ´�.
//���� ���� : ��� �����Ͱ� ���� �޸� ���� �ִ� ����
//�ܺ� ���� : �������� ���� ���, ��� �����͸� ���� �޸𸮷� ���̴� ��� �ܺα�� ��ġ�� ����Ǿ� �ִ� ���·� �����Ѵ�.

//���� �˰���

//(1) Bubble Sort
//������ 2�� key�� ��, ������� �Ǿ� ���� ������ ���� ��ȯ�Ѵ�.

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void bubble_sort(int arr[], int count)
{
	int isSwap = 1;
	//�߰��� �ȹٲ�� ���, ���� ���Ѵ�.
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
//���ĵǾ��ִ� �κп� ���ο� key�� ��� �����Ѵ�.

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
//�̹� ���ĵ� ��� : O(n)
//����: �˰����� �����ϴ�.
//������(stability)�� �ִ�.
//���ĵ� ����Ʈ������ ȿ�����̴�.

//(#) optimal Sorting Tree
//���� ���� ���� �ð��� ����Ʈ���� ����Ͽ� �м�
//ex [K0,K1,K2]�� ����
//�ִ� 3�� ��

//decision tree ����:
//	������ ���� ��� �� n!
//���� h�� ����Ʈ�� ���� �� L <=2^h
//~ O(nlog n)
//� Ű ���� ���ϴ� �˰��� nlog n �̻��� ����� �䱸�ȴ�.


//(4) Merge Sort
//����Ʈ�� ����, ���ҵ� ����Ʈ �鿡 ���� ������ �����ϰ�,
//�ش� ����Ʈ�鵵 Merge Sort. ����, �ش� ������ �����Ѵ�.

//Merge: ���ĵ� �� ����Ʈ�� ���Ѵ�.
//���� �� ���ĵ� ���鿡 ����, ��Ģ�� ���� �ϳ��� ���ο� ������ �ִ´�
// 2578	#1346		1
//#2578	 346		12
// 578	#346		123
// 578	#46			1234 ...

void merge(int arr[], int left, int mid, int right)
{
	int sorted[100]; // �ӽ�
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

//�ð����⵵ : O(nlog n)
//T(n) = n + 2T(n/2) / 2n + 4T(n/4) ...
//	   = kn + 2^kT(n/2^k)
// k = log n ���� ��ȯ�ϸ�
// nlog n + nT(1)
// => O(nlog n)

//(5) Quick Sort
//pivot key�� �̿��Ͽ� ����Ʈ�� �����Ѵ�
//recursive -> �ι��� quick sort�� �����Ѵ�.
//1�� ���� �� ���� �ϳ��� �����͸� ó���Ѵ�

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

//Average Case: merge sort�� ����ϰ� ����, O(nlog n)

//worst case: �׻� �����͸� 1 vs �������� �����Ѵ�
//T(n) = n + T(n-1) + T(n-2) + ... = O(n^2)

//���� ���ĵ� ����Ʈ�� ���ؼ��� �ſ� ��ȿ�����̴�.

//(6) Max heap ������ �̿��� ���� ���
//1. max heap ����(insert n)
//2. delete_max ����(n��)

//worst case: O(nlog n)
// insert/ delete ��� worst case�� O(log n) �̴�.

void adjust(int list[], int root, int n)
{
	//delete_MAX�� ����� �κ��� �ڵ�
	//leaf ��尡 �ƴ� �κп� ���� �ڵ� ����
	//heap �ڷᱸ�� �����ϸ鼭 �ٽ� ����.
	int temp = list[root], child = 2 * root;
	while (child <= n) {
		if ((child < n) && (list[child] < list[child + 1])) child++;//�� ū �ڽĳ�� ã��
		if (temp > list[child])
			break;
		else {
			list[child / 2] = list[child];//�ڽ� ���κб��� ã�ƺ���.
			child = child * 2;
		}
	}
	list[child / 2] = temp;
}

void heap_sort(int list[], int n)
{
	//max heap���� �����ϴ� ����
	for (int i = n / 2; i > 0; i--)
	{
		adjust(list, i, n);
	}

	//delete_max�� ���� ����
	for (int i = n - 1; i > 0; i--)
	{
		swap(&list[1], &list[i + 1]);
		adjust(list, 1, i);
	}
}

//(7) Radix Sort

//Ű ���� ������ �ʰ� �ؽ̰� ���� ����� ���� Ű ���� ���� ���� ���Ͽ� �����ϴ� ���.
//�������� Ű ���� ���� ���ʴ�� �����Ѵ�.

//���ο� �ɸ��� �ð� : O(n)
//�ε����� random access�� �����ϹǷ�, �̷� ���� �����ߴ�.
// d �ڸ� 10����? -> O(dn) d �� ���� ������, O(n)������� �� �� �ִ�

//���� : Ű�� ���̰� ������ ������ ������ ���ڿ��̾�� �Ѵ�.