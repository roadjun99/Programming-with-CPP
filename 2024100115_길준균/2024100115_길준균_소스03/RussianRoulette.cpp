#include "RussianRoulette.h"
int playRussianRoulette(int nPlayers, int nBullets, int nChambers) {
    srand((unsigned)time(NULL));

    int remainingBullets = nBullets;
    int currentPlayer = rand() % nPlayers + 1;

    cout << "\n총을 돌렸습니다. " << currentPlayer << "번부터 시작합니다.\n";
    while (remainingBullets > 0) {
        int pos = rand() % nChambers;

        cout << "[" << currentPlayer << "번] 탄창을 무작위로 돌렸습니다.\n";
        cout << "\t엔터를 누르면 격발됩니다...";
        cin.ignore();

        if (pos <= remainingBullets) {
            cout << "\t빵~~~!! " << currentPlayer << "번이 총에 맞았습니다!";
            remainingBullets--;
            nPlayers--;
            cout << "\t현재 생존자는 " << nPlayers << "명입니다.\n";
        }
        else {
            cout << "\t휴~ 살았습니다!\n";
        }

        if (nPlayers == 0) {
            cout << "모든 사람이 죽었습니다. 게임 종료.\n";
            break;
        }
        currentPlayer = (currentPlayer % nPlayers) + 1;

        if (remainingBullets == 0) {
            cout << "총알이 전부 떨어졌습니다. 게임 종료.\n";
            break;
        }
    }
    return 0;
}