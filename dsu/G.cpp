#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>
#include <set>
using namespace std;
const int64_t inf = 1e18;
const int64_t inf2 = 1e9;
vector<int> pushes;
vector<pair<int64_t, int> > heap;
void siftDown(int i) {
	while (2 * i + 1 < int(heap.size())) {
		int l = 2 * i + 1;
		int r = 2 * i + 2;
		int j = l;
		if (r < int(heap.size()) && heap[r].first < heap[l].first) {
			j = r;
		}
		if (heap[i].first > heap[j].first) {
			swap(pushes[heap[i].second], pushes[heap[j].second]);
			swap(heap[i], heap[j]);
		}
		i = j;
	}
}
void siftUp(int i) {
	while (heap[(i - 1) / 2].first > heap[i].first) {
		int j = (i - 1) / 2;
		swap(pushes[heap[i].second], pushes[heap[j].second]);
		swap(heap[i], heap[j]);
		i = (i - 1) / 2;
	}
}
void Insert(int64_t i) {
	heap.push_back({ i, int(pushes.size()) });
	pushes.push_back(int(heap.size() - 1));
	siftUp(int(heap.size() - 1));
}
int64_t getMin() {
	if (int(heap.size()) == 0) {
		return inf;
	}
	return heap[0].first;
}
void Erase(int num) {
	int i = pushes[num];
	pushes[heap[int(heap.size() - 1)].second] = pushes[heap[i].second];
	heap[i] = heap[int(heap.size() - 1)];
	heap.pop_back();
	siftDown(i);
}
struct Node {
	int type;
	int64_t value;
	int i;
	int j;
};
signed main() {
	int n, m;
	cin >> n >> m;
	vector<vector<Node > > arr(n);
	vector<int64_t> ans(n, -inf);
	for (int i = 0; i < m; i++) {
		int l, r;
		int64_t v;
		cin >> l >> r >> v; l--; r--;
		arr[l].push_back({ 1, v, r, int(arr[r].size()) });
		arr[r].push_back({ 2, v, l, int(arr[l].size()) - 1 });
	}
	int64_t t = -inf;
	multiset<int64_t> mul;
	for (int i = 0; i < n; i++) {
		if (!mul.empty()) {
			t = -*mul.begin();
		}
		for (int j = 0; j < int(arr[i].size()); j++) {
			if (arr[i][j].type == 1) {
				mul.insert(-arr[i][j].value);
			}
		}
		if (!mul.empty()) {
			t = -*mul.begin();
		}
		for (int j = 0; j < int(arr[i].size()); j++) {
			if (arr[i][j].type == 2) {
				mul.erase(mul.find(-arr[i][j].value));
			}
		}
		ans[i] = t;
	}
	for (int i = 0; i < n; i++) {
		if (ans[i] == -inf) {
			cout << 0 << " ";
		} else {
			cout << ans[i] << " ";
		}
	}
}
