#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const long long h = (long long)(1e18);
int main() {
	int m;
	long long n;
	cin >> n >> m;
	cout << "? 1" << endl;
	long long a;
	cin >> a;
	if (a == n) {
		cout << "! 1" << endl;
		return 0;
	}
	n -= (a - 1);
	if (n <= 0) {
		n += h;
	}
	long long  l = max(n - m, 0ll);
	long long r = min(n + 1, h - m + 1);
	while (r - l > 1) {
		long long mid = (l + r) / 2;
		cout << "? " << mid << endl;
		long long t;
		cin >> t;
		t -= (a - 1);
		if (t <= 0) {
			t += h;
		}
		if (t == n) {
			cout << "! " << mid << endl;
			return 0;
		}
		if (t > n) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	if (l == r) {
		cout << "! -1" << endl;
		return 0;
	}
	cout << "? " << l << endl;
	long long t;
	cin >> t;
	t -= (a - 1);
	if (t <= 0) {
		t += h;
	}
	if (t == n) {
		cout << "! " << l << endl;
		return 0;
	}
	cout << "! -1" << endl;
}
