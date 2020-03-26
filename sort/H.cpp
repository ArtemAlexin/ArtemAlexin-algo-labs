#include<iostream>
#include<vector>
using namespace std;
unsigned long long ans = 0;
unsigned long long merge(vector<unsigned int>& a, unsigned int l, unsigned int m, unsigned int r) {
	unsigned int i = l;
	unsigned long long sum = 0;
	unsigned int j = m;
	vector<unsigned int> c;
	while (i < m && j < r) {
		if (a[i] < a[j]) {
			c.push_back(a[i]);
			i++;
		} else if (a[i] == a[j]) {
			c.push_back(a[i]);
			i++;
		} else {
			c.push_back(a[j]);
			sum += int64_t((m - i));
			j++;
		}
	}
	while (i < m) {
		c.push_back(a[i]);
		i++;
	}
	while (j < r) {
		c.push_back(a[j]);
		j++;
	}
	for (unsigned int k = l; k < r; k++) {
		a[k] = c[k - l];
	}
	return sum;
}
void merge_sort(vector<unsigned int>& a, unsigned int l, unsigned int r) {
	if (r - l == 1) {
		return;
	}
	unsigned int mid = (l + r) / 2;
	merge_sort(a, l, mid);
	merge_sort(a, mid, r);
	ans += int64_t(merge(a, l, mid, r));
}
unsigned int n;
unsigned int a, b;
unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}
int main() {
	unsigned int m;
	cin >> n >> m;
	cin >> a >> b;
	vector<unsigned int> arr(n);
	for (unsigned int i = 0; i < n; i++) {
		arr[i] = nextRand24() % m;
	}
	merge_sort(arr, 0, n);
	cout << ans;
}
