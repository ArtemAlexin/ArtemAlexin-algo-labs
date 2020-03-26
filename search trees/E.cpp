#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
using namespace std;
struct Node {
	int x;
	int y;
	int id;
	int size;
	Node* left;
	Node* right;
	Node(int x, int y, int id) {
		this->x = x;
		this->y = y;
		this->id = id;
		this->size = 1;
		left = nullptr;
		right = nullptr;
	}
};
struct f {
	int id;
	int par;
	int left;
	int right;
};
vector<f> gl;
bool cmp(f &t1, f &t2) {
	return t1.id < t2.id;
}

struct Cortesian {
	Node* root;
	int size;
	Cortesian() {
		root = nullptr;
	}
	Cortesian(Node x) {
		root = &x;
		size = x.size;
	}
	Cortesian(Node* x) {
		root = x;
		size = x->size;
	}
};
int size_(Node* root) {
	if (root == nullptr) return 0;
	return root->size;
}
void update(Node* root) {
	if (root == nullptr) return;
	root->size = size_(root->left) + size_(root->right) + 1;
}
Node* merge(Node* root1, Node* root2) {
	if (root1 == nullptr) return root2;
	if (root2 == nullptr) return root1;
	if (root1->y < root2->y) {
		root1->right = merge(root1->right, root2);
		update(root1);
		return root1;
	} else {
		root2->left = merge(root1, root2->left);
		update(root2);
		return root2;
	}
}
void up(Node* cur, int par) {
	if (cur == nullptr) return;
	int left = 0, right = 0;
	if (cur->left != nullptr) {
		left = cur->left->id;
	}
	if (cur->right != nullptr) {
		right = cur->right->id;
	}
	gl.push_back({ cur->id, par, left, right });
	up(cur->left, cur->id);
	up(cur->right, cur->id);
}
struct tup {
	int x;
	int y;
	int id;
};
bool cmp2(tup& t1, tup& t2) {
	return t1.x < t2.x;
}
int main() {
	int n;
	cin >> n;
	vector<tup> arr(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		arr[i] = { x, y, i + 1 };
	}
	sort(arr.begin(), arr.end(), cmp2);
	deque<Cortesian> deq;
	for (int i = 0; i < (int)arr.size(); i++) {
		Node* x = new Node(arr[i].x, arr[i].y, arr[i].id);
		deq.push_back(Cortesian(x));
	}
	while ((int)deq.size() > 1) {
		Cortesian fs = deq.front();
		deq.pop_front();
		Cortesian se = deq.front();
		deq.pop_front();
		if (fs.size < se.size) {
			deq.push_front(se);
			deq.push_back(fs);
		} else {
			deq.push_back(Cortesian(merge(fs.root, se.root)));
		}
	}
	Cortesian cur = deq.front();
	up(cur.root, 0);
	sort(gl.begin(), gl.end(), cmp);
	cout << "YES\n";
	for (auto i : gl) {
		cout << i.par << " " << i.left << " " << i.right << '\n';
	}
}

/*public static void up(Node cur, int pr, ArrayList<Tupple4> arr2) {
        if (cur == null) return;
        int left = 0, right = 0;
        if (cur.left != null) {
            left = cur.left.num;
        }
        if (cur.right != null) {
            right = cur.right.num;
        }
        arr2.add(new Tupple4(cur.num, pr, left, right));
        up(cur.left, cur.num, arr2);
        up(cur.right, cur.num, arr2);

    }*/
