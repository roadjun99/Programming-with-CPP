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
        printf("\n\n������ �������� 0�� ��������.\n");
        printf("replay�� ���÷��� 1�� ��������\n");
        printf("�ٽ� �����Ϸ��� ( 0 , 1 )�� ������ �ƹ�Ű�� ��������.\n");
        printf("Ű�� �Է��ϼ��� : ");
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