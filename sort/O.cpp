#include<iostream>
#include<vector>
using namespace std;
bool check(vector<int>& arr) {
	bool incr = true;
	for (int i = 1; i < int(arr.size()); i++) {
		if (arr[i] >= arr[i - 1]) {
			continue;
		} else {
			incr = false;
			break;
		}
	}
	return  incr;
}
int main() {
	int n;
	do {
		cin >> n;
		if (n == 0) {
			return 0;
		}
		int firstidx = -1;
		int sum = 0;
		vector<int> web(n);
		vector<pair<int, int> > ans;
		for (int i = 0; i < n; i++) {
			cin >> web[i];
			if (web[i] == 1 && firstidx < 0) {
				firstidx = i;
			}
			sum += web[i];
		}
		if (check(web)) {
			cout << -1 << endl;
		} else {
			for (int i = 0; i < n; i++) {
				if (i != firstidx && web[i] == 1) {
					ans.push_back({ firstidx, i });
				}
			}
			for (int i = 0; i < n; i++) {
				if (i == firstidx) {
					continue;
				}
				for (int j = i + 1; j < n; j++) {
					if (j == firstidx) {
						continue;
					}
					ans.push_back({ i, j });
				}
			}
			int i = firstidx;
			for (i = firstidx + 1; i < n - sum; i++) {
				ans.push_back({ firstidx, i });
				firstidx = i;
			}
			if (i == firstidx + 1)
				i = firstidx;
			for (; i > 0; i--) {
				ans.push_back({ i - 1, i });
			}
			cout << ans.size() << endl;
			for (int i = 0; i < int(ans.size()); i++) {
				cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
			}
		}
	} while (1);
}
