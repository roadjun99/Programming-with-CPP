#include "MineSweeper.h"
void main()
{
    int total;
    loadRanking("MineRanking.bin");
    while (true)
    {
        system("cls");
        printf("  <Mine Sweeper>\n");
        printf("  �ż��� �� ������ ���� �Է� (81�̸�): ");
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