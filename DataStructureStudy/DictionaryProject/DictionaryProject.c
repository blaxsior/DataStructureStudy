#pragma once

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//메모리 누수 검사용 코드

#include <stdio.h>
#include "Dict.h"
#include "cQueue.h"
#include "strUtil.h"

int main()
{
	//scanf("%*s");
	//_CrtSetBreakAlloc(292);
	char buffer[BUF_SIZE];
	makeDictionary();
	printf("Total number of documents: %d\n", file_count);
	printf("Total number of indexed words: %d\n", word_count);
	printf("Total number of comparison: %d\n", cmp_insert_count);
	cmpMode = 0; // search를 검사한다.
	
	printf("[ # ] to Quit\n");
	printf("Word: ");
	while (scanf("%s", buffer) == 1)
	{
		if (buffer[0] == '#')
		{
			printf("Bye!\n");
			break;
		}
		cmp_search_count = 0; //혹시 모르는 상황 대비 초기화
		searchWord(buffer);
		printf("\nTotal number of comparison: %d\n", cmp_search_count);
		
		printf("Word: ");
	}
	deleteDictionary();
	//scanf("%*s");
	//_CrtDumpMemoryLeaks();
}