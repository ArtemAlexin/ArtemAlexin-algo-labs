import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Cortesian tree = new Cortesian();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for(int i = 0; i < n; i++) {
            int op = in.nextInt();
            int value = in.nextInt();
            if(op == 1) {
                tree.insert(value);
            } else if(op == -1) {
                tree.remove(value);
            } else {
                System.out.println(tree.kth(tree.getSize() - value + 1));
            }
        }
    }

    public static class Cortesian {
        private Node root;
        private int size;
        public Cortesian() {
            root = null;
            size = 0;
        }

        public boolean exists(int x) {
            Node cur = root;
            while(cur != null) {
                if(cur.x == x) return true;
                if(cur.x < x)
                    cur = cur.right;
                else
                    cur = cur.left;
            }
            return false;
        }
        private int size(Node x) {
            if(x == null) return 0;
            return x.size;
        }
        private void update(Node x) {
            if(x == null) return;
            x.size = size(x.left) + size(x.right) + 1;
        }
        private Pair split(Node root, int value) {
            if(root == null) return new Pair(null, null);
            if(root.x <= value) {
                Pair p = split(root.right, value);
                root.right = p.first;
                update(root);
                return new Pair(root, p.second);
            } else {
                Pair p = split(root.left, value);
                root.left = p.second;
                update(root);
                return new Pair(p.first, root);
            }
        }
        private Node merge(Node root1, Node root2) {
            if(root1 == null) return root2;
            if(root2 == null) return root1;
            if(root1.y < root2.y) {
                root1.right = merge(root1.right, root2);
                update(root1);
                return root1;
            } else {
                root2.left = merge(root1, root2.left);
                update(root2);
                return root2;
            }
        }
        public void insert(int x) {
            if(!exists(x)) {
                Pair t = split(this.root, x);
                this.root = merge(merge(t.first, new Node(x)),t.second);
                size++;
            }
        }
        public int getSize() {
            return size;
        }
        public int kth(int k) {
            Node cur = root;
            while(k != size(cur.left) + 1) {
                if(size(cur.left) + 1 > k)
                    cur = cur.left;
                else  {
                    k-= (size(cur.left) + 1);
                    cur = cur.right;
                }
            }
            return cur.x;
        }
        public void remove(int x) {
            if(exists(x)) {
                Pair t = split(this.root, x);
                t.first = split(t.first, x - 1).first;
                this.root = merge(t.first, t.second);
                size--;
            }
        }
    }

    public static class Node {
        public int x;
        public int y;
        public int size;
        Node left;
        Node right;
        Node(int x) {
            this.x = x;
            this.y = (int) (Math.random() * 1000000);
            size = 1;
        }
    }

    public static class Pair {
        public Node first;
        public Node second;

        public Pair(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }
}
