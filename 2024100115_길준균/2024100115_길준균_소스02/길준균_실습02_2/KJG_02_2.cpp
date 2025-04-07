// 3
#include <iostream>
using namespace std;
void main() {
	int n;
	double value;
	double sum = 0.0;
	cout << "pi의 근삿값을 구해보겠습니다. 항의 개수를 입력하세요. : ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		value = 1.0 / (4 * i - 3) - 1.0 / (4 * i - 1);
		sum += value;
	}
	cout << "근삿값 : " << 4 * sum << endl;
}