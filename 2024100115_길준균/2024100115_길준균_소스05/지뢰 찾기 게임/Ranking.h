#pragma once
#include <stdio.h>
#define MAX_RANK 10
struct PlayInfo {
    char name[64];
    int nBomb;         // 매설된 지뢰 수
    double time;       // 소요 시간
    double score;      // 최종 점수
};
// 랭킹 관리 함수들
void loadRanking(const char* filename);
void storeRanking(const char* filename);
int addRanking(int nBomb, double tElapsed);
void printRanking();