#include<iostream>
#include<algorithm>
using namespace std;
int main() {
	string ans;
	int k;
	cin >> k;
	for (int i = 0; i < 1000; i++) {
		ans.push_back('P');
	}
	cout << ans << '\n';
	int cnt = 1;
		for (int i = 1; i < 1000; i++) {
			string copy = ans;
			for (int j = 0; j < i; j++) {
				if (j == 0) {
					copy[j] = (char)((int)copy[j] + 31);
				} else {
					copy[j] = (char)((int)copy[j] + 30);
				}
			}
			copy[i] = (char)((int)copy[i] - 1);
			reverse(copy.begin(), copy.end());
			cout << copy << '\n';
			cnt++;
			if (cnt == k) break;
	}
}
