#include<iostream>
#include<set>
#include<vector>
#include<list>
#include<algorithm>
#include<time.h>
#include<unordered_set>
#include<sstream>
#pragma GCC optimize("O3")
using namespace std;
vector<int> p{ 1000003, 1000006, 1000033, 1000039, 1000081, 1000099 };
struct hashF {
	int a;
	int b;
	int mod;
	hashF() {
		mod = p[rand() % 6];
		a = rand() % (mod - 1) + 1;
		b = rand() % mod;
	}
	uint32_t getId(uint32_t x, uint32_t m) {
		return (a * x + b) % mod % m;
	}
};
struct Node {
	string value;
	Node* prev = NULL;
	Node* next = NULL;
};
struct P {
	string key;
	string value;
	uint32_t h;
	Node* inList;
};
bool operator < (P left, P right) {
	return left.key < right.key;
}
bool cmp(P left, P right) {
	return left.key < right.key;
}
uint32_t calcH(string f) {
	uint32_t pow = 1;
	uint32_t h = 0;
	for (int i = 0; i < (int)f.size(); i++) {
		h += (f[i] * pow);
		pow *= 29;
	}
	return h;
}
struct HashMap {
	Node* back = NULL;
	hashF h = hashF();
	const int defaultCapacity = 10;
	vector<set<P> > arr;
	uint32_t size;
	HashMap() {
		size = 0;
		arr.resize(defaultCapacity);
	}
	void extend() {
		if (arr.size() <= 3 * size) {
			vector<set<P> > arrCopy(arr.size() * 2);
			hashF tmp = hashF();
			for (auto i : arr) {
				for (auto element : i) {
					arrCopy[tmp.getId(element.h, arrCopy.size())].insert(element);
				}
			}
			arr.clear();
			arr = arrCopy;
			h = tmp;
		}
	}
	void insert(string key, string value) {
		extend();
		P cur = { key, value, calcH(key), NULL};
		uint32_t id = h.getId(cur.h, arr.size());
		auto it = arr[id].lower_bound(cur);
		if (it != arr[id].end() && it->key == key) {
			it->inList->value = value;
			cur.inList = it->inList;
			arr[id].erase(it);
			arr[id].insert(cur);
			return;
		}
		if (back == NULL) {
			back = new Node();
			back->next = NULL;
			back->prev = NULL;
			back->value = cur.value;
			cur.inList = back;
			arr[id].insert(cur);
			size++;
			return;
		}
		Node* n = new Node();
		n->value = value;
		n->next = NULL;
		n->prev = back;
		back->next = n;
		back = back->next;
		cur.inList = back;
		arr[id].insert(cur);
		size++;
		return;
	}
	string exists(string key) {
		uint32_t curH = calcH(key);
		uint32_t id = h.getId(curH, arr.size());
		P cur = { key, "", curH, NULL };
		auto it = arr[id].lower_bound(cur);
		return it != arr[id].end() && it->key == key ? it->value : "none";
	}
	void remove(string key) {
		uint32_t curH = calcH(key);
		uint32_t id = h.getId(curH, arr.size());
		P cur = { key, "", curH, NULL };
		auto it = arr[id].lower_bound(cur);
		if (it != arr[id].end() && it->key == key) {
			if(it->inList->prev == NULL) {
				if (it->inList->next == NULL) {
					back = NULL;
				} else {
					it->inList->next->prev = NULL;
				}
			} else if (it->inList->next == NULL) {
				if (it->inList->prev == NULL) {
					back = NULL;
				} else {
					it->inList->prev->next = NULL;
					back = back->prev;
				}
			} else {
				it->inList->prev->next = it->inList->next;
				it->inList->next->prev = it->inList->prev;
			}
			arr[id].erase(it);
			return;
		}
	}
	void next(string key) {
		uint32_t curH = calcH(key);
		uint32_t id = h.getId(curH, arr.size());
		P cur = { key, "", curH, NULL };
		auto it = arr[id].lower_bound(cur);
		if (it == arr[id].end() || it->key != key || it->inList->next == NULL) {
			cout << "none\n";
		} else {
			cout << it->inList->next->value << '\n';
		}
	}
	void prev(string key) {
		uint32_t curH = calcH(key);
		uint32_t id = h.getId(curH, arr.size());
		P cur = { key, "", curH, NULL };
		auto it = arr[id].lower_bound(cur);
		if (it == arr[id].end() || it->key != key || it->inList->prev == NULL) {
			cout << "none\n";
		} else {
			cout << it->inList->prev->value << '\n';
		}
	}
};
int main() {
	freopen("linkedmap.in", "r", stdin);
	freopen("linkedmap.out", "w", stdout);
	HashMap m = HashMap();
	string s;
	while (getline(cin, s)) {
		stringstream in(s);
		string op = "";
		while (in >> op) {
			string key, value;
			if (op == "put") {
				in >> key >> value;
				m.insert(key, value);
			} else if (op == "get") {
				string key;
				in >> key;
				cout << m.exists(key) << '\n';
			} else if (op == "next") {
				string key;
				in >> key;
				m.next(key);
			} else if (op == "prev") {
				string key;
				in >> key;
				m.prev(key);
			} else {
				string key;
				in >> key;
				m.remove(key);
			}
		}
	}
}
