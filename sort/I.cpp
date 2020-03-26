#include<iostream>
#include<vector>
using namespace std;
int64_t mid;
struct cashier {
	int serviceTime;
	int paymentTime;
	int waitingTime;
	cashier(int a, int b, int c) {
		paymentTime = a;
		serviceTime = b;
		waitingTime = c;
	}
	cashier() { }
	bool operator <(cashier a2) {
		if (this->paymentTime == 0 && a2.paymentTime == 0) {
			return  (mid - serviceTime - waitingTime) >
				(mid - a2.waitingTime - a2.serviceTime);
		}
		if (a2.paymentTime == 0) {
			return 0;
		}
		if (this->paymentTime == 0) {
			return 1;
		}
		return (mid - serviceTime - waitingTime) / paymentTime >
			(mid - a2.waitingTime - a2.serviceTime) / a2.paymentTime;
	}
};
template<typename T>
void merge(vector<T>& a, int l, int m, int r) {
	int i = l; int j = m;
	vector<T> t;
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
bool check(vector<cashier>& cashiers, int n, int p) {
	merges(cashiers, 0, int(cashiers.size()));
	int cnt = n;
	int64_t cakes = p;
	for (int i = 0; i < int(cashiers.size()); i++) {
		int64_t c = (mid - int64_t(cashiers[i].waitingTime + cashiers[i].serviceTime));
		if (c < 0) {
			continue;
		} else {
			if (cashiers[i].paymentTime == 0) {
				return 1;
			}
			cakes -= c / cashiers[i].paymentTime;
			cnt--;
		}
		if (cnt == 0 && cakes > 0)
			return 0;
		if (cakes <= 0)
			return 1;
	}
	return cakes <= 0;
}
int main() {
	int m;
	cin >> m;
	vector<cashier> cashiers(m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		cashiers[i] = cashier(a, b, c);
	}
	int64_t r = (int64_t)(1e10);
	int n, p;
	cin >> n >> p;
	int64_t l = 0;
	while (r - l > 0) {
		mid = (r + l) / 2;
		if (check(cashiers, n, p)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	cout << l;
}
