// 3
#include <iostream>
using namespace std;
void main() {
	int n;
	double value;
	double sum = 0.0;
	cout << "pi�� �ٻ��� ���غ��ڽ��ϴ�. ���� ������ �Է��ϼ���. : ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		value = 1.0 / (4 * i - 3) - 1.0 / (4 * i - 1);
		sum += value;
	}
	cout << "�ٻ� : " << 4 * sum << endl;
}