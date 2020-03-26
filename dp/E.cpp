#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
using namespace std;
#define cin in
#define cout out
int main() {
	ifstream in("levenshtein.in");
	ofstream out("levenshtein.out");
	string s1;
	string s2;
	cin >> s1;
	cin >> s2;
	vector<vector<int> > f(int(s1.size() + 1), vector<int>(int(s2.size() + 1)));
	f[0][0] = 0;
	for (int i = 1; i <= int(s1.size()); i++) {
		f[i][0] = f[i - 1][0] + 1;
	}
	for (int i = 1; i <= int(s2.size()); i++) {
		f[0][i] = f[0][i - 1] + 1;
	}
	for (int i = 1; i <= int(s1.size()); i++) {
		for (int j = 1; j <= int(s2.size()); j++) {
			if (s1[i - 1] == s2[j - 1]) {
				f[i][j] = f[i - 1][j - 1];
			} else {
				f[i][j] = min(f[i - 1][j], min(f[i][j - 1], f[i - 1][j - 1])) + 1;
			}
		}
	}
	cout << f[int(s1.size())][int(s2.size())];
}
