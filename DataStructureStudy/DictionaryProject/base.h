#pragma once
#include <stdio.h>
//Ư�� ���ϵ鿡 ���ÿ� �ʿ��� ���� ���� ���� �����ϴ� ��� ����.

//���� ũ�� ���ܾ� �� ���� �� �ܾ 46�����ε�, ���ϰ� 100���� ����
#define BUF_SIZE 100
//���̺��� ������. hash�� Dict�� ���� ����
#define TABLE_SIZE 1000

//�⺻���� ���ϸ�
char filename[] = "doc000.txt";

//insert
int cmp_insert_count = 0; //���� �� ���ڿ� �� ���� Ƚ�� | Total number of comparison: 
int file_count = 0; //Total number of documents: 
int word_count = 0; //Total number of indexed words: 

int cmpMode = 1; // 1�̸� insert, 0�̸� search�� ���� �˻��Ѵ�.

//search
int cmp_search_count = 0; //�˻��� ���ڿ� �� ���� Ƚ�� | Total number of comparison: 