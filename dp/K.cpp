#include<iostream>
#include<vector>
#include<string>
using namespace std;
#define ll int64_t
const ll p = 1e9;
vector<vector<ll> > f;
vector<ll> s;
ll dp(int i, int j) {
	if (i < 0 || i >= int(f.size()) || j < 0 || j > int(f[i].size()) || i > j) {
		return 0;
	}
	if (f[i][j] >= 0) {
		return f[i][j];
	}
	if (s[i] == s[j]) {
		return f[i][j] = (dp(i + 1, j) + dp(i, j - 1) + 1) % p;
	} else {
		return f[i][j] = (dp(i + 1, j) % p + dp(i, j - 1) % p - dp(i + 1, j - 1) % p + p) % p;
	}
}
int main() {
	int n;
	cin >> n;
	f.resize(n);
	s.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	for (int i = 0; i < n; i++) {
		f[i].assign(n, -1);
	}
	for (int i = 0; i < n; i++) {
		f[i][i] = 1ll;
	}
	dp(0, n - 1);
	cout << f[0][n - 1];
}
