#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int> > dp(2);
int ok(int i, int j) {
	return i >= 0 && i < 2 && j >= 0 && j < int(dp[i].size()) ?  dp[i][j] : 0;
}
int main() {
	string s1, s2;
	s1.push_back(' ');
	s2.push_back(' ');
	string tmp;
	cin >> tmp;
	s1.append(tmp);
	tmp.clear();
	cin >> tmp;
	s2.append(tmp);
	for (int i = 0; i < 2; i++) {
		dp[i].resize(s1.size());
	}
	dp[0][0] = 1;
	for (int i = 1; i < int(dp[0].size()); i++) {
		if (s1[i] == '*') dp[0][i] = dp[0][i - 1];
	}
	for (int i = 1; i < int(s2.size()); i++) {
		for (int j = 0; j < int(s1.size()); j++) {
			if (s1[j] == s2[i] || s1[j] == '?') {
				dp[1][j] = ok(0, j - 1);
			} else if (s1[j] == '*') {
				dp[1][j] = max(ok(0, j), ok(1, j - 1));
			} else {
				dp[1][j] = 0;
			}
		}
		swap(dp[0], dp[1]);
	}
	dp[0][s1.size() - 1] == 1 ? cout << "YES" : cout << "NO";
}
