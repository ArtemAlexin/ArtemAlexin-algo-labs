#include<iostream>
#include<fstream>
using namespace std;
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
 private :
	listElement<T>* root;
	listElement<T>* nail;
	int _size = 0;

 public :
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
		int q = i+1;
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
class queue {
 private :
	 list<T> l;

 public :
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
 private :
	 list<T> l;

 public :
	 void push(int i) {
		 l.push_back(i);
	 }
	 void pop() {
		 l.pop_back();
	 }
	 T back() {
		 return l.back();
	 }
};
int main() {
	stack<int> l;
	ifstream in("stack2.in");
	ofstream out("stack2.out");
	int n;
	in >> n;
	for (int i = 0; i < n; i++) {
		char c;
		in >> c;
		if (c == '+') {
			int a;
			in >> a;
			l.push(a);
		} else {
			out << l.back() << endl;
			l.pop();
		}
	}
}
