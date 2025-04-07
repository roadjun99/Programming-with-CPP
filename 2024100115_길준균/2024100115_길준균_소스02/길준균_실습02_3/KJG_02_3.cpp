// 4
#include <iostream>
#include <conio.h>
#include <string>
#include <cmath>
using namespace std;
int calculateScore(int n, int Tr) {
    int length = to_string(n).length();// 숫자의 자릿수 계산
    int baseScore = 0;
    // 자릿수별 기본 점수 설정
    if (length == 1) baseScore = 50;
    else if (length == 2) baseScore = 100;
    else if (length == 3) baseScore = 150;
    else baseScore = 200; // 4자리 이상
    int finalScore = baseScore - (Tr * 5);
    return max(finalScore, 0); // 점수가 0 이하로 내려가지 않도록 보장. 마이너스 점수를 받으면 상처받을 거예요..
}
int main() {
    string input;
    int n, t;
    char ch;
    cout << "숫자 입력 : ";
    while (true) {
        ch = _getch();
        if (ch == 13) {
            break;
        }
        if (isdigit(ch)) {
            input += ch;
            cout << "*";
        }
    }
    n = stoi(input);
    int numDigits = input.length(); // 숫자의 자릿수 계산
    int min = 0;
    int max = pow(10, numDigits); // 10^자릿수
    cout << endl << "숫자를 맞혀보세요! (범위: " << min << " ~ " << max << ") : ";
    cin >> t;
    int Tr = 1;
    while (t != n) {
        if (t > n) {
            max = t;
            cout << "땡! " << t << "보다 작습니다. (새로운 범위: " << min << " ~ " << max << ") : ";
        }
        else {
            min = t;
            cout << "땡! " << t << "보다 큽니다. (새로운 범위: " << min << " ~ " << max << ") : ";
        }
        Tr++;
        cin >> t;
        cout << endl;
    }
    int score = calculateScore(n, Tr);
    cout << "정답! " << Tr << "번 만에 맞히셨습니다!" << endl;
    cout << "점수 계산 방식: 기본 점수 - (시도 횟수 × 5)" << endl;
    cout << "최종 점수: " << score << " 점" << endl;
}