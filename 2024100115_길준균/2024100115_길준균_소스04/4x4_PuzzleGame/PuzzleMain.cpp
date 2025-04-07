#include "Ranking.h"
extern int playFifteenPuzzle();
void main()
{
    char num;
    while (true)
    {
        loadRanking("ranking.bin");
        int rank = playFifteenPuzzle();
        printRanking();
        storeRanking("ranking.bin");
        printf("\n\n게임을 끝내려면 0을 누르세요.\n");
        printf("replay를 보시려면 1을 누르세요\n");
        printf("다시 시작하려면 ( 0 , 1 )을 제외한 아무키나 누르세요.\n");
        printf("키를 입력하세요 : ");
        num = _getche();
        if (num == '0')
        {
            break;
        }
        else if (num == '1')
        {
            ReplayShuffle();
            break;
        }
        else
        {
            continue;
        }
    }
}