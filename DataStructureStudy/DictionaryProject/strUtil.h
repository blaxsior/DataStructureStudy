#pragma once
#include "base.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void setFileName(int number)
{
	char o1 = '0' + number / 100;
	char o2 = '0' + (number / 10) % 10;
	char o3 = '0' + (number % 10);
	filename[3] = o1;
	filename[4] = o2;
	filename[5] = o3;
}

char* strInit(char* str) //malloc ���-> �ܺο��� free �ʿ�!
{
	if (str == NULL)
		return NULL;
	char buffer[BUF_SIZE];
	int count = 0;
	char* cur = str;
	while (*cur != '\0')
	{
		if (isalpha(*cur))
		{
			buffer[count] = tolower(*cur);//�ҹ��ڷ� �����Ѵ�
			count++;
			if (count >= BUF_SIZE - 1)
				return NULL;
			//Ȥ�� ���� ���� ��Ȳ ���.
		}
		cur++;//���� char�� �̵��Ѵ�.
	}
	if (count != 0) //���ڿ��� �����ϸ�
	{
		buffer[count] = '\0'; //�������� ���ڿ� �����ٰ� ǥ�����ش�.
		char* returnStr = (char*)malloc(sizeof(char) * (count+1)); //���ڿ� + '\0' ������ ���̰� �ȴ�
		
		memcpy(returnStr, buffer, count);
		returnStr[count] = '\0';
		return returnStr;
	}
	else
	{
		return NULL;
	}
}

char* getrawStr(char* str)
{
	int len = strlen(str) + 1;
	char* returnStr = (char*)malloc(sizeof(char) * len);
	memcpy(returnStr, str, len);
	//returnStr[len] = '\0';

	return returnStr;
}
