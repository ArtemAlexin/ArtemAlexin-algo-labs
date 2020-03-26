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
struct P {
	string key;
	string value;
	uint32_t h;
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
	hashF h = hashF();
	const int defaultCapacity = 1;
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
		P cur = { key, value, calcH(key) };
		uint32_t id = h.getId(cur.h, arr.size());
		auto it = arr[id].lower_bound(cur);
		if (it != arr[id].end() && it->key == key) {
			arr[id].erase(it);
			arr[id].insert(cur);
			return;
		}
		arr[id].insert(cur);
		size++;
		return;
	}
	string exists(string key) {
		uint32_t curH = calcH(key);
		uint32_t id = h.getId(curH, arr.size());
		P cur = { key, "", curH };
		auto it = arr[id].lower_bound(cur);
		return it != arr[id].end() && it->key == key ? it->value : "none";
	}
	void remove(string key) {
		uint32_t curH = calcH(key);
		uint32_t id = h.getId(curH, arr.size());
		P cur = { key, "", curH };
		auto it = arr[id].lower_bound(cur);
		if (it != arr[id].end() && it->key == key) {
			arr[id].erase(it);
			return;
		}
	}
};
int main() {
	freopen("map.in", "r", stdin);
	freopen("map.out", "w", stdout);
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
			} else {
				string key;
				in >> key;
				m.remove(key);
			}
		}
	}
}
