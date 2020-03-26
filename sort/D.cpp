#include<iostream>
#include<vector>
#include<iomanip>
#include<cstdlib>
using namespace std;
int main() {
	int n;
	double A;
	cin >> n >> A;
	double m = 12456789;
	double left = -A;
	double right = A + 1;
	double r = A;
	for (int i = 0; i < 100; i++) {
		double delta = (left + right) / 2;
		double mid = delta;
		r = A;
		for (int j = 0; j < n - 1; j++) {
			r = r - delta;
			delta -= 2;
			if (r <= 0) {
				r = 123456789;
				break;
			}
		}
		if (r < m) {
			m = r;
			left = mid;
		} else {
			right = mid;
		}
	}
	printf("%.2f", m);
}
