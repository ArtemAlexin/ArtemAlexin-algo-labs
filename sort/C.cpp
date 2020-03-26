#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;
int partition(vector<int> &a, int l, int r) {
	int x = rand() % (r - l + 1) + l;
	int i = l;
	int j = r;
	while (i <= j) {
		while (i <= r && a[i] < a[x]) {
			i++;
		}
		while (j >= l && a[j] > a[x]) {
			j--;
		}
		if (i >= j) {
			break;
		}
		if (i == x) {
			x = j;
		} else if (x == j) {
			x = i;
		}
		swap(a[i++], a[j--]);
	}
	if (i > j + 1) {
		return i - 1;
	} else {
		i--;
		j++;
		if (x <= i) {
			swap(a[i], a[x]);
			return i;
		}
		if (x >= j) {
			swap(a[j], a[x]);
			return j;
		}
		return j - 1;
	}
}
int stat(vector<int>& a, int l, int r, int k) {
	if (r - l <= 1) {
		if (k == 2) {
			return max(a[l], a[r]);
		} else {
			return min(a[l], a[r]);
		}
	}
	int i = partition(a, l, r);
	if (k == i - l + 1) {
		return a[i];
	} else if (k < i - l + 1) {
		return stat(a, l, i - 1, k);
	} else {
		return stat(a, i + 1, r, k - (i - l + 1));
	}
}
int main() {
	srand(time(0));
	int n, k;
	cin >> n >> k;
	int A, B, C;
	cin >> A >> B >> C;
	vector<int> a(n);
	cin >> a[0] >> a[1];
	for (int i = 2; i < n; i++) {
		a[i] = A * a[i - 2] + B * a[i - 1] + C;
	}
	cout << stat(a, 0, int(a.size() - 1), k);
}
