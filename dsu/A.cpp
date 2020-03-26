#include<iostream>
#include<vector>
using namespace std;
int n;
bool ok(int i) {
	return i >= 0 && i < n;
}
int main() {
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	for (int i = 0; i < n; i++) {
		if (ok(2 * i + 1)) {
			if (arr[i] > arr[2 * i + 1]) {
				cout << "NO";
				return 0;
			}
		}
		if (ok(2 * i + 2)) {
			if (arr[i] > arr[2 * i + 2]) {
				cout << "NO";
				return 0;
			}
		}
	}
	cout << "YES";
	return 0;
}
