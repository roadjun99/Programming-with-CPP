// 4
#include <iostream>
#include <conio.h>
#include <string>
#include <cmath>
using namespace std;
int calculateScore(int n, int Tr) {
    int length = to_string(n).length();// ������ �ڸ��� ���
    int baseScore = 0;
    // �ڸ����� �⺻ ���� ����
    if (length == 1) baseScore = 50;
    else if (length == 2) baseScore = 100;
    else if (length == 3) baseScore = 150;
    else baseScore = 200; // 4�ڸ� �̻�
    int finalScore = baseScore - (Tr * 5);
    return max(finalScore, 0); // ������ 0 ���Ϸ� �������� �ʵ��� ����. ���̳ʽ� ������ ������ ��ó���� �ſ���..
}
int main() {
    string input;
    int n, t;
    char ch;
    cout << "���� �Է� : ";
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
    int numDigits = input.length(); // ������ �ڸ��� ���
    int min = 0;
    int max = pow(10, numDigits); // 10^�ڸ���
    cout << endl << "���ڸ� ����������! (����: " << min << " ~ " << max << ") : ";
    cin >> t;
    int Tr = 1;
    while (t != n) {
        if (t > n) {
            max = t;
            cout << "��! " << t << "���� �۽��ϴ�. (���ο� ����: " << min << " ~ " << max << ") : ";
        }
        else {
            min = t;
            cout << "��! " << t << "���� Ů�ϴ�. (���ο� ����: " << min << " ~ " << max << ") : ";
        }
        Tr++;
        cin >> t;
        cout << endl;
    }
    int score = calculateScore(n, Tr);
    cout << "����! " << Tr << "�� ���� �����̽��ϴ�!" << endl;
    cout << "���� ��� ���: �⺻ ���� - (�õ� Ƚ�� �� 5)" << endl;
    cout << "���� ����: " << score << " ��" << endl;
}