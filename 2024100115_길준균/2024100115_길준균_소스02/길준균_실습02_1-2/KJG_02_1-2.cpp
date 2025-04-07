// 1-(4)
#include <iostream>
using namespace std;
void main() {
	int n;
	cout << "³ôÀÌ : ";
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < n - i; j++) {
			cout << "  ";
		}
		for (int k = i; k >= 2; k--) {
			cout << k << " ";
		}
		for (int l = 1; l <= i; l++) {
			cout << l << " ";
		}
		cout << endl;
	}
}