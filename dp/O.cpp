#include<iostream>
#include<vector>
using namespace std;
const int inf = 1e9;
void declare(vector<vector<int> > & dp) {
	dp.resize(400);
	for (int i = 0; i < 400; i++) {
		dp[i].assign(400, -inf);
	}
}
int up(int a, int b) {
	int c = a / b;
	if (a % b != 0) {
		c++;
	}
	return c;
}
bool isOk(int cnt1, int cnt2, int a, int b, int l, int searchingWidth) {
	vector < vector<int> > dp;
	declare(dp);
	if (searchingWidth > cnt1 * a + cnt2 * b) {
		return 0;
	}
	for (int ii = cnt1; ii >= 0; ii--) {
		for (int jj = cnt2; jj >= 0; jj--) {
			if (ii == cnt1 && jj == cnt2) {
				dp[ii][jj] = 0;
			}
			if (dp[ii][jj] - l >= 0) {
				return 1;
			}
			if (dp[ii][jj] > -inf) {
				int j = up(searchingWidth, b);
				int t2 = b * j, t1 = 0;
				for(int i = 0; ii >= i && t1 - a < searchingWidth; i++) {
						t1 += a;
						if (jj >= j) {
							if (ii - i >= 0 && jj - j >= 0 && dp[ii - i][jj - j] < dp[ii][jj] + 1) {
								dp[ii - i][jj - j] = dp[ii][jj] + 1;
							}
						}
						for (; t1 + t2 - b >= searchingWidth; t2 -= b, j--) {
							if (j <= 0) break;
						}
				}
			}
		}
	}
	return 0;
}

int main() {
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	int x, a, y, l, b;
	cin >> x >> a >> y >> b >> l;
	int minVal = 1;
	if (b > a) {
		swap(a, b);
		swap(x, y);
	}
	int maxVal = 100000;
	while (maxVal - minVal > 1) {
		int mid = (minVal + maxVal) / 2;
		isOk(x, y, a, b, l, mid) ? minVal = mid : maxVal = mid;
	}
	cout << minVal;
	return 0;
}
