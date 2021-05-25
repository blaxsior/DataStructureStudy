#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Symbol table :
// key - value ������ �����͸� ����.
// operation : 
// Insert. Delete. Search
// �ٽ��� �Ǵ� �κ��� Ž�� �κ�!

//���
//1) List : O(n) ������� Ž��
//2) BST  : average O(log n)
//3) Hashing : O(1) (�ؽ� �Լ��� �� ������� ���)
//		Key ���� ������ �ʰ�, �ؽ� �Լ��� �̿��Ͽ� key �� ���� ���� ��ġ�� �ٷ� ����Ѵ�.
//		key �� ������ ������� ������ ����� �����ϹǷ�, ����ð� ���� search�� ����.
//		�������� �ܾ ã�� ��, ������ �պ��� ���� ���� �ƴ϶�, �ش� ���ĺ����� �ٷ� search �õ��ϴ� ��İ� ���.

//hashing ���
//(1) Static Hashing : 
// Ideal�� ��� : key ��ü�� �״�� ����Ѵ�. ex) �й��� key�� ���
//
//add(key, value)
//	index = hash_function(key)
//	ht[index] = value
//
//search(key)
//	index = hash_function(key)
//	return ht[index]
//

//
// In real : �Ұ����ϰų� ��ȿ������. key ������ ���ؼ� ������ �ʹ� ���� ���� �� ����. -> �ٸ� hashing function �ʿ�!
//	ex) Hash function : ID�� Ư�� �ڸ����� ������.
//	-> �̷� ��ĵ� collision�� �߻��� ���ɼ� ����. (2018123, 2021123) -> 123���� �浹 �߻�

/********************************************************************************/

//Hash Table : ������ �������� ���̺�(2���� �迭 ��) �� <key, value> ������ �ڷḦ �����ϴ� �ڷᱸ��.
//
// ���Ǿ�(synonyms) : �� key �� ���� �� f(i1) = f(i2) �� ��
//						ex) f(char) = (fceil) = 2

// �浹(collision) : �� ���� �ٸ� key�� ���� bucket�� �ؽ̵Ǵ� ���)
// hashing 'char' -> hashing 'ceil'

// �����÷ο�(overflow)
// ���ο� key i �� ������ bucket�� �ؽ� ��Ű�� ���
// ���� ������ ���� ���

//�˻� ���� ����
//BST : ��� O(log n) �־� O(n)
//Hashing : hash �ð� + bucket search
//				= O(1) ���� �ð� �ɸ� (bucket�� ���� ���� �����ٰ� ����)

/********************************************************************************/

//���� �е�(loading density, loading factor)
// a = n/(s*b)
//		s : number of slots in each bucket
//		b : number of bucket

// ex) n = 500.  b = 1000, s = 1
// 0.5

/********************************************************************************/

//�ʿ� ����?

// ����� �����ؾ� �Ѵ�
// �浹�� ����� �Ѵ�(key �� ���� �л�Ǿ�� �Ѵ�)
// ex) ù ���ڷ� �ؽ� �õ��ϸ�, �浹 �����Ƿ� ���� �ʴ�.


//���� �ؽ� �Լ�(uniform hash function)
//��� ��Ŷ�� ���Ͽ� 1) �����ϰ� ����, 2) collision �� �ּ�

/********************************************************************************/

//Hash Function

//(1) �����Լ�(division)
// h(x) = x mod M (M�� ���̺��� ũ��)
// [0, M-1] �� ����
// M�� ������ �߿��ϴ�. (�������� ������ ����� �ȵ�!
//
// !!! M �� ���� : �Ҽ� Ȥ�� 20 ������ �Ҽ��� ������ �ʴ� ���� ��������!

//�߰� ���� �Լ�(mid-square)
//h(x) = x �� ������ ��, �߰��� r ��Ʈ�� �����Ѵ�.
//[0, 2^r - 1]
//� ���� ���Ƶ� �ٸ� �ؽ� �ּ� ������ �ȴ�.

//���� �Լ�(folding)
//h(x) x �� ���� �κ����� ������ ���Ѵ�. 
// ex) �ܾ��� �� ���ڸ� char�� �����ϰ� �ش� ������ ���Ѵ�.


/********************************************************************************/

// Overflow Handling �����÷ο� ó��

//(1) ���� ���� �ּҹ�
//	1)���������(linear proving) : ���� ����� ���� ���Ͽ� ����
//	2)���������(quadratic probing) : i^2 ������ ��ġ ����
//	3)���ؽ�(rehashing) : �ٸ� �ؽ��Լ� ���

//(2) ü�̴�(chaining) : �浹 �߻���, linked list�� �����Ͽ� ����

#define TABLE_SIZE 100
typedef struct
{
	char key[30];
	int value;
}item;
typedef item element;

element ht[TABLE_SIZE];

/********************************************************************************/

// ���������(linear proving)
// �浹 �Ͼ�� ���� �ڸ��� ���� [ (h(x) + i) % TABLE_SIZE ]

int transform(char* key) {
	int number = 0;
	while (*key)
		number += *key++; //folding ����
	return number;
}

int linearHash(char* key) {
	return (transform(key) % TABLE_SIZE);
}

void linearInsert(element item)
{
	int i = linearHash(item.key);
	int hv = i;
	//for(int j = 0; j < )
	while (strlen(ht[i].key) != 0) // ��ĭ �ƴ� �� ����!
	{
		if (strcmp(ht[i].key, item.key) == 0)
		{//�ߺ��� ��
			printf("duplication!\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hv) // ������� ���ƿ�
		{
			printf("table full!\n");
			return;
		}
	}
	ht[i] = item;
}

void linear_search(element item)
{
	int idx = linearHash(item.key);
	int hx = idx;

	while (strlen(ht[idx].key) != 0) // �� �� bucket�� �ƴ� ��
	{
		if (strcmp(ht[idx].key, item.key) != 0) {
			printf("loc : %d!\n", idx);
			return;
		}
		idx = (idx + 1) % TABLE_SIZE; // ���� ĭ Ž��
		if (idx == hx)
		{
			break;
		}
	}
	printf("fail to search\n");
}

//�˻� �ð� :
//���� �е� a �� ���Ͽ� 0.5 ���ϰ� �Ǹ�, �뷫������ ����ð� ���� ó�� �����ϴ�.
//�����ؽ��Լ��� ���� ��Ȳ.

//Ư¡:
//Ŭ�����͵��� ���� ��ġ�� ���ļ� ��Ÿ�� �� �ִ� -> �������� ������, ���� ������ �� �ִ�.

/********************************************************************************/

// ���������(Quadratic Probing)
// ht[(h(x) + i^2) % b], 0 <= i <=(b-1)/2
// Ŭ�����͸��� ����.
// ������� �˻� �ð� ����.

// ���ؽ�(Rehashing)
// �浹 �߻��� ���ο� �ؽ� �Լ��� ����!
// ht[(h(x) + i * h'(x)) % b]

/********************************************************************************/

// ü�̴�(Chaining)
// ���� �� �ϳ��� ���� ����Ʈ�� ���
// �� ����Ʈ�� ��� synonym�� ����

typedef struct list* list_ptr;

typedef struct list
{
	element item;
	list_ptr link;
};

list_ptr cht[TABLE_SIZE];


int hash(char* key) {
	int x = 0;
	char* cur = key;

	while (*cur != '\0')
	{
		x += *cur;
		cur++;
	}//folding ������� �ؽ� ����
	return x % TABLE_SIZE;
}


void chain_insert(element item) {
	int i = hash(item.key);
	list_ptr temp, before = NULL;

	for (list_ptr cur = cht[i]; cur != NULL; before = cur, cur = cur->link)
	{
		if (strcmp(cur->item.key, item.key) == 0)
		{
			printf("�ߺ�!\n");
			return;
		}
	}
	temp = (list*)malloc(sizeof(list));
	temp->item = item;
	temp->link = NULL;
	if (before)//���ۺ��� NULL ������ ���� �ƴ� ���
		before->link = temp;
	else //���ۺ��� NULL ���ͼ� cur�� NULL�� ���-> ���̺� ó������ ���� ��� -> ���̺� ó������ ����.
		cht[i] = temp;
}

void chain_search(element item) {
	int i = hash(item.key);
	for (list_ptr cur = cht[i]; cur != NULL; cur = cur->link)
	{
		if (strcmp(cur->item.key, item.key) == 0)
		{
			printf("success!\n");
			return; //�߰��� ���!
		}
	}
	printf("fail\n"); //������ Ž���ص� �߰� ���ϴ� ���!
}

//�˻�(search) �ð�
// ���� �е� a �� ���Ͽ�,
// �� ���� �� key �� : ��� a ( a = key / ���̺� ������)
//�ؽ� ���̺� ���� key ��� �˻� �ð� U = a
//�ؽ� ���̺� �ִ� key ��� �˻� �ð� S = 1 + a/2

//�ؽ� ���̺��� Ư¡(�� ����)
// Ư¡ : ����� ��������� �Һ��Ͽ�, ���� �ӵ��� ��½�Ű�� ����� ä���Ѵ�.
// ���� : ����� ���̺� ũ��� ���� �ؽ� �Լ�(uniform hashing function) �� ����� �˰��� ����, O(1)�� ����� �ð��� �ɸ���.
// ���� : Data�� ũ�� �����ʹ� ���� ���� ����ǹǷ�, ũ�⿡ ���� ���� ����� �ſ� ��ȿ������ ����̴�.