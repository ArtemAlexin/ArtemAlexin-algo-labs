#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
vector<vector<ll> > dp;
vector<ll> values;
vector<ll> sums;
vector<vector<int> > p;
vector<string> codes;
ll f(int i, int j) {
	if (i < 0 || i >(int)dp.size() || j < 0 || j >(int)dp[i].size()) return 0;
	if (dp[i][j] >= 0) {
		return dp[i][j];
	}
	ll val = 1e18;
	for (int t = i; t < j; t++) {
		val = min(val, f(i, t) + f(t + 1, j));
	}
	val += (sums[j] - sums[i] + values[i]);
	return dp[i][j] = val;
}
void solve() {
	for (int i = 0; i < (int)dp.size(); i++) {
		for (int j = 0; j < (int)dp.size() - i; j++) {
			if (i + j == j) continue;
			int jj = i + j;
			int ii = j;
			ll val = 1e18;
			int id = -1;
			for (int t = jj > 0 ? p[ii][jj - 1] : i; t <
				(ii + 1 < (int)dp.size() ? min(p[ii + 1][jj] + 1, jj) : jj); t++) {
				if (dp[ii][t] + dp[t + 1][jj] < val) {
					val = dp[ii][t] + dp[t + 1][jj];
					id = t;
				}
				// val = min(val, dp[ii][t] + dp[t + 1][jj]);
			}
			p[ii][jj] = id;
			val += (sums[jj] - sums[ii] + values[ii]);
			dp[ii][jj] = val;
		}
	}
}
void reb(int i, int j) {
	if (i == j) return;
	int idx = -1;
	for (int t = i; t < j; t++) {
		if (dp[i][t] + dp[t + 1][j] + sums[j] - sums[i] + values[i] == dp[i][j]) {
			idx = t;
			break;
		}
	}
	for (int k = i; k <= j; k++) {
		codes[k].push_back(idx < k ? '1' : '0');
	}
	reb(i, idx);
	reb(idx + 1, j);
}
int main() {
	freopen("optimalcode.in", "r", stdin);
	freopen("optimalcode.out", "w", stdout);
	int n;
	cin >> n;
	values.resize(n);
	sums.resize(n);
	codes.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> values[i];
		i == 0 ? sums[i] = values[i] : sums[i] = sums[i - 1] + values[i];
	}
	dp.resize(n);
	p.resize(n);
	for (int i = 0; i < n; i++) {
		dp[i].assign(n, -1);
		dp[i][i] = 0;
		p[i].assign(n, -1);
		p[i][i] = i;
	}
	solve();
	// cout << f(0, n - 1) << endl;
	cout << dp[0][n - 1] << endl;
	reb(0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << codes[i] << endl;
	}
}
