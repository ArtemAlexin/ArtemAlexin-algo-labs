#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
vector<ll> dp1;
vector<ll> dp2;
void dfs(vector<vector<pair<int, ll > > >& g, vector<bool>& used, int cur, int par) {
	used[cur] = 1;
	for (auto v : g[cur]) {
		if (v.first != par && !used[v.first]) {
			dfs(g, used, v.first, cur);
		}
	}
	ll sum = 0;
	for (auto v : g[cur]) {
		if (v.first != par) {
			sum += max(dp1[v.first], dp2[v.first]);
		}
	}
	for (auto v : g[cur]) {
		if (v.first != par) {
			dp1[cur] = max(dp2[v.first] + v.second + sum - max(dp1[v.first], dp2[v.first]), dp1[cur]);
		}
	}
	dp2[cur] = sum;
}
int main() {
	freopen("matching.in", "r", stdin);
	freopen("matching.out", "w", stdout);
	int n;
	cin >> n;
	vector<vector<pair<int, ll> > > g(n);
	for (int i = 0; i < n - 1; i++) {
		long long cost;
		int u, v;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({ v, cost });
		g[v].push_back({ u, cost });
	}
	vector<bool> used(n, 0);
	dp2.resize(n);
	dp1.resize(n);
	dfs(g, used, 0, 0);
	cout << max(dp1[0], dp2[0]);
}
