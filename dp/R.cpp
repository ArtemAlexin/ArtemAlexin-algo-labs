# include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int N = 3e3 + 3;

int n, used[N][N];
pair <int, int> par[N][N];

void bfs(int x, int y) {
	queue < pair <int, int> > q;
	q.push(make_pair(x, y));
	used[x][y] = 1;
	par[x][y] = { x, y };
	while (!q.empty()) {
		pair <int, int> p = q.front();
		q.pop();
		for (int i = 0; i <= 9; i++) {
			int tox = p.first + i, toy = (p.second * 10 + i) % n;
			if (tox <= n && !used[tox][toy]) {
				used[tox][toy] = 1;
				par[tox][toy] = { i, p.second };
				q.push(make_pair(tox, toy));
			}
		}
	}
}

int main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	cin >> n;
	bfs(0, 0);
	string ans;
	int o = 0;
	while (n > 0) {
		int x = par[n][o].first;
		ans += char(x + '0');
		o = par[n][o].second;
		n -= x;
	}
	reverse(ans.begin(), ans.end());
	cout << ans << endl;
}
