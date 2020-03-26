#include<iostream>
#include<vector>
using namespace std;
#define ll int64_t
const ll p = 999999937;
vector<vector<ll> > matrix(2, vector<ll>(2));
vector<vector<ll> > E(2, vector<ll>(2));
vector<vector<ll> > mult(const vector<vector<ll> >& m, const vector<vector<ll> >& r = matrix) {
	vector<vector<ll> > res(2, vector<ll>(2));
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				res[i][j] += (m[i][k] * r[k][j] % p);
				res[i][j] %= p;
			}
		}
	}
	return res;
}
vector<vector<ll>> bin(vector<vector<ll> >& m, ll n) {
	if (n == 0) {
		return E;
	}
	if (n == 1) {
		return matrix;
	}
	if (n % 2 == 0) {
		vector<vector<ll> > ans = bin(m, n / 2);
		return mult(ans, ans);
	}
	return mult(bin(m, n - 1), matrix);
}
int main() {
	E[0][0] = 1;
	E[0][1] = 0;
	E[0][1] = 0;
	E[1][1] = 1;
	matrix[0][0] = 4;
	matrix[0][1] = 1;
	matrix[1][0] = 1;
	matrix[1][1] = 0;
	ll n;
	cin >> n;
	while (n != 0) {
		n--;
		if (n == 0) {
			cout << 5 << endl;
		} else {
			vector<vector<ll> > t = matrix;
			t = bin(t, n);
			cout << (t[0][0] * 5 % p + t[0][1] % p) % p << endl;
		}
		cin >> n;
	}
}
