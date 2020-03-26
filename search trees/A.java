import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        BinaryTree tree = new BinaryTree();
        Scanner in = new Scanner(System.in);
        while(in.hasNextLine()) {
            String t = in.nextLine();
            Scanner in2 = new Scanner(t);
            String comand = in2.next();
            int a = in2.nextInt();
            if(comand.equals("insert")) {
                tree.add(a);
            } else if(comand.equals("exists")) {
                System.out.println(tree.find(a));
            } else if(comand.equals("next")) {
                Node cur = tree.next(a);
                if(cur == null)
                    System.out.println("none");
                else
                    System.out.println(cur.value);
            } else if(comand.equals("prev")) {
                Node cur = tree.prev(a);
                if(cur == null)
                    System.out.println("none");
                else
                    System.out.println(cur.value);
            } else {
                tree.delete(a);
            }
        }
    }
}
class Node {
    public int value;
    public Node left;
    public Node right;
    public Node parent;

    public Node(int value, Node left, Node right) {
        this.parent = this;
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public Node(int value) {
        this.value = value;
        this.parent = this;
        this.left = this.right = null;
    }
    public Node(Node x) {
        this.value = x.value;
        this.left = x.left;
        this.right = x.right;
        this.parent = x.parent;
    }
}
class Utility {
    public static void swap(Node x, Node y) {
        int tmp = x.value;
        x.value = y.value;
        y.value = tmp;
    }
}

class BinaryTree {
    public Node root;

    BinaryTree(int x) {
        root = new Node(x);
    }

    BinaryTree() {
        root = null;
    }

    public void add(int x) {
        Node cur = root;
        Node par = root;
        while (cur != null) {
            par = cur;
            if (cur.value == x) return;
            if (cur.value < x) {
                cur = cur.right;
            } else {
                cur = cur.left;
            }
        }
        createNode(x, par);
    }

    private void declare(Node cur, int val, Node par, boolean isright) {
        cur = new Node(val);
        cur.parent = par;
        if (isright) {
            par.right = cur;
        } else {
            par.left = cur;
        }
    }

    private void createNode(int value, Node par) {
        if (par == null) {
            root = new Node(value);
            return;
        }
        if (par.value < value) {
            declare(par.right, value, par, true);
        } else {
            declare(par.left, value, par, false);
        }
    }

    public void printBinaryTree() {
        print(root);
    }

    private void print(Node cur) {
        if (cur == null) return;
        if (cur.left != null)
            print(cur.left);
        System.out.println(cur.value);
        if (cur.right != null)
            print(cur.right);
    }
    public void delete(int x) {
        Node cur = find_(x);
        if(cur != null)
            delete(cur);
    }
    public Node next(Node x) {
        Node cur = x;
        if (cur.right != null) {
            cur = cur.right;
            while (cur.left != null) {
                cur = cur.left;
            }
            return cur;
        } else {
            while (cur.parent.right == cur) {
                cur = cur.parent;
            }
            return cur.parent;
        }
    }

    private void declare2(Node parent, Node son, Node x) {
        if (parent == x) {
            son.parent = son;
            root = son;
        } else {
            if (parent.right == x) {
                parent.right = son;
                son.parent = parent;
            } else {
                parent.left = son;
                son.parent = parent;
            }
        }
    }

    public void delete(Node x) {
        if (x.right == x.left) {
            if (x.parent == x) {
                root = null;
                return;
            }
            if (x.parent.right == x) {
                x.parent.right = null;
                x.parent = null;
            } else {
                x.parent.left = null;
                x.parent = null;
            }
        } else if (x.right == null) {
            declare2(x.parent, x.left, x);
        } else if (x.left == null) {
            declare2(x.parent, x.right, x);
        } else {
            Node cur = next(x);
            Utility.swap(x, cur);
            delete(cur);
        }
    }

    private Node find_(int x) {
        Node cur = root;
        while (cur != null && cur.value != x) {
            if (cur.value > x) {
                cur = cur.left;
            } else {
                cur = cur.right;
            }
        }
        return cur;
    }

    public boolean find(int x) {
        Node cur = find_(x);
        return cur != null;
    }
    public Node next(int x) {
        Node cur = find_(x);
        if(cur != null) {
            Node tmp = next(cur);
            if(tmp.value <= x) {
                return null;
            } else {
                return tmp;
            }
        } else {
            this.add(x);
            Node t = this.find_(x);
            Node ans = next(t);
            this.delete(t);
            if(ans.value <= x) return null;
            return ans;
        }
    }
    private Node prev(Node x) {
        Node cur = x;
        if (cur.left != null) {
            cur = cur.left;
            while (cur.right != null) {
                cur = cur.right;
            }
            return cur;
        } else {
            while (cur.parent.left == cur) {
                cur = cur.parent;
            }
            return cur.parent;
        }
    }
    public Node prev(int x) {
        Node cur = find_(x);
        if(cur != null) {
            Node tmp = prev(cur);
            if(tmp.value >= x) {
                return null;
            } else {
                return tmp;
            }
        } else {
            this.add(x);
            Node t = this.find_(x);
            Node ans = prev(t);
            this.delete(t);
            if(ans.value >= x) return null;
            return ans;
        }
    }
}
