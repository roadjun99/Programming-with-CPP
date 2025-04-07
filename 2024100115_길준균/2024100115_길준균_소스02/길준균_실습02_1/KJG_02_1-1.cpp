// 1-(1)
#include <iostream>
using namespace std;
void main() {
	int n;
	cout << "³ôÀÌ : ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			cout << "  " << j;
		}
		cout << endl;
	}
}