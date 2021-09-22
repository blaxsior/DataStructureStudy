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
	temp->list = fInit(-1);// file 은 계속 sorting을 진행하므로, 이를 편하게 하기 위해 더미노드 생성.
	temp->lc = NULL;
	temp->rc = NULL;

	return temp;
}

void fInsert(Word* curWord, int fileIdx)
{
	File* current = curWord->list; //더미노드

	while (current->next != NULL)
	{
		//cmp_insert_count++;
		if (current->next->idx == fileIdx) //file을 발견
		{
			current->next->count++;
			current = current->next;
			while (current->before->idx != -1) //더미노드가 앞 노드이면 더이상 자리 못바꾼다.
			{
				if (current->count > current->before->count)//내부 값만 변경하는 방식으로...
				{
					int tempIdx = current->idx;
					int tempcount = current->count;
					
					current->idx = current->before->idx;
					current->count = current->before->count;
					current->before->idx = tempIdx;
					current->before->count = tempcount;

					current = current->before;
				}
				else break;//자기자리 찾음.
			}
			return;
		}
		current = current->next;
	}
	//current는 마지막 값인 경우. 무조건 처음에는 count 1이고, 이 값이 최소이므로 비교 필요 없음.
	File* temp = fInit(fileIdx);
	temp->before = current;
	current->next = temp;
}
//hash 2를 사용하여, 내부적으로 위치를 설정.
//success 테이블 방식
//성공 혹은 left/right 로 수행됨.
//left = -1 : 작거나 같은 경우
//right = -2 : 큰 경우
//success = 1 : 해당값 획득
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
			//아래에서 strcmp 한번 수행
			if (strncmp(current->str, str, BUF_SIZE) == 0)
			{
				*success = 1;
				return current;
			}
		}
		if (route <= 0) //작거나 같으면 왼쪽에 저장.
		{
			current = current->lc;
			*success = -1; //왼쪽
		}
		else
		{
			current = current->rc;
			*success = -2; //오른쪽
		}
	}
	//cur == NULL이 나와버리는 상황
	return before;
}
//root에서 insert 여부 찾기 시작. str에 대해 wsearch를 이용하여 위치 탐색. 없으면 만들고. curfile 삽입
void wInsert(Word* root, char* str, int fileIdx)
{
	int success = 0;
	
	Word* current = wSearch(root, str, &success);
	if (success == 1)//실제로 있음-> file만 삽입
	{
		free(str);
		fInsert(current, fileIdx);
	}
	else if (success == -1)//없는 경우-> wInit으로 생성 후 삽입.
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
	else//오류 상황. 오류 발생했음을 알린다.
	{
		printf("word 삽입 실패. 오류 발생\n");
		exit(EXIT_FAILURE);
	}
}

void wPrint(Word* target)
{
	File* current = target->list->next;//word->list는 더미노드

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
//post order traverse 사용
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