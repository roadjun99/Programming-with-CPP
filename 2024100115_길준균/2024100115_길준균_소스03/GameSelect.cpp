#include "RussianRoulette.h"
#include "speedGugu.h"
#include "speedAdd.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// �Լ� ����
void showGameMenu() {
    srand((unsigned)time(NULL));

    char choice;
    while (true) {
        cout << "\n===== ���� ���� =====\n";
        cout << "r : ���þ� �귿\n";
        cout << "* : ���ǵ� ������\n";
        cout << "+ : ���ǵ� ����\n";
        cout << "q : ����\n";
        cout << "���� >> ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 'r': {
            int players, bullets, chambers;
            cout << "�ο� �� �Է�: ";
            cin >> players;
            cout << "�Ѿ� �� �Է�: ";
            cin >> bullets;
            cout << "źâ ũ�� �Է�: ";
            cin >> chambers;
            cin.ignore();
            playRussianRoulette(players, bullets, chambers);
            break;
        }
        case '*':
            cout << "\n[���ǵ� ������ ����]\n";
            playSpeedGugu(5);
            break;
        case '+':
            cout << "\n[���ǵ� ���� ����]\n";
            playSpeedAdd(5);
            break;
        case 'q':
            cout << "������ �����մϴ�.\n";
            return;
        default:
            cout << "�߸��� �Է��Դϴ�. �ٽ� �����ϼ���.\n";
        }
    }
}