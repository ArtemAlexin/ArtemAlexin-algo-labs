#include<iostream>
#include<cmath>
#include<vector>
using namespace std;
int main() {
	int m, n;
	cin >> n >> m;
	if (m < 17 && m >= 0) {
		for (int i = 0; i < m; i++) {
			cout << 0 << " " << 1 << " " << 1 << " " << endl;
		}
		return 0;
	}
	int t;
	double r = sqrt(m * (log(m) / log(2))) / 4;
	if (r > int(r)) {
		t = int(r) + 1;
	} else {
		t = int(r);
	}
	int now = t + 1;
	int number = 2 * t + 1;
	for (int i = 1; i <= t; i++) {
		cout << "1" << " " << now << " " << i << endl;
	}
	for (int i = 0; i < t + 1; i++) {
		cout << "1 " << i + t + 2 << " " << now << endl;
		for (int i2 = 1; i2 <= t; i2 ++) {
			cout << "0" << " " << i2 << " " << i2 + 1 << endl;
			i2++;
			number++;
		}
		if (number > 2 * t) {
			now = i + t + 2;
		}
	}
	for (int i = 0; i < m - number; i++) {
		cout << 0 << " " << 1 << " " << 1 << " " << endl;
	}
	return 0;
}
