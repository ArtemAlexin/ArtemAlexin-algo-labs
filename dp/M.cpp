#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
int64_t inf = 1e18;
#define ll int64_t
int main() {
	freopen("salesman.in", "r", stdin);
	freopen("salesman.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<vector<ll > > g(n);
	for (int i = 0; i < n; i++) {
		g[i].assign(n, inf);
	}
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		u--; v--;
		g[u][v] = c;
		g[v][u] = c;
	}
	vector<vector<ll> > dp((1 << n));
	for (int i = 0; i < (1 << n); i++) {
		dp[i].assign(n, inf);
	}
	for (int i = 0; i < n; i++) {
		dp[(1 << i)][i] = 0;
	}
	for (int i = 1; i < n; i++) {
		dp[0][i] = inf;
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n; i++) {
				if ((mask & (1 << i)) > 0 && (mask & (1 << j)) > 0 && i != j) {
					dp[mask][j] = min(dp[mask ^ (1 << j)][i] + g[i][j], dp[mask][j]);
				}
			}
		}
	}
	ll mi = inf;
	for (int i = 0; i < n; i++) {
		if (dp[(1 << n) - 1][i] < mi) {
			mi = dp[(1 << n) - 1][i];
		}
	}
	if (mi >= inf) {
		cout << -1;
	} else {
		cout << mi;
	}
}
