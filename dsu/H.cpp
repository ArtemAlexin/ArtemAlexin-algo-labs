#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int color, offset;
vector <int> ran;
vector <int> d;
vector <int> h;
int getParent(int v) {
	while (v != d[v]) {
		color ^= ran[v];
		v = d[v];
	}
	color ^= ran[v];
	return d[v];
}
void doIt(int& tmp) {
	color = 0;
	tmp = getParent(tmp);
}
void unite(int v, int u) {
	int v2 = v, u2 = u;
	doIt(v2);
	int c1 = color;
	doIt(u2);
	int c2 = color;
	if (v2 == u2)
		return;

	if (h[u2] > h[v2])
		swap(v2, u2);
	h[v2] += h[u2];
	if (c1 == c2) {
		ran[u2] ^= 1;
	}
	d[u2] = v2;
}
int main() {
	int n, m, type, a, b;
	cin >> n >> m;
	d.resize(n);
	for (int i = 0; i < n; i++)
		d[i] = i;
	ran.resize(n);
	h.assign(n, 1);
	for (int i = 0; i < m; i++) {
		cin >> type >> a >> b;
		switch (type) {
		case 1:
			b = (b + offset) % n;
			a = (a + offset) % n;
			doIt(a);
			a = color;
			doIt(b);
			b = color;
			if (a == b) {
				offset = (offset + 1) % n;
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
			break;
		case 0:
			b = (b + offset) % n;
			a = (a + offset) % n;
			unite(a, b);
			break;
		}
	}
	return 0;
}
