#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
template<typename T>
void merge(vector<T>& a, int l, int m, int r) {
	int i = l; int j = m;
	vector<T> t(r - l);
	int z = 0;
	while (i < m && j < r) {
		if (a[i] < a[j]) {
			t[z] = a[i];
			i++;
		} else {
			t[z] = a[j];
			j++;
		}
		z++;
	}
	if (i >= m) {
		while (j < r) {
			t[z] = a[j];
			j++;
			z++;
		}
	}
	if (j >= r) {
		while (i < m) {
			t[z] = a[i];
			i++;
			z++;
		}
	}
	for (int k = l; k < r; k++) {
		a[k] = t[k - l];
	}
}
template<typename T>
void merges(vector<T>& a, int l, int r) {
	if (r - l <= 1) {
		return;
	}
	int mid = (l + r) / 2;
	merges(a, l, mid);
	merges(a, mid, r);
	merge(a, l, mid, r);
}
int t;
struct Element {
	float value;
	int id;
	bool operator <(Element &a2) {
		return value > a2.value;
	}
};

vector<Element> f2;
bool ok(float s, vector<pair<float, float> >& v_w) {
	f2.resize(int(v_w.size()));
	for (int i = 0; i < int(f2.size()); i++) {
		f2[i].value = v_w[i].first - s * v_w[i].second;
		f2[i].id = i + 1;
	}
	merges(f2, 0, int(f2.size()));
	float res = 0;
	for (int i = 0; i < t; i++) {
		res += f2[i].value;
	}
	if (res >= 0) {
		return 1;
	}
	return 0;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n >> t;
	vector<pair<float, float> > arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
	float l = 0;
	float r = 1e6;
	for (int i = 0; i < 50; i++) {
		float mid = (l + r) / 2;
		if (ok(mid, arr)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	ok(l, arr);
	for (int i = 0; i < t; i++) {
		cout << f2[i].id << " ";
	}
}
