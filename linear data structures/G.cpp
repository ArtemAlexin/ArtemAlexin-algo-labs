#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cstdlib>
using namespace std;
template<typename T>
class vector {
 private:
	int _size = 0;
	int capacity = 1;
	T* arr;

 public:
	vector() {
		arr = (T*)malloc(sizeof(T) * capacity);;
	}
	vector(int n) {
		capacity = 2 * n;
		arr = (T*)malloc(sizeof(T) * capacity);;
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
			T* arr2 = (T*)malloc(sizeof(T) * capacity);
			for (int i = 0; i < _size; i++)
				arr2[i] = arr[i];
			arr2[_size] = a;
			free(arr);
			arr = arr2;
		}
		_size++;
	}
	void pop_back() {
		if (_size * 4 <= capacity) {
			capacity = capacity / 2;
			T* arr2 = (T*)malloc(sizeof(T) * capacity);
			for (int i = 0; i < _size; i++)
				arr2[i] = arr[i];
			free(arr);
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
		free(arr);
	}
};

template<typename T>
class stack {
 private:
	vector<T> arr;
 public:
	void push(const T& a) {
		arr.push_back(a);
	}
	void pop() {
		arr.pop_back();
	}
	T& top() {
		return arr[arr.size() - 1];
	}
	bool empty() {
		return arr.size() == 0;
	}
};
class queueM {
	stack<pair<int, int> > left;
	stack<pair<int, int> > right;

 public:
	int getMin() {
		if (!right.empty()) {
			int min2 = right.top().second;
			right.pop();
			return min(min2, left.top().second);
		} else {
			int min2 = left.top().first;
			while (!left.empty()) {
				if (!right.empty()) {
					min2 = right.top().second;
				}
				int a = left.top().first;
				right.push({ a, min(a, min2) });
				left.pop();
			}
			min2 = right.top().second;
			right.pop();
			return min2;
		}
	}
	void push(int a) {
		if (!left.empty()) {
			left.push({ a, min(a, left.top().second) });
		} else {
			left.push({ a, a });
		}
	}
};
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m, k;
	int a, b, c;
	cin >> n >> m >> k >> a >> b >> c;
	vector<int> arr(k);
	queueM que;
	if (m >= k) {
		for (int i = 0; i < k; i++) {
			int a;
			cin >> a;
			arr[i] = a;
			que.push(arr[i]);
		}
		int f = arr[k - 1];
		int l = arr[k - 2];
		for (int i = k; i < m; i++) {
			int z = a * l + b * f + c;
			que.push(z);
			l = f;
			f = z;
		}
		int64_t sum = 0;
		sum += que.getMin();
		for (int i = m; i < n; i++) {
			int z = a * l + b * f + c;
			que.push(z);
			l = f;
			f = z;
			sum += que.getMin();
		}
		cout << sum;
	} else {
		int64_t sum = 0;
		for (int i = 0; i < m; i++) {
			int a;
			cin >> a;
			arr[i] = a;
			que.push(arr[i]);
		}
		sum += que.getMin();
		for (int i = m; i < k; i++) {
			int a;
			cin >> a;
			arr[i] = a;
			que.push(arr[i]);
			sum += que.getMin();
		}
		int f = arr[k - 1];
		int l = arr[k - 2];
		for (int i = k; i < n; i++) {
			int z = a * l + b * f + c;
			que.push(z);
			sum += que.getMin();
			l = f;
			f = z;
		}
		cout << sum;
	}
}
