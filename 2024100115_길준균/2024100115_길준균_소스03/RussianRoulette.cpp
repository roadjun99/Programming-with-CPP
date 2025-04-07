#include "RussianRoulette.h"
int playRussianRoulette(int nPlayers, int nBullets, int nChambers) {
    srand((unsigned)time(NULL));

    int remainingBullets = nBullets;
    int currentPlayer = rand() % nPlayers + 1;

    cout << "\n���� ���Ƚ��ϴ�. " << currentPlayer << "������ �����մϴ�.\n";
    while (remainingBullets > 0) {
        int pos = rand() % nChambers;

        cout << "[" << currentPlayer << "��] źâ�� �������� ���Ƚ��ϴ�.\n";
        cout << "\t���͸� ������ �ݹߵ˴ϴ�...";
        cin.ignore();

        if (pos <= remainingBullets) {
            cout << "\t��~~~!! " << currentPlayer << "���� �ѿ� �¾ҽ��ϴ�!";
            remainingBullets--;
            nPlayers--;
            cout << "\t���� �����ڴ� " << nPlayers << "���Դϴ�.\n";
        }
        else {
            cout << "\t��~ ��ҽ��ϴ�!\n";
        }

        if (nPlayers == 0) {
            cout << "��� ����� �׾����ϴ�. ���� ����.\n";
            break;
        }
        currentPlayer = (currentPlayer % nPlayers) + 1;

        if (remainingBullets == 0) {
            cout << "�Ѿ��� ���� ���������ϴ�. ���� ����.\n";
            break;
        }
    }
    return 0;
}