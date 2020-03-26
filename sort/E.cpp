#include<iostream>
#include<vector>
#include<string>
using namespace std;
void bucket_sort(vector<string>& a, vector<int>& c, int k) {
	vector<string> b(int(a.size()));
	for (int i = 0; i < int(a.size()); i++) {
		c[a[i][k] - 'a']++;
	}
	for (int i = 1; i < int(c.size()); i++) {
		c[i] = c[i] + c[i - 1];
	}
	for (int i = int(a.size() - 1); i >= 0; i--) {
		b[c[a[i][k] - 'a'] - 1] = a[i];
		c[a[i][k] - 'a' ]--;
	}
	a = b;
}
void digit_sort(vector<string>& a, int k, int size) {
	int t = size - 1;
	for (int i = 0; i < k; i++) {
		vector<int> c(26);
		bucket_sort(a, c, t);
		t--;
	}
}
int main() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<string> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	digit_sort(a, k, m);
	for (int i = 0; i < int(a.size()); i++) {
		cout << a[i] << endl;
	}
}
