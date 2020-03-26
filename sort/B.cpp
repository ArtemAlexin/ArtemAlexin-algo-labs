#include<iostream>
#include<vector>
using namespace std;
pair<int, int> bins(vector<int>& a, int x) {
	int l = -1;
	int r = int(a.size());
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (a[mid] >= x) {
			r = mid;
		} else {
			l = mid;
		}
	}
	int ansl = r;
	if (!(ansl < int(a.size()) && a[ansl] == x)) {
		ansl = -2;
		l = -2;
	} else {
		l = -1;
		r = int(a.size());
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (a[mid] <= x) {
				l = mid;
			} else {
				r = mid;
			}
		}
	}
	if (!(l > -1 && a[l] == x)) {
		l = -2;
		ansl = -2;
	}
	return {ansl + 1, l + 1};
}
int main() {
	vector<int> a;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		a.push_back(k);
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		pair<int, int> p = bins(a, x);
		cout << p.first << " " << p.second << endl;
	}
}
