#include "RussianRoulette.h"
#include "speedGugu.h"
#include "speedAdd.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 함수 정의
void showGameMenu() {
    srand((unsigned)time(NULL));

    char choice;
    while (true) {
        cout << "\n===== 게임 선택 =====\n";
        cout << "r : 러시안 룰렛\n";
        cout << "* : 스피드 구구단\n";
        cout << "+ : 스피드 덧셈\n";
        cout << "q : 종료\n";
        cout << "선택 >> ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 'r': {
            int players, bullets, chambers;
            cout << "인원 수 입력: ";
            cin >> players;
            cout << "총알 수 입력: ";
            cin >> bullets;
            cout << "탄창 크기 입력: ";
            cin >> chambers;
            cin.ignore();
            playRussianRoulette(players, bullets, chambers);
            break;
        }
        case '*':
            cout << "\n[스피드 구구단 시작]\n";
            playSpeedGugu(5);
            break;
        case '+':
            cout << "\n[스피드 덧셈 시작]\n";
            playSpeedAdd(5);
            break;
        case 'q':
            cout << "게임을 종료합니다.\n";
            return;
        default:
            cout << "잘못된 입력입니다. 다시 선택하세요.\n";
        }
    }
}