#pragma once
#include <stdio.h>
#define MAX_RANK 10
struct PlayInfo {
    char name[64];
    int nBomb;         // �ż��� ���� ��
    double time;       // �ҿ� �ð�
    double score;      // ���� ����
};
// ��ŷ ���� �Լ���
void loadRanking(const char* filename);
void storeRanking(const char* filename);
int addRanking(int nBomb, double tElapsed);
void printRanking();