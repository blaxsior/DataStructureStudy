#pragma once
#include "file.h"
#include "hash.h"

typedef struct _word
{
	char* str;
	File* list;
	struct _word* lc;
	struct _word* rc;
}Word;

Word* wInit(char* item)
{
	word_count++;
	Word* temp = (Word*)malloc(sizeof(Word));
//	printf("%s: %d\n", item, hash1(item));

	temp->str = item;
	temp->list = fInit(-1);// file �� ��� sorting�� �����ϹǷ�, �̸� ���ϰ� �ϱ� ���� ���̳�� ����.
	temp->lc = NULL;
	temp->rc = NULL;

	return temp;
}

void fInsert(Word* curWord, int fileIdx)
{
	File* current = curWord->list; //���̳��

	while (current->next != NULL)
	{
		//cmp_insert_count++;
		if (current->next->idx == fileIdx) //file�� �߰�
		{
			current->next->count++;
			current = current->next;
			while (current->before->idx != -1) //���̳�尡 �� ����̸� ���̻� �ڸ� ���ٲ۴�.
			{
				if (current->count > current->before->count)//���� ���� �����ϴ� �������...
				{
					int tempIdx = current->idx;
					int tempcount = current->count;
					
					current->idx = current->before->idx;
					current->count = current->before->count;
					current->before->idx = tempIdx;
					current->before->count = tempcount;

					current = current->before;
				}
				else break;//�ڱ��ڸ� ã��.
			}
			return;
		}
		current = current->next;
	}
	//current�� ������ ���� ���. ������ ó������ count 1�̰�, �� ���� �ּ��̹Ƿ� �� �ʿ� ����.
	File* temp = fInit(fileIdx);
	temp->before = current;
	current->next = temp;
}
//hash 2�� ����Ͽ�, ���������� ��ġ�� ����.
//success ���̺� ���
//���� Ȥ�� left/right �� �����.
//left = -1 : �۰ų� ���� ���
//right = -2 : ū ���
//success = 1 : �ش簪 ȹ��
Word* wSearch(Word* root, char* str ,int* success)
{
	Word* current = root;
	Word* before = NULL;

	int hashValue = hash2(str);

	while (current != NULL)
	{
		before = current;

		int route = hash2(current->str) - hashValue;
		
		cmpMode ? cmp_insert_count++ : cmp_search_count++;
		if (route == 0)
		{
			cmpMode ? cmp_insert_count++ : cmp_search_count++;
			//�Ʒ����� strcmp �ѹ� ����
			if (strncmp(current->str, str, BUF_SIZE) == 0)
			{
				*success = 1;
				return current;
			}
		}
		if (route <= 0) //�۰ų� ������ ���ʿ� ����.
		{
			current = current->lc;
			*success = -1; //����
		}
		else
		{
			current = current->rc;
			*success = -2; //������
		}
	}
	//cur == NULL�� ���͹����� ��Ȳ
	return before;
}
//root���� insert ���� ã�� ����. str�� ���� wsearch�� �̿��Ͽ� ��ġ Ž��. ������ �����. curfile ����
void wInsert(Word* root, char* str, int fileIdx)
{
	int success = 0;
	
	Word* current = wSearch(root, str, &success);
	if (success == 1)//������ ����-> file�� ����
	{
		free(str);
		fInsert(current, fileIdx);
	}
	else if (success == -1)//���� ���-> wInit���� ���� �� ����.
	{
//		printf("%s: %d\n", str, hash1(str));
		current->lc = wInit(str);
		fInsert(current->lc, fileIdx);
	}
	else if (success == -2)
	{
//		printf("%s: %d\n", str, hash1(str));
		current->rc = wInit(str);
		fInsert(current->rc, fileIdx);
	}
	else//���� ��Ȳ. ���� �߻������� �˸���.
	{
		printf("word ���� ����. ���� �߻�\n");
		exit(EXIT_FAILURE);
	}
}

void wPrint(Word* target)
{
	File* current = target->list->next;//word->list�� ���̳��

	printf("*****************************\n");
	while (current != NULL)
	{
		setFileName(current->idx);
		printf("%s (%s: %d)\n", filename, target->str, current->count);
		fPrintSentence(current, target->str);
		current = current->next;
		putchar('\n');
	}
	printf("*****************************\n");
}
//post order traverse ���
void wDeleteAll(Word* root)
{
	if (root == NULL)
	{
		return;
	}
	
	wDeleteAll(root->lc);
	wDeleteAll(root->rc);

	fDeleteAll(root->list);
	free(root->str);
	free(root);
}