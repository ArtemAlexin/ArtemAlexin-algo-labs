#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
vector<int> pushes;
vector<pair<int64_t, int> > heap;
int s = 0;
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
void decreaseKey(int num, int64_t value) {
	int i = pushes[num];
	if (i >= 0) {
		heap[i].first = min(value, heap[i].first);
		siftUp(i);
	}
}
pair<int64_t, int> extractMin() {
	if (int(heap.size() == 0)) {
		return { -1, -1 };
	}
	int i = 0;
	pair<int64_t, int> ans = heap[0];
	swap(pushes[heap[i].second], pushes[heap[int(heap.size() - 1)].second]);
	pushes[heap[i].second] = -1;
	swap(heap[i], heap[int(heap.size() - 1)]);
	heap.pop_back();
	siftDown(i);
	return ans;
}
void insert(int64_t i) {
	heap.push_back({ i, pushes.size() });
	pushes.push_back(int(heap.size() - 1));
	siftUp(int(heap.size() - 1));
}
signed main() {
	string str;
	while (cin >> str) {
		if (str == "extract-min") {
			pair<int64_t, int> a = extractMin();
			if (a.second == -1) {
				cout << '*' << endl;
			} else {
				cout << a.first << " " << a.second + 1 << endl;
			}
			pushes.push_back(-1);
		}
		if (str == "decrease-key") {
			int a;
			int64_t b;
			cin >> a >> b;
			a--;
			decreaseKey(a, b);
			pushes.push_back(-1);
		}
		if (str == "push") {
			int64_t a;
			cin >> a;
			insert(a);
		}
	}
}
