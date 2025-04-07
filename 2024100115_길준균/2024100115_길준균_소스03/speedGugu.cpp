#include "speedGugu.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

static double Score = 0;
static double tElapsed = 0;

// 한 자리 곱셈 문제 한 번 출제
bool playGugu() {
    int a = rand() % 8 + 2; // 2~9
    int b = rand() % 8 + 2;
    int answer;

    cout << "문제: " << a << " x " << b << " = ";
    cin >> answer;

    return (answer == a * b);
}
// n번 반복, 처리 시간 측정 및 점수 계산
double playSpeedGugu(int count) {
    int correct = 0;

    cout << "\n[스피드 구구단 게임 시작]\n";

    auto t1 = high_resolution_clock::now();
    for (int i = 1; i <= count; i++) {
        cout << "[" << i << "/" << count << "] ";
        if (playGugu()) {
            cout << "정답!\n";
            correct++;
        }
        else {
            cout << "오답!\n";
        }
    }
    auto t2 = high_resolution_clock::now();
    duration<double> elapsed = t2 - t1;
    tElapsed = elapsed.count();

    if (correct < count) {
        Score = 0.0;
    }
    else {
        Score = 100.0 * (5.0 * count - tElapsed) / (5.0 * count);
        if (Score < 0.0) Score = 0.0;
    }

    cout << fixed << setprecision(2);
    cout << "\n정답 수: " << correct << " / " << count << endl;
    cout << "걸린 시간: " << tElapsed << "초\n";
    cout << fixed << setprecision(1);
    cout << "점수: " << Score << "점\n";

    return Score;
}