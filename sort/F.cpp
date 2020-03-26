#include<iostream>
#include<vector>
using namespace std;
void antiquicksort(vector<int>& a) {
	for (int i = 0; i < int(a.size()); i++) {
		swap(a[i], a[i / 2]);
	}
}
int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
	}
	antiquicksort(a);
	for (auto i : a) {
		cout << i << " ";
	}
}
