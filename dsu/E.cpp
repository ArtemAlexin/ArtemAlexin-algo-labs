#include<iostream>
#include<vector>
using namespace std;
const int N = 2e5 + 3;
struct dsu {
	int p[N], sz[N];
	void init() {
		for (int i = 1; i < N; i++) {
			p[i] = i, sz[i] = 1;
		}
	}
	int f_s(int v) {
		return v == p[v] ? v : p[v] = f_s(p[v]);
	}
	void u_s(int a, int b) {
		a = f_s(a);
		b = f_s(b);
		if (a < b)
			swap(a, b);
		p[b] = a;
	}
};
int n, q;
dsu a, b;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> q;
	a.init();
	b.init();
	while (q--) {
		int tp, x, y;
		cin >> tp >> x >> y;
		if (tp == 1) {
			a.u_s(x, y);
		} else if (tp == 2) {
			x = b.f_s(x);
			while (x < y) {
				b.u_s(x, x + 1);
				a.u_s(x, x + 1);
				x = b.f_s(x);
			}
		} else {
			if (a.f_s(x) == a.f_s(y))
				puts("YES");
			else
				puts("NO");
		}
	}
}
