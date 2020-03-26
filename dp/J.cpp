#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> calcNOP(vector<char>& a1, vector<char>& a2) {
	int s1 = (int)a1.size() + 1;
	int s2 = (int)a2.size() + 1;
	vector<vector<int> > NOP(2, vector<int>(s2));
	for (int i = 1; i < s1; i++) {
		NOP[1][0] = 0;
		for (int j = 1; j < s2; j++) {
			NOP[0][j] = NOP[1][j];
			if (a1[i - 1] == a2[j - 1]) {
				NOP[1][j] = NOP[0][j - 1] + 1;
			} else {
				if (NOP[0][j] <= NOP[1][j - 1]) {
					NOP[1][j] = NOP[1][j - 1];
				} else {
					NOP[1][j] = NOP[0][j];
				}
			}
		}
	}
	return NOP[1];
}
vector<char> ans;
void solve(vector<char>& x, vector<char>& y) {
	if ((int)y.size() <= 0) return;
	if (x.size() == 1) {
		if (find(y.begin(), y.end(), x[0]) != y.end()) {
			ans.push_back(x[0]);
			return;
		} else {
			return;
		}
	}
	int mid = (int)x.size() / 2;
	vector<char> x2(mid);
	copy(x.begin(), x.begin() + mid, x2.begin());
	vector<char> x3((int)x.size() - mid);
	copy(x.begin() + mid, x.end(), x3.begin());
	vector<char> y3((int)y.size());
	copy(y.begin(), y.end(), y3.begin());
	vector<int> f = calcNOP(x2, y);
	reverse(x3.begin(), x3.end());
	reverse(y3.begin(), y3.end());
	vector<int> s = calcNOP(x3, y3);
	int max = s[0];
	int partition = -1;
	reverse(s.begin(), s.end());
	for (int i = 0; i <= (int)y.size(); i++) {
		if (f[i] + s[i] > max) {
			max = f[i] + s[i];
			partition = i;
		}
	}
	if (partition != -1) {
		partition--;
	}
	if (s[(int)y3.size()] > max) {
		partition = (int)y3.size() - 1;
	}
	vector<char> yr1(partition + 1);
	if (partition != -1) {
		copy(y.begin(), y.begin() + partition + 1, yr1.begin());
	}
	vector<char> yr2((int)y.size() - partition - 1);
	copy(y.begin() +  1 + partition, y.end(), yr2.begin());
	solve(x2, yr1);
	reverse(x3.begin(), x3.end());
	solve(x3, yr2);
}
int main() {
	vector<char> x;
	vector<char> y;
	string s1, s2;
	cin >> s1 >> s2;
	x.resize((int)s1.size());
	for (int i = 0; i < (int)s1.size(); i++) {
		x[i] = s1[i];
	}
	y.resize((int)s2.size());
	for (int i = 0; i < (int)y.size(); i++) {
		y[i] = s2[i];
	}
	solve(x, y);
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i];
	}
}
