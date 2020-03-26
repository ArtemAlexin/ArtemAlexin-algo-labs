#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
#define cin in
#define cout out
const int inf = 1e9;
vector<int> ans;
void findAnswer(vector<vector<int> >& f, vector<int> &w, int k, int s) {
	if (f[k][s] == 0) {
		return;
	}
	if (f[k][s] == f[k - 1][s]) {
		findAnswer(f, w, k - 1, s);
	} else {
		findAnswer(f, w, k - 1, s - w[k]);
		ans.push_back(k);
	}
}
int main() {
	ifstream in("knapsack.in");
	ofstream out("knapsack.out");
	int n, m;
	cin >> n >> m;
	vector<int> c(n + 1);
	vector<int> w(n + 1);
	vector<vector<int> > f(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		f[i][0] = 0;
	}
	for (int i = 0; i <= m; i++) {
		f[0][i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	for (int k = 1; k <= n; k++) {
		for (int s = 1; s <= m; s++) {
			if (s < w[k]) {
				f[k][s] = f[k - 1][s];
			} else {
				f[k][s] = max(f[k - 1][s], f[k - 1][s - w[k]] + c[k]);
			}
		}
	}
	findAnswer(f, w, n, m);
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i << " ";
	}
}
