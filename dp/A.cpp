#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
struct Node {
	int64_t cost;
	int64_t length;
	int64_t width;
};
struct Node2 {
	int left;
	int middle;
	int right;
};
const int inf = 1e9;
void doIt(vector<vector<Node2> > &parents, vector<string>& ans, pair<int, int> begin) {
	if (parents[begin.first][begin.second].left != parents[begin.first][begin.second].right) {
		Node2 cur = parents[begin.first][begin.second];
		ans[begin.first * 3].push_back('(');
		ans[begin.second * 3 + 2].push_back(')');
		doIt(parents, ans, { cur.left, cur.middle });
		doIt(parents, ans, { cur.middle + 1, cur.right });
	}
}
Node dp(vector<vector<Node> >& f, vector<vector<Node2> >& parents, int i, int j) {
	if (f[i][j].cost != inf) {
		return f[i][j];
	}
	for (int k = 1; k <= j - i; k++) {
		Node simba = dp(f, parents, i, j - k);
		Node simba2 = dp(f, parents, j - k + 1, j);
		int64_t cost = simba.cost + simba2.cost +
			simba.length * simba2.width * simba.width;
		if (cost < f[i][j].cost) {
			parents[i][j] = { i, j - k, j };
			f[i][j] = { cost, simba.length, simba2.width };
			if (k == j - i) {
				return f[i][j];
			}
		} else if (cost == f[i][j].cost && simba.length
			* simba2.width < f[i][j].length * f[i][j].width) {
			parents[i][j] = { i, j - k, j };
			f[i][j] = { cost, simba.length, simba.width };
			if (k == j - i) {
				return f[i][j];
			}
		}
		if (k == j - i) {
			return f[i][j];
		}
	}
	return f[i][j];
}
int main() {
	ifstream in("matrix.in");
	ofstream out("matrix.out");
	int n;
	in >> n;
	vector<vector<Node> > f(n);
	vector<vector<Node2> > parents(n, vector<Node2>(n));
	for (int i = 0; i < n; i++) {
		f[i].assign(n, { inf, i, i });
	}
	for (int i = 0; i < n; i++) {
		int64_t length, width;
		in >> length >> width;
		f[i][i] = { 0, length, width };
		parents[i][i] = { i, i, i };
	}
	dp(f, parents, 0, n - 1);
	vector<string> ans(3 * n);
	for (int i = 1; i < 3 * n; i += 3) {
		ans[i] = "A";
		ans[i - 1] = "";
		ans[i + 1] = "";
	}
	pair<int, int> begin = { 0, n - 1 };
	doIt(parents, ans, begin);
	for (int i = 0; i < 3 * n; i++) {
		out << ans[i];
	}
}
