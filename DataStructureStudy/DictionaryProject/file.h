#pragma once
#include <stdlib.h>
#include "strUtil.h"
#include "cQueue.h"

// struct file��  ����� ����Ʈ ������ �����ȴ�.

typedef struct _file
{
	int idx; // ���� ��ȣ. ����, �� ��ȣ�� ����ؼ� ���� ������ �����̴�.
	int count; // �ܾ ��Ÿ�� Ƚ��
	struct _file* before;
	struct _file* next; // �� ���
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

		if ((fs = fopen(filename, "r"))) //�ش� �̸��� ������ ������ ��
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
	}//���������� ���� ����
}