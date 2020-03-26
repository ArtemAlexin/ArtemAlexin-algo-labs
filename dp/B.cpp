#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#define out cout
#define in cin
using namespace std;
const int inf = 1e9 + 1;
int main() {
	ifstream in("lis.in");
	ofstream out("lis.out");
	int n;
	cin >> n;
	vector<int> num(n);
	vector<int> f;
	f.assign(n + 1, inf);
	f[0] = -inf;
	vector<int> p(n + 1, -1);
	vector<int> p2(n + 1, -1);
	for (int i = 0; i < n; i++) {
		cin >> num[i];
	}
	for (int i = 0; i < n; i++) {
		int j = upper_bound(f.begin(), f.end(), num[i]) - f.begin();
		if (j > 0 && f[j - 1] < num[i] && f[j] > num[i]) {
			f[j] = num[i];
			p[j] = i;
			p2[i] = p[j - 1];
		}
	}
	int begin = 0;
	for (int i = 1; i < n + 1; i++) {
		if (f[i] != inf) {
			begin = i;
		}
	}
	begin = p[begin];
	vector<int> ans;
	while (begin != -1) {
		ans.push_back(num[begin]);
		begin = p2[begin];
	}
	cout << ans.size() << endl;
	for (int i = int(ans.size()) - 1; i >= 0; i--) {
		cout << ans[i] << " ";
	}
}
