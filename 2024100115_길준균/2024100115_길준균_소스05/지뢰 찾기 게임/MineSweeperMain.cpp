#include "MineSweeper.h"
void main()
{
    int total;
    loadRanking("MineRanking.bin");
    while (true)
    {
        system("cls");
        printf("  <Mine Sweeper>\n");
        printf("  매설할 총 지뢰의 개수 입력 (81미만): ");
        scanf_s("%d", &total, sizeof(total));
        if (total < 81)
        {
            playMineSweeper(total);
            break;
        }
    }
    printRanking();
    storeRanking("MineRanking.bin");
}