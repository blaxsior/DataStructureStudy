#pragma once
#include <stdio.h>
//특정 파일들에 동시에 필요한 전역 변수 등을 포함하는 헤더 파일.

//버퍼 크기 영단어 중 가장 긴 단어가 46글자인데, 후하게 100으로 맞춤
#define BUF_SIZE 100
//테이블의 사이즈. hash와 Dict에 사용될 예정
#define TABLE_SIZE 1000

//기본적인 파일명
char filename[] = "doc000.txt";

//insert
int cmp_insert_count = 0; //삽입 중 문자열 비교 연산 횟수 | Total number of comparison: 
int file_count = 0; //Total number of documents: 
int word_count = 0; //Total number of indexed words: 

int cmpMode = 1; // 1이면 insert, 0이면 search에 대해 검사한다.

//search
int cmp_search_count = 0; //검색중 문자열 비교 연산 횟수 | Total number of comparison: 