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

char* strInit(char* str) //malloc 사용-> 외부에서 free 필요!
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
			buffer[count] = tolower(*cur);//소문자로 저장한다
			count++;
			if (count >= BUF_SIZE - 1)
				return NULL;
			//혹시 버퍼 넘을 상황 대비.
		}
		cur++;//다음 char로 이동한다.
	}
	if (count != 0) //문자열이 존재하면
	{
		buffer[count] = '\0'; //마지막에 문자열 끝났다고 표시해준다.
		char* returnStr = (char*)malloc(sizeof(char) * (count+1)); //문자열 + '\0' 문자의 길이가 된다
		
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
