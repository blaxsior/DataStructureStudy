#pragma once
#include "base.h"

const int priNum1[] = { 59,7,37,19,17, 23,71,29,5,53, 67,2,11,47,41, 31,13,3,43,61 };
const int priNum2[] = { 71,31,61,19,47, 13,5,3,2,67, 37,29,7,41,23, 59,43,53,11,17 };

//해시함수. 무작위로 설정된 2 ~ 71 사이의 소수 20개를 이용, 각 문자와 곱하면서 해시 함수 생성.

//folding 방식 사용
int hash(char* str, const int prime[])
{
	int value = 0;
	int count = 0;
	if (str != NULL)
	{
		for (char* cur = str; *cur != '\0'; cur++)
		{
			value += (count < 20) ? (*cur) * (prime[count]) : (*cur);
			count++;
		}
	}
	return value;
	//prime 에 priNum1 또는 priNum2를 넣어 사용}
}

int hash1(char* str)
{
	return hash(str, priNum1)%TABLE_SIZE;
}

int hash2(char* str)
{
	return hash(str, priNum2);
}