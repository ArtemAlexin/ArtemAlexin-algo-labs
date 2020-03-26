#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
vector <vector<int> > g;
int gcd(int a, int b) {
	if (a == 0 || b == 0) {
		return a + b;
	}
	return gcd(b, a % b);
}
vector<int> ans;
int buildNumber(vector<bool>& used) {
	int ans = 0;
	for (int i = 0; i < (int)used.size(); i++) {
		ans = ans * 2 + 1 - (int)used[i];
	}
	return ans;
}
int k;
void cntAns(vector<vector<ll> >& dp, vector<int> &values, vector<bool>& used, int& m, int idx) {
	int n = (int)values.size();
	if (m == 0) {
		return;
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			if (gcd(idx, values[i]) >= k) {
				if (dp[buildNumber(used)][i] >= (ll)m) {
					ans.push_back(values[i]);
					used[i] = 1;
					cntAns(dp, values, used, m, values[i]);
					return;
				} else {
					m -= (int)dp[buildNumber(used)][i];
				}
			}
		}
	}
}
int main() {
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
	int n, m;
	cin >> n >> m >> k;
	g.resize(n);
	for (int i = 0; i < n; i++) {
		g[i].resize(n);
	}
	vector<int> values(n);
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		values[i] = a;
	}
	if (n == 1 && m == 1) {
		cout << values[0];
		return 0;
	}
	sort(values.begin(), values.end());
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (gcd(values[i], values[j]) >= k && i != j) {
				g[i][j] = 1;
				g[j][i] = 1;
			}
		}
	}
	vector<vector<ll> > dp((1 << n), vector<ll>(n));
	for (int i = 0; i < n; i++) {
		dp[(1 << (n - i - 1))][i] = 1;
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if ((mask & (1 << (n - i - 1))) > 0) {
				for (int j = 0; j < n; j++) {
					if (j != i && g[i][j] && (mask & (1 << (n - j - 1))) > 0) {
						dp[mask][i] += dp[mask ^ (1 << (n - i - 1))][j];
					}
				}
			}
		}
	}
	vector<bool> used(n);
	cntAns(dp, values, used, m, 0);
	if ((int)ans.size() != n) {
		cout << -1;
	}  else {
		for (auto i : ans) {
			cout << i << " ";
		}
	}
}
