#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <memory.h>
#include <time.h>
#include <ctype.h>
extern void playMineSweeper(int nBomb = 13);

struct PlayInfo
{
	char name[200];      //�÷��̾� �̸�
	int nMine;               //������ ����
	double tElapsed;      //���� �ҿ� �ð�
	double Score;         //���� ����
};

extern void loadRanking(const char* filename);                     //��ŷ ���� �б�
extern void storeRanking(const char* filename);                     //��ŷ ���� ����
extern void printRanking();                                             //��ŷ �����ֱ�
extern int addRanking(int total, double tElap, double score);      //��ŷ �߰�