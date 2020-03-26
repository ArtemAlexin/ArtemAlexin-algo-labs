# include <iostream>
# include <string>
# include <cstdlib>
#include<time.h>
#include<cstdio>
using namespace std;

template<typename T>
class vector {
 private:
	int _size = 0;
	T* arr;
	int capacity = 1;

 public:
	vector() {
		arr = new T[capacity];
	}
	vector(int n) {
		capacity = 2 * n;
		arr = new T[capacity];
		_size = n;
	}
	int size() {
		return _size;
	}
	void push_back(const T& a) {
		if (_size < capacity) {
			arr[_size] = a;
		} else {
			capacity = capacity * 2;
			T* arr2 = new T[capacity];
			for (int i = 0; i < _size; i++) {
				arr2[i] = arr[i];
			}
			arr2[_size] = a;
			delete[] arr;
			arr = arr2;
		}
		_size++;
	}
	void pop_back() {
		if (_size * 4 <= capacity) {
			capacity = capacity / 2;
			T* arr2 = new T[capacity];
			for (int i = 0; i < _size; i++)
				arr2[i] = arr[i];
			delete[] arr;
			arr = arr2;
		}
		_size--;
		if (_size == 0)
			return;
	}
	T& operator[](int a) {
		return arr[a];
	}
	~vector() {
		delete[] arr;
	}
};

template<typename T>
struct listElement {
	listElement* next;
	listElement* prev;
	T data;
	listElement(T a) {
		data = a;
		next = NULL;
		prev = NULL;
	}
	listElement() {}
};
template<typename T>
class list {
 private:
	listElement<T>* root;
	listElement<T>* nail;
	int _size = 0;

 public:
	list() {
		root = new listElement<T>;
		nail = new listElement<T>;
		root->next = nail;
		nail->prev = root;
	}
	list(T a) {
		root = new listElement<T>;
		nail = new listElement<T>;
		listElement<T>* n = new listElement<T>(a);
		root->next = n;
		n->prev = root;
		nail->prev = n;
		n->next = nail;
		_size = 1;
	}
	int size() {
		return _size;
	}
	void push_back(int a) {
		listElement<T>* n = new listElement<T>(a);
		n->prev = nail->prev;
		n->next = nail;
		nail->prev->next = n;
		nail->prev = n;
		_size++;
	}
	void pop_back() {
		_size--;
		listElement<T>* n = nail->prev;
		nail->prev->prev->next = nail;
		nail->prev = nail->prev->prev;
		delete(n);
	}
	void pop_front() {
		listElement<T>* n = root->next;
		n->next->prev = root;
		root->next = n->next;
		delete(n);
	}
	T get(int i) {
		listElement<T>* cur = root;
		int q = i + 1;
		while (q > 0) {
			cur = cur->next;
			q--;
		}
		return cur->data;
	}
	T back() {
		return nail->prev->data;
	}
};
template<typename T>
class queu {
 private:
	list<T> l;

 public:
	void push(int i) {
		l.push_back(i);
	}
	void pop() {
		l.pop_front();
	}
	T top() {
		return l.get(0);
	}
};
template<typename T>
class stack {
 private:
	list<T> l;

 public:
	void push(int i) {
		l.push_back(i);
	}
	void pop(int i) {
		l.pop_back();
	}
	void back(int i) {
		return l.back();
	}
};
int bins(const string& t);
const int mod = (1 << 16);
vector<string> mp;
vector<pair<string, int > > labels;
vector<int> reg(26);
queu<int> que;
int i;
int bins(const string& t) {
	int l = 0;
	int r = labels.size() - 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (labels[mid].first <= t) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return labels[l - 1].second;
}
void check(const string& s) {
	switch (s[0]) {
	case '+': {
		int t1 = que.top();
		que.pop();
		int t2 = que.top();
		que.pop();
		que.push((t1 + t2) % mod);
		break;
	}
	case '-': {
		int	t1 = que.top();
		que.pop();
		int t2 = que.top();
		que.pop();
		que.push((t1 - t2 + mod) % mod);
		break;
	}
	case '*': {
		int t1 = que.top();
		que.pop();
		int t2 = que.top();
		que.pop();
		que.push(int((int64_t(t1) * t2) % mod));
		break;
	}
	case '/': {
		int t1 = que.top();
		que.pop();
		int t2 = que.top();
		que.pop();
		if (t2 != 0) {
			que.push((t1 / t2) % mod);
		} else {
			que.push(0);
		}
		break;
	}
	case '%': {
		int t1 = que.top();
		que.pop();
		int t2 = que.top();
		que.pop();
		if (t2 != 0) {
			que.push((t1 % t2) % mod);
		} else {
			que.push(0);
		}
		break;
	}
	case '>': {
		int t1 = que.top();
		que.pop();
		reg[s[1] - 'a'] = t1;
		break;
	}
	case '<': {
		que.push(reg[s[1] - 'a']);
		break;
	}
	case 'P': {
		if (s.size() == 1) {
			int t1 = que.top();
			que.pop();
			cout << t1 << '\n';
		} else {
			cout << reg[s[1] - 'a'] << '\n';
		}
		break;
	}
	case 'C': {
		if (s.size() == 1) {
			int t1 = que.top();
			que.pop();
			cout << char(t1 % 256);
		} else {
			cout << char(reg[s[1] - 'a'] % 256);
		}
		break;
	}
	case ':': {
		break;
	}
	case 'J': {
		string a = s.substr(1);
		int cur = bins(a);
		i = cur;
		break;
	}
	case 'Z': {
		if (reg[s[1] - 'a'] == 0) {
			string a = s.substr(2);
			int cur = bins(a);
			i = cur;
		}
		break;
	}
	case 'E': {
		if (reg[s[1] - 'a'] == reg[s[2] - 'a']) {
			string a = s.substr(3);
			int cur = bins(a);
			i = cur;
		}
		break;
	}
	case 'G': {
		if (reg[s[1] - 'a'] > reg[s[2] - 'a']) {
			string a = s.substr(3);
			int cur = bins(a);
			i = cur;
		}
		break;
	}
	case 'Q': {
		exit(0);
		break;
	}
	default: {
		int a = stoi(s);
		que.push(a);
		break;
	}
	}
}
void quick_sort(int l, int r, vector<pair<string, int > >& b) {
	int len = r - l + 1;
	if (len <= 1) return;
	pair <string, int> x = labels[rand() % len + l];
	int pos = l;
	for (int i = l; i <= r; i++) {
		if (labels[i] < x)
			b[pos++] = labels[i];
	}
	int p1 = pos - 1;
	for (int i = l; i <= r; i++) {
		if (labels[i] == x)
			b[pos++] = labels[i];
	}
	int p2 = pos;
	for (int i = l; i <= r; i++) {
		if (labels[i] > x)
			b[pos++] = labels[i];
	}
	for (int i = l; i <= r; i++) {
		labels[i] = b[i];
	}
	quick_sort(l, p1, b);
	quick_sort(p2, r, b);
}
int main() {
	srand(time(NULL));
	string s;
	while (cin >> s) {
		mp.push_back(s);
		if (s[0] == ':') {
			labels.push_back({ s.substr(1), i });
		}
		i++;
	}
	vector < pair<string, int> > b(labels.size());
	for (int j = 0; j < labels.size(); j++) {
		b[j] = labels[j];
	}
	quick_sort(0, labels.size() - 1, b);
	i = 0;
	while (i < mp.size()) {
		check(mp[i]);
		i++;
	}
}
