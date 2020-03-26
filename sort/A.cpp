#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int>& a, int l, int m, int r) {
	int i = l; int j = m;
	vector<int> t;
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
	for (int k = l; k < r; k++) {
		a[k] = t[k - l];
	}
}
void merges(vector<int>& a, int l, int r) {
	if (r - l <= 1) {
		return;
	}
	int mid = (l + r) / 2;
	merges(a, l, mid);
	merges(a, mid, r);
	merge(a, l, mid, r);
}

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	merges(arr, 0, n);
	for (int i = 0; i < int(arr.size()); i++) {
		cout << arr[i] << " ";
	}
}
