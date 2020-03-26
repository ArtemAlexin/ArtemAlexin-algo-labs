#include<iostream>
#include<time.h>
#include<fstream>
#include<string>
using namespace std;
template<typename T>
class vector {
 private :
	int _size = 0;
	int capacity = 1;
	T* arr;

 public :
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
	void push_back(int a) {
		if (_size < capacity) {
			arr[_size] = a;
		} else {
			capacity *= 2;
			T* arr2 = new T[capacity];
			for (int i = 0; i < _size; i++)
				arr2[i] = arr[i];
			arr2[_size] = a;
			delete(arr);
			arr = arr2;
		}
		_size++;
	}
	void pop_back() {
		_size--;
		if (_size == 0)
			return;
		if (_size * 4 < capacity) {
			capacity /= 2;
			T* arr2 = new T[capacity];
			for (int i = 0; i < _size; i++)
				arr2[i] = arr[i];
			delete(arr);
			arr = arr2;
			return;
		}
	}
	T& operator[](int a) {
		return arr[a];
	}
	~vector() {
		delete(arr);
	}
};
template<typename T>
class stack {
 private :
	vector<T> arr;
 public :
	void push(T a) {
		arr.push_back(a);
	}
	void pop() {
		arr.pop_back();
	}
	T top() {
	 return arr[arr.size() - 1];
	}
};
template<typename T>
class bad_queue {
 private :
	 int begin = 0;
	 vector<T> arr;
 public :
	 bad_queue() {}
	 bad_queue(T a) {
		 arr[begin] = a;
		 begin;
	 }
	 void push(T a) {
		 arr.push_back(a);
	 }
	 void pop() {
		 begin++;
	 }
	 T front() {
		 return arr[begin];
	 }
};
int main() {
	ifstream in("queue1.in");
	ofstream out("queue1.out");
	bad_queue<int> st;
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		char c;
		in >> c;
		if (c == '+') {
			int a;
			in >> a;
			st.push(a);
		} else {
			out << st.front() << endl;
			st.pop();
		}
	}
	return 0;
}
