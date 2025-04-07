#include "MineSweeper.h"
#define NUM_MVP 10              //랭킹 10위까지
static PlayInfo MVP[NUM_MVP];   //랭킹 배열
static int nMVP = NUM_MVP;      //랭킹 배열 길이

//랭킹 초기화 함수
static void initRanking()
{
    PlayInfo noname = { "Untitled",1000,1000.0,0.0 };
    for (int i = 0; i < nMVP; i++)
    {
        MVP[i] = noname;
    }
}
//랭킹 저장파일에서 정보를 읽는다. 랭킹 배열을 초기화 하는 함수 파일이 없으면 initRanking함수를 호출해 초기화한다.
void loadRanking(const char* filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL)
    {
        initRanking();
    }
    else
    {
        fread(MVP, sizeof(PlayInfo), nMVP, fp);
        fclose(fp);
    }
}
//랭킹을 불러와 파일에 저장
void storeRanking(const char* filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "wb");
    if (fp == NULL)
    {
        return;
    }
    fwrite(MVP, sizeof(PlayInfo), nMVP, fp);
    fclose(fp);
}
//랭킹 출력
void printRanking()
{
    for (int i = 0; i < nMVP; i++)
    {
        printf("[%2d위] %4d  %-16s %5.1f %5.1f\n", i + 1, MVP[i].nMine, MVP[i].name, MVP[i].tElapsed, MVP[i].Score);
    }
}
//랭킹 추가
int addRanking(int total, double tElap, double score)
{
    if (score > MVP[nMVP - 1].Score)
    {
        int pos = nMVP - 1;
        for (; pos > 0; pos--)
        {
            if (score <= MVP[pos - 1].Score)
            {
                break;
            }
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nMine = total;
        MVP[pos].tElapsed = tElap;
        MVP[pos].Score = score;
        printf(" %d위입니다. 이름을 입력하세요: ", pos + 1);
        scanf_s("%s", MVP[pos].name, sizeof(MVP[pos].name));
        return pos + 1;
    }
    return 0;
}