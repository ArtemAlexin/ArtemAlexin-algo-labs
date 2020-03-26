#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct node {
	int parent;
	int cnt = 1;
	int min;
	int max;
	node(int parent, int value) {
		this->parent = parent;
		this->min = value;
		this->max = value;
	}
	node() {}
};
vector<node> sets;
vector<int> rang;
int find_leader(int i) {
	if (sets[i].parent == i) {
		return i;
	}
	return sets[i].parent = find_leader(sets[i].parent);
}
void unite(int a, int b) {
	int ca = find_leader(a);
	int cb = find_leader(b);
	if (ca == cb) {
		return;
	}
	if (rang[ca] < rang[cb]) {
		swap(ca, cb);
	}
	sets[cb].parent = ca;
	sets[ca].min = min(sets[ca].min, sets[cb].min);
	sets[ca].max = max(sets[ca].max, sets[cb].max);
	sets[ca].cnt += sets[cb].cnt;
	if (rang[ca] == rang[cb]) {
		rang[ca]++;
	}
}
int main() {
	int n;
	cin >> n;
	rang.resize(n + 1);
	sets.resize(n + 1);
	for (int i = 0; i < n + 1; i++) {
		sets[i] = node(i, i);
	}
	string str;
	while (cin >> str) {
		if (str == "union") {
			int a, b;
			cin >> a >> b;
			unite(a, b);
		} else {
			int a;
			cin >> a;
			a = find_leader(a);
			cout << sets[a].min << " " << sets[a].max << " " << sets[a].cnt << endl;
		}
	}
}
