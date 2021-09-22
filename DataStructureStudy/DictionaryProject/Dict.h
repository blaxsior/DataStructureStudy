#pragma once
#include "word.h"
#include "cQueue.h"

Word* dict[TABLE_SIZE];
//dict�� ������ ���� hash1�� ���

//strInit �� ���� ������ str�� �޴´�.
void dictInsert(char* str, int fileIdx)
{
	int hashValue = hash1(str);
	if (str == NULL) //NULL ���ڿ��� ���
	{
		return;
	}

	if (dict[hashValue] == NULL) // ó�� ���� NULL �� ���,
	{
		dict[hashValue] = wInit(str); // word�� �����ؼ� ����
		fInsert(dict[hashValue], fileIdx); // file ������ ����.
		return;
	}
	//root ���� �����ϴ� ���. ���� ������ �˾Ƽ� ���ϸ鼭 �ִ´�.
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
		if ((fs = fopen(filename, "r"))) //�ش� �̸��� ������ ������ ��
		{
			file_count++;//���� ���� ���� ����
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