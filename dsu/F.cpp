#include<iostream>
#include<vector>
using namespace std;
vector<int> p;
vector<int> r;
int find(int i) {
	if (p[i] == i) {
		return i;
	}
	return p[i] = find(p[i]);
}
void unite(int u, int v) {
	int i = find(u);
	int j = find(v);
	if (i == j) {
		return;
	}
	if (r[i] <= r[j]) {
		p[i] = j;
		if (r[j] == r[i]) {
			r[j]++;
		}
		return;
	}
	p[j] = i;
}
struct Node {
	string type;
	int u;
	int v;
};
int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
	}
	vector<Node> arr;
	for (int i = 0; i < k; i++) {
		string a;
		int u, v;
		cin >> a >> u >> v;
		u--; v--;
		arr.push_back({ a, u, v });
	}
	p.resize(n);
	for (int i = 0; i < n; i++) {
		p[i] = i;
	}
	r.resize(n);
	vector<string> ans;
	for (int i = arr.size() - 1; i >= 0; i--) {
		if (arr[i].type == "cut") {
			unite(arr[i].u, arr[i].v);
		}
		if (arr[i].type == "ask") {
			if (find(arr[i].u) == find(arr[i].v)) {
				ans.push_back("YES");
			} else {
				ans.push_back("NO");
			}
		}
	}
	for (int i = ans.size() - 1; i >= 0; i--) {
		cout << ans[i] << endl;
	}
}
