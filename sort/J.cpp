#include<iostream>
#include<vector>
using namespace std;
unsigned long long ans = 0;
long long k;
unsigned long long merge(vector<long long>& a, unsigned int l, unsigned int m, unsigned int r) {
	unsigned int i = l;
	unsigned long long sum = 0;
	unsigned int j = m;
	while (i < m && j < r) {
		if (a[i] > a[j] - k) {
			j++;
		}  else {
			sum += int64_t((r - j));
			i++;
		}
	}
	i = l;
	j = m;
	vector<long long> t;
	while (i < m && j < r) {
		if (a[i] < a[j]) {
			t.push_back(a[i]);
			i++;
		} else {
			t.push_back(a[j]);
			j++;
		}
	}
	if (i >= m) {
		while (j < r) {
			t.push_back(a[j]);
			j++;
		}
	}
	if (j >= r) {
		while (i < m) {
			t.push_back(a[i]);
			i++;
		}
	}
	for (unsigned int z = l; z < r; z++) {
		a[z] = t[z - l];
	}
	return sum;
}
void merge_sort(vector<long long>& a, unsigned int l, unsigned int r) {
	if (r - l == 1) {
		if (a[l] >= k) {
			ans++;
		}
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
unsigned int nextRand32() {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}
int main() {
	cin >> n >> k;
	cin >> a >> b;
	vector<int> arr(n);
	for (int i = 0; i < int(n); i++) {
		arr[i] = int(nextRand32());
	}
	vector<long long> sum(n);
	sum[0] = int64_t(arr[0]);
	for (int i = 1; i < int(n); i++) {
		sum[i] = sum[i - 1] + arr[i];
	}
	merge_sort(sum, 0, int(sum.size()));
	cout << ans;
}
