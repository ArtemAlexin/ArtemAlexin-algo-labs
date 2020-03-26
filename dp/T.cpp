#include<iostream>
#include<vector>
#include<cstdio>
#include<map>

using namespace std;

const int N = 3e5 + 2;

int n;
long long cnt[N], dw[N], up[N];
vector <int> g[N];
map < pair <int, int>, long long > mp;

void dfs_cnt(int v, int pr = 0) {
	cnt[v] = 1;
	for (int to : g[v]) {
		if (to == pr)
			continue;
		dfs_cnt(to, v);
		cnt[v] += cnt[to];
	}
}

void dfs_dw(int v, int pr = 0) {
	dw[v] = cnt[v];
	for (int to : g[v]) {
		if (to == pr)
			continue;
		dfs_dw(to, v);
		dw[v] += dw[to];
	}
}

void dfs_up(int v, int pr = 0) {
	up[v] += up[pr] + (n - cnt[v]);
	long long sum = 0;
	for (int to : g[v]) {
		if (to == pr)
			continue;
		sum += dw[to];
	}
	for (int to : g[v]) {
		if (to == pr)
			continue;
		up[to] = sum - dw[to];
		dfs_up(to, v);
	}
	long long ret = dw[v] * (n - cnt[v]) + cnt[v] * (up[v] - (n - cnt[v]));
	mp[{pr, v}] = mp[{v, pr}] = ret;
}

int main() {
	freopen("treedp.in", "r", stdin);
	freopen("treedp.out", "w", stdout);
	cin >> n;
	vector < pair <int, int> > e;
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
		e.emplace_back(u, v);
	}
	dfs_cnt(1);
	dfs_dw(1);
	dfs_up(1);
	for (int i = 0; i < (int)e.size(); i++) {
		printf("%lld\n", mp[e[i]]);
	}
}
