#pragma once
#include "word.h"
#include "cQueue.h"

Word* dict[TABLE_SIZE];
//dict에 삽입할 때는 hash1을 사용

//strInit 을 통해 생성된 str을 받는다.
void dictInsert(char* str, int fileIdx)
{
	int hashValue = hash1(str);
	if (str == NULL) //NULL 문자열의 경우
	{
		return;
	}

	if (dict[hashValue] == NULL) // 처음 값이 NULL 인 경우,
	{
		dict[hashValue] = wInit(str); // word를 생성해서 대입
		fInsert(dict[hashValue], fileIdx); // file 정보를 넣음.
		return;
	}
	//root 값이 존재하는 경우. 왼쪽 오른쪽 알아서 비교하면서 넣는다.
	wInsert(dict[hashValue], str, fileIdx);
}

void deleteDictionary()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		wDeleteAll(dict[i]);
	}
}

void searchWord(char* str)
{
	int hashValue = hash1(str);
	int success = 0;

	Word* myWord = wSearch(dict[hashValue], str, &success);
	if (success == 1)
	{
		wPrint(myWord);
	}
}

void makeDictionary()
{
	FILE* fs;
	char buffer[BUF_SIZE];
	for (int idx = 1; idx <= 100; idx++)
	{
		setFileName(idx);
		if ((fs = fopen(filename, "r"))) //해당 이름의 파일이 존재할 때
		{
			file_count++;//읽은 파일 개수 증가
			while (!feof(fs))
			{
				if (fscanf(fs, "%s", buffer) == 1)
				{
					dictInsert(strInit(buffer), idx);
				}				
			}
			fclose(fs);
		}
	}
}