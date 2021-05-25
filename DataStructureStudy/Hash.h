#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Symbol table :
// key - value 쌍으로 데이터를 저장.
// operation : 
// Insert. Delete. Search
// 핵심이 되는 부분은 탐색 부분!

//방식
//1) List : O(n) 순서대로 탐색
//2) BST  : average O(log n)
//3) Hashing : O(1) (해시 함수가 잘 만들어진 경우)
//		Key 값을 비교하지 않고, 해시 함수를 이용하여 key 로 부터 저장 위치를 바로 계산한다.
//		key 의 개수와 관계없이 빠르게 계산이 가능하므로, 상수시간 내에 search가 가능.
//		사전에서 단어를 찾을 때, 사전을 앞부터 보는 것이 아니라, 해당 알파벳부터 바로 search 시도하는 방식과 비슷.

//hashing 방식
//(1) Static Hashing : 
// Ideal한 방식 : key 자체를 그대로 사용한다. ex) 학번을 key로 사용
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
// In real : 불가능하거나 비효율적임. key 개수에 비해서 공간이 너무 많이 사용될 수 있음. -> 다른 hashing function 필요!
//	ex) Hash function : ID를 특정 자리수로 나눈다.
//	-> 이런 방식도 collision이 발생할 가능성 존재. (2018123, 2021123) -> 123으로 충돌 발생

/********************************************************************************/

//Hash Table : 고정된 사이즈의 테이블(2차원 배열 등) 에 <key, value> 쌍으로 자료를 저장하는 자료구조.
//
// 동의어(synonyms) : 두 key 가 같을 때 f(i1) = f(i2) 일 때
//						ex) f(char) = (fceil) = 2

// 충돌(collision) : 두 개의 다른 key가 같은 bucket에 해싱되는 경우)
// hashing 'char' -> hashing 'ceil'

// 오버플로우(overflow)
// 새로운 key i 를 가득찬 bucket에 해싱 시키는 경우
// 저장 공간이 없는 경우

//검색 삽입 삭제
//BST : 평균 O(log n) 최악 O(n)
//Hashing : hash 시간 + bucket search
//				= O(1) 정도 시간 걸림 (bucket이 고정 길이 가진다고 가정)

/********************************************************************************/

//적재 밀도(loading density, loading factor)
// a = n/(s*b)
//		s : number of slots in each bucket
//		b : number of bucket

// ex) n = 500.  b = 1000, s = 1
// 0.5

/********************************************************************************/

//필요 조건?

// 계산이 간단해야 한다
// 충돌이 적어야 한다(key 가 고르게 분산되어야 한다)
// ex) 첫 문자로 해싱 시도하면, 충돌 많으므로 좋지 않다.


//균일 해싱 함수(uniform hash function)
//모든 버킷에 대하여 1) 균일하게 분포, 2) collision 이 최소

/********************************************************************************/

//Hash Function

//(1) 제산함수(division)
// h(x) = x mod M (M은 테이블의 크기)
// [0, M-1] 의 범위
// M의 선택이 중요하다. (한쪽으로 몰리게 만들면 안됨!
//
// !!! M 의 선택 : 소수 혹은 20 이하의 소수로 나뉘지 않는 값을 선택하자!

//중간 제곱 함수(mid-square)
//h(x) = x 를 제곱한 후, 중간의 r 비트를 선택한다.
//[0, 2^r - 1]
//몇개 문자 같아도 다른 해싱 주소 가지게 된다.

//폴딩 함수(folding)
//h(x) x 를 여러 부분으로 나누어 더한다. 
// ex) 단어의 각 문자를 char로 생각하고 해당 값들을 더한다.


/********************************************************************************/

// Overflow Handling 오버플로우 처리

//(1) 선형 개방 주소법
//	1)선형조사법(linear proving) : 가장 가까운 다음 버켓에 저장
//	2)이차조사법(quadratic probing) : i^2 떨어진 위치 저장
//	3)재해싱(rehashing) : 다른 해시함수 사용

//(2) 체이닝(chaining) : 충돌 발생시, linked list에 연결하여 저장

#define TABLE_SIZE 100
typedef struct
{
	char key[30];
	int value;
}item;
typedef item element;

element ht[TABLE_SIZE];

/********************************************************************************/

// 선형조사법(linear proving)
// 충돌 일어나면 다음 자리에 저장 [ (h(x) + i) % TABLE_SIZE ]

int transform(char* key) {
	int number = 0;
	while (*key)
		number += *key++; //folding 수행
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
	while (strlen(ht[i].key) != 0) // 빈칸 아닐 때 까지!
	{
		if (strcmp(ht[i].key, item.key) == 0)
		{//중복일 때
			printf("duplication!\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hv) // 원래대로 돌아옴
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

	while (strlen(ht[idx].key) != 0) // 텅 빈 bucket이 아닐 때
	{
		if (strcmp(ht[idx].key, item.key) != 0) {
			printf("loc : %d!\n", idx);
			return;
		}
		idx = (idx + 1) % TABLE_SIZE; // 다음 칸 탐색
		if (idx == hx)
		{
			break;
		}
	}
	printf("fail to search\n");
}

//검색 시간 :
//적재 밀도 a 에 대하여 0.5 이하가 되면, 대략적으로 상수시간 내로 처리 가능하다.
//균일해싱함수일 때의 상황.

//특징:
//클러스터들이 일정 위치에 뭉쳐서 나타날 수 있다 -> 균일하지 않으며, 성능 나빠질 수 있다.

/********************************************************************************/

// 이차조사법(Quadratic Probing)
// ht[(h(x) + i^2) % b], 0 <= i <=(b-1)/2
// 클러스터링이 감소.
// 평균적인 검색 시간 감소.

// 리해싱(Rehashing)
// 충돌 발생시 새로운 해시 함수를 적용!
// ht[(h(x) + i * h'(x)) % b]

/********************************************************************************/

// 체이닝(Chaining)
// 버켓 당 하나의 연결 리스트를 사용
// 각 리스트는 모든 synonym을 저장

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
	}//folding 방식으로 해시 구성
	return x % TABLE_SIZE;
}


void chain_insert(element item) {
	int i = hash(item.key);
	list_ptr temp, before = NULL;

	for (list_ptr cur = cht[i]; cur != NULL; before = cur, cur = cur->link)
	{
		if (strcmp(cur->item.key, item.key) == 0)
		{
			printf("중복!\n");
			return;
		}
	}
	temp = (list*)malloc(sizeof(list));
	temp->item = item;
	temp->link = NULL;
	if (before)//시작부터 NULL 나오는 것은 아닌 경우
		before->link = temp;
	else //시작부터 NULL 나와서 cur이 NULL인 경우-> 테이블에 처음으로 들어가는 경우 -> 테이블에 처음으로 넣음.
		cht[i] = temp;
}

void chain_search(element item) {
	int i = hash(item.key);
	for (list_ptr cur = cht[i]; cur != NULL; cur = cur->link)
	{
		if (strcmp(cur->item.key, item.key) == 0)
		{
			printf("success!\n");
			return; //발견한 경우!
		}
	}
	printf("fail\n"); //끝까지 탐색해도 발견 못하는 경우!
}

//검색(search) 시간
// 적재 밀도 a 에 대하여,
// 각 버켓 당 key 수 : 평균 a ( a = key / 테이블 사이즈)
//해싱 테이블에 없는 key 평균 검색 시간 U = a
//해싱 테이블에 있는 key 평균 검색 시간 S = 1 + a/2

//해싱 테이블의 특징(장 단점)
// 특징 : 충분한 저장공간을 소비하여, 동작 속도를 상승시키는 방식을 채택한다.
// 장점 : 충분한 테이블 크기와 균일 해싱 함수(uniform hashing function) 에 가까운 알고리즘 사용시, O(1)에 가까운 시간이 걸린다.
// 단점 : Data의 크기 순서와는 관계 없이 저장되므로, 크기에 의한 연산 수행시 매우 비효울적인 방식이다.