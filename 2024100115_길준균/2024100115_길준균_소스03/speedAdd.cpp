#include "speedAdd.h"
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace chrono;

static double Score = 0;
static double tElapsed = 0;

bool playAdd() {
    int a = rand() % 90 + 10;
    int b = rand() % 90 + 10;
    int answer;

    cout << "문제: " << a << " + " << b << " = ";
    cin >> answer;

    return (answer == a + b);
}
double playSpeedAdd(int count) {
    int correct = 0;
    cout << "\n[스피드 덧셈 게임 시작]\n";

    auto t1 = high_resolution_clock::now();
    for (int i = 1; i <= count; i++) {
        cout << "[" << i << "/" << count << "] ";
        if (playAdd()) {
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