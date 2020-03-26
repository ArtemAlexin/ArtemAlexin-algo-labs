#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Node {
	int left;
	int right;
	int cost;
};
vector<int> ans;
int cnt(int i) {
	int k = 0;
	while (i > 0) {
		k += i % 2;
		i /= 2;
	}
	return k;
}
const int inf = 1e6;
void solve(int i, vector<vector<int> >& g, int k) {
	if (cnt(i) == 0) {
		return;
	}
	for (int j = 0; j < k; j++) {
		if (g[i][j] < inf) {
			ans.push_back(j + 1);
			solve(i - (1 << j), g, k);
			return;
		}
	}
}
int main() {
	int n, k;
	cin >> k >> n;
	vector<Node> arr(k);
	for (int i = 0; i < k; i++) {
		int l, r, b;
		cin >> l >> r >> b;
		arr[i] = { l, r, b };
	}
	vector<vector<int> > dp((1 << k));
	for (int i = 0; i < (1 << k); i++) {
		dp[i].assign(k, inf);
	}
	for (int i = 0; i < k; i++) {
		dp[(1 << i)][i] =  n <= arr[i].right && n >= arr[i].left ? n + arr[i].cost : inf;
	}
	for (int i = 1; i < (1 << k); i++) {
		for (int j = 0; j < k; j++) {
			for (int t = 0; t < k; t++) {
				if (t == j)
					continue;
				if (dp[i ^ (1 << j)][t] >= arr[j].left && dp[i ^ (1 << j)][t] <= arr[j].right) {
					dp[i][j] = dp[i ^ (1 << j)][t] + arr[j].cost;
					break;
				}
			}
		}
	}

	int m = -inf;
	int idx = -1;
	for (int i = 1; i < (1 << k); i++) {
		for (int j = 0; j < k; j++) {
			if (cnt(i) > m && dp[i][j] < inf) {
				idx = i;
				m = cnt(i);
			}
		}
	}
	if (m == -inf) {
		cout << 0;
		return 0;
	}
	solve(idx, dp, k);
	cout << m << endl;
	for (int i = int(ans.size()) - 1; i >= 0; i--) {
		cout << ans[i] << " ";
	}
}
