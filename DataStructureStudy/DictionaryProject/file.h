#pragma once
#include <stdlib.h>
#include "strUtil.h"
#include "cQueue.h"

// struct file은  양방향 리스트 구조로 구성된다.

typedef struct _file
{
	int idx; // 파일 번호. 이후, 이 번호를 사용해서 파일 접근할 예정이다.
	int count; // 단어가 나타난 횟수
	struct _file* before;
	struct _file* next; // 뒷 노드
}File;

File* fInit(int idx)
{
	File* temp = (File*)malloc(sizeof(File));
	
	temp->idx = idx;
	temp->count = 1;
	temp->before = NULL;
	temp->next = NULL;

	return temp;
}

void fPrintSentence(File* input, char* curWord)
{
	int count = 0;
	if (input)
	{
		FILE* fs;
		char buffer[BUF_SIZE];
		setFileName(input->idx);
		cQInit();
		char* temp;

		if ((fs = fopen(filename, "r"))) //해당 이름의 파일이 존재할 때
		{
			while (!feof(fs) && !cQFull())
			{
				if (fscanf(fs, "%s", buffer) == 1)
				{
					if ((temp = getrawStr(buffer)) != NULL) cQadd(temp);
				}
			}
			while (!feof(fs))
			{
				if (count >= input->count) break;

				temp = strInit(cQueue[cur]);
				if (temp != NULL)
				{
					if (strncmp(curWord, temp, BUF_SIZE) == 0)
					{
						cQprt(feof(fs));
					}
					free(temp);
				}
				cQdel();
				if (fscanf(fs, "%s", buffer) == 1)
				{
					if ((temp = getrawStr(buffer)) != NULL) cQadd(temp);
				}
			}
			while (!cQEmpty())
			{
				temp = strInit(cQueue[cur]);
				if (temp != NULL)
				{
					if (count < input->count && strncmp(curWord, temp, BUF_SIZE) == 0)
					{
						cQprt(feof(fs));
					}
					free(temp);
				}
				cQdel();
			}
			fclose(fs);
		}
	}
}

void fDeleteAll(File* input)
{
	File* current = input;
	File* delNode;

	while (current != NULL)
	{
		delNode = current;
		current = current->next;
		free(delNode);
	}//순차적으로 전부 삭제
}