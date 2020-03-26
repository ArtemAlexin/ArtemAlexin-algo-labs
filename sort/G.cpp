#include<iostream>
#include<vector>
using namespace std;
int n;
unsigned int a, b;
unsigned int st;
void bucket_sort(vector<pair<unsigned int, unsigned int > >& a, unsigned int k) {
	vector<unsigned int> c(st + 1);
	if (k == 0) {
		for (int i = 0; i < n; i++) {
			c[a[i].first]++;
		}
		for (unsigned int i = 1; i < st + 1; i++) {
			c[i] = c[i - 1] + c[i];
		}
		vector<pair<unsigned int , unsigned int> > ans(n);
		for (int i = n - 1; i >= 0; i--) {
			ans[c[a[i].first] - 1] = a[i];
			c[a[i].first]--;
		}
		a = ans;
		return;
	}
	for (int i = 0; i < n; i++) {
		c[a[i].second]++;
	}
	for (unsigned int i = 1; i < st + 1; i++) {
		c[i] = c[i - 1] + c[i];
	}
	vector<pair<unsigned int, unsigned int> > ans(n);
	for (int i = n - 1; i >= 0; i--) {
		ans[c[a[i].second] - 1] = a[i];
		c[a[i].second]--;
	}
	a = ans;
}
void digitsort(vector<pair<unsigned int, unsigned int > >& a) {
	for (int i = 1; i >= 0; i--) {
		bucket_sort(a, i);
	}
}
unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}
unsigned int nextRand32() {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}
int main() {
	int t;
	st = (1 << 16);
	cin >> t >> n;
	cin >> a >> b;
	vector<pair<unsigned int, unsigned int > > a(n);
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < n; j++) {
			unsigned int b = nextRand32();
			a[j].first = b / st;
			a[j].second = b % st;
		}
		digitsort(a);
		unsigned long long sum = 0;
		for (int i = 0; i < n; i++)
			sum += (unsigned long long)(a[i].first * st + a[i].second) * (unsigned long long)(i + 1);
		cout << sum << '\n';
	}
}
