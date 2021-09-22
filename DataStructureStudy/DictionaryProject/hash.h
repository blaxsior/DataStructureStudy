#pragma once
#include "base.h"

const int priNum1[] = { 59,7,37,19,17, 23,71,29,5,53, 67,2,11,47,41, 31,13,3,43,61 };
const int priNum2[] = { 71,31,61,19,47, 13,5,3,2,67, 37,29,7,41,23, 59,43,53,11,17 };

//�ؽ��Լ�. �������� ������ 2 ~ 71 ������ �Ҽ� 20���� �̿�, �� ���ڿ� ���ϸ鼭 �ؽ� �Լ� ����.

//folding ��� ���
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
	//prime �� priNum1 �Ǵ� priNum2�� �־� ���}
}

int hash1(char* str)
{
	return hash(str, priNum1)%TABLE_SIZE;
}

int hash2(char* str)
{
	return hash(str, priNum2);
}