#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int > > p;
int find(int n) {
	if (p[n].first == n) {
		return n;
	} else {
		return p[n].first = find(p[n].first);
	}
}
void unite(int i, int j) {
	int ui = find(i);
	int uj = find(j);
	if (ui == uj) {
		return;
	}
	p[ui].first = uj;
	int m = min(p[ui].second, p[uj].second);
	p[ui].second = m;
}
int main() {
	int n;
	cin >> n;
	p.resize(n);
	for (int i = 0; i < n; i++) {
		p[i] = { i, i };
	}
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		a--;
		int b = find(a);
		cout << b + 1 << " ";
		unite(b, (b + 1) % n);
	}
}
