#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>
using namespace std;
int n;
vector<int>  bsize(int a) {
	int b = a;
	int j = 0;
	vector<int> ans;
	while (j < n) {
		ans.push_back(b % 2);
		b /= 2;
		j++;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
bool increasing(vector<int>& a) {
	for (int i = 1; i < int(a.size()); i++) {
		if (a[i] < a[i - 1]) {
			return 0;
		}
	}
	return 1;
}
bool check(vector<pair<int, int > >& a) {
	int l = (1 << n);
	for (int i = 0; i < l; i++) {
		vector<int> arr = bsize(i);
		for (int j = 0; j < int(a.size()); j++) {
			if (arr[a[j].first] > arr[a[j].second])
				swap(arr[a[j].first], arr[a[j].second]);
		}
		if (!increasing(arr)) {
			return 0;
	}
	}
	return 1;
}
int main() {
	int m, k;
	cin >> n >> m >> k;
	vector<pair<int, int > > a;
	for (int i = 0; i < k; i++) {
		int r;
		cin >> r;
		for (int j = 0; j < r; j++) {
			int first, second;
			cin >> first >> second;
			if (first > second) {
				swap(first, second);
			}
			a.push_back({ first - 1, second - 1});
		}
	}
	if (check(a)) {
		cout << "YES";
	} else {
		cout << "NO";
	}
}
