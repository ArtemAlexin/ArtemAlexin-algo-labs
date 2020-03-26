#include<iostream>
#include<vector>
using namespace std;
vector <int> d, read;
vector<int> number;
int curt;
int getParrent(int i) {
	if (i != d[i]) {
		int th = d[i];
		d[i] = getParrent(d[i]);
		if (d[th] != th)
			number[i] += number[th];
	}
	return d[i];
}
void unite(int i, int j) {
	int v = getParrent(i);
	int u = getParrent(j);
	d[v] = u;
}
int64_t zerg = 0ll, p = 1e+6 + 3ll;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	d.resize(n + m);
	number.resize(n + m);
	read.resize(n);
	for (int i = 0; i < n + m; i++) {
		d[i] = i;
	}
	curt = n;
	for(int k = 0; k < m; k++) {
		int type, i, j;
		cin >> type;
		if (type == 1) {
			cin >> i;
			i = (i + (int)zerg) % n;
			number[getParrent(i)]++;
			zerg = (30 * zerg + 239) % p;
		}
		if (type == 2) {
			cin >> i >> j;
			i = (i + (int)zerg) % n;
			j = (j + (int)zerg) % n;
			if (getParrent(i) == getParrent(j)) {
				continue;
			}
			unite(j, curt);
			unite(i, curt);
			curt++;
			zerg = (13 * zerg + 11) % p;
		}
		if (type == 3) {
			int s;
			cin >> i;
			i = (i + (int)zerg) % n;
			getParrent(i);
			s = number[i];
			if (d[i] != i)
				s += number[d[i]];
			int q = s - read[i];
			read[i] = s;
			cout << q << '\n';
			zerg = ((int64_t)100500 * zerg + q) % p;
		}
	}
	return 0;
}
