#include<iostream>
#include<fstream>
#include<string>
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
		nail->next = NULL;
		root->prev = NULL;
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
	void push_back(T a) {
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
	~list() {
		listElement<T>* n = root;
		while (n != NULL) {
			n = n->next;
			delete(root);
			root = n;
		}
	}
};
template<typename T>
class queue {
 private :
	list<T> l;

 public :
	void push(T i) {
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
	void push(T i) {
		l.push_back(i);
	}
	void pop() {
		l.pop_back();
	}
	T back() {
		return l.back();
	}
	bool empty() {
		return l.size() == 0;
	}
};
bool compatable(char c, char c2) {
	return (c == '[' && c2 == ']') || (c == '(' && c2 == ')');
}
int main() {
	ifstream in("brackets.in");
	ofstream out("brackets.out");
	string s;
	while (in >> s) {
		stack<char> st;
		for (int i = 0; i < int(s.size()); i++) {
			char c = s[i];
			if (!st.empty()) {
				if (compatable(st.back(), c)) {
					st.pop();
				} else {
					st.push(c);
				}
			} else {
				st.push(c);
			}
		}
		if (st.empty()) {
			out << "YES" << endl;
		} else {
			out << "NO" << endl;
		}
	}
}
