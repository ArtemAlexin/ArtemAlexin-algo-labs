import java.io.*;
import java.util.NoSuchElementException;


public class Main {
    public static void main(String[] args) throws IOException {

        BinaryTree tree = new BinaryTree();
        Scanner in = new Scanner(System.in);
        while(in.hasNext()) {
            String t = in.nextLine();
            Scanner in2 = new Scanner(t);
            String comand = in2.next();
            int a = in2.nextInt();
            if(comand.equals("insert")) {
                tree.add(a);
            } else if(comand.equals("exists")) {
                System.out.println(tree.find(a));
            } else if(comand.equals("next")) {
                int cur = tree.next(a);
                if(cur == -1000000001)
                    System.out.println("none");
                else
                    System.out.println(cur);
            } else if(comand.equals("prev")) {
                int cur = tree.prev(a);
                if(cur == -1000000001)
                    System.out.println("none");
                else
                    System.out.println(cur);
            } else {
                tree.delete(a);
            }
        }
    }

    static class BinaryTree {
        public Node root;

        BinaryTree(int x) {
            root = new Node(x);
        }
        BinaryTree(Node x) {
            root = x;
            if(x != null)
                x.parent = x;
        }
        BinaryTree() {
            root = null;
        }
        private boolean isRoot(Node x) {
            return x.parent == x;
        }
        private boolean isLeftSon(Node x) {
            return x.parent.left == x;
        }
        private boolean isRightSon(Node x) {
            return x.parent.right == x;
        }
        private void doSomethingWithRootOrNot(Node parent, Node x) {
            if(isRoot(parent)) {
                x.parent = x;
            } else {
                x.parent = parent.parent;
                if(x.value > parent.parent.value) {
                    parent.parent.right = x;
                } else {
                    parent.parent.left = x;
                }
            }
        }
        private void rotateRight(Node x) {

            Node parent = x.parent;
            parent.left = x.right;
            if(x.right != null)
                x.right.parent = parent;
            x.right = parent;
            doSomethingWithRootOrNot(parent, x);
            parent.parent = x;
        }
        private void rotateLeft(Node x) {
            Node parent = x.parent;
            parent.right = x.left;
            if(x.left != null)
                x.left.parent = parent;
            x.left = parent;
            doSomethingWithRootOrNot(parent, x);
            parent.parent = x;
        }
        private void zig(Node x) {
            if (isLeftSon(x)) {
                rotateRight(x);
            } else {
                rotateLeft(x);
            }
        }
        private void zig_zag(Node x) {
            zig(x);
            zig(x);
        }
        private void zig_zig(Node x) {
            zig(x.parent);
            zig(x);
        }
        private void splay(Node x) {
            if(isRoot(x)) return;
            while(!isRoot(x)) {
                if (isRoot(x.parent)) {
                    zig(x);
                } else if(isLeftSon(x) && isRightSon(x.parent) || isRightSon(x) && isLeftSon(x.parent)) {
                    zig_zag(x);
                } else {
                    zig_zig(x);
                }
            }
            root = x;
        }
        public void add(int x) {
            Node cur = root;
            Node par = root;
            while (cur != null) {
                par = cur;
                if (cur.value == x) {splay(cur);return;}
                if (cur.value < x) {
                    cur = cur.right;
                } else {
                    cur = cur.left;
                }
            }
            splay(createNode(x, par));
        }

        private Node declare(Node cur, int val, Node par, boolean isright) {
            cur = new Node(val);
            cur.parent = par;
            if (isright) {
                par.right = cur;
            } else {
                par.left = cur;
            }
            return cur;
        }

        private Node createNode(int value, Node par) {
            if (par == null) {
                root = new Node(value);
                return root;
            }
            if (par.value < value) {
                return declare(par.right, value, par, true);
            } else {
                return declare(par.left, value, par, false);
            }
        }
        private Node findMax(BinaryTree r) {
            Node cur = r.root;
            while(cur.right != null) {
                cur = cur.right;
            }
            return cur;
        }
        private BinaryTree merge(BinaryTree a1, BinaryTree a2) {
            if(a1.root == null)
                return a2;
            if(a2.root == null)
                return a1;
            Node m = findMax(a1);
            a1.splay(m);
            a1.root.right = a2.root;
            a2.root.parent = a1.root;
            return a1;
        }
        private void delete(Node x) {
            splay(x);
            root = merge(new BinaryTree(x.left), new BinaryTree(x.right)).root;
        }
        public void delete(int x) {
            Node cur = find_(x);
            if(cur!= null) {
                delete(cur);
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
        private int next(int x) {
            boolean yes = false;
            if(!find(x)) {
                this.add(x);
                yes = true;
            }
            Node cur = root;
            int ans = -1000000001;
            if(cur.right != null) {
                cur = cur.right;
                while (cur.left != null) {
                    cur = cur.left;
                }
                ans = cur.value;
                splay(cur);
            }
                if(yes)
                    delete(x);
                return ans;
        }
        private int prev(int x) {
            boolean yes = false;
            if(!find(x)) {
                this.add(x);
                yes = true;
            }
            Node cur = root;
            int ans = -1000000001;
            if(cur.left != null) {
                cur = cur.left;
                while (cur.right != null) {
                    cur = cur.right;
                }
                ans = cur.value;
                splay(cur);
            }
            if(yes)
                delete(x);
            return ans;
        }
        private Node find_(int x) {
            Node cur = root;
            Node par = cur;
            while (cur != null && cur.value != x) {
                par = cur;
                if (cur.value > x) {
                    cur = cur.left;
                } else {
                    cur = cur.right;
                }
            }
            if(cur == null && par != null)
                splay(par);
            else if(cur != null)
                splay(cur);
            return cur;
        }

        public boolean find(int x) {
            Node cur = find_(x);
            return cur != null;
        }
    }

    static class Node {
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

    public static class Pair {
        Node first;
        Node second;

        public Pair(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }
}
class Scanner implements AutoCloseable {

    private final Reader in;
    private StringBuilder nextWord = new StringBuilder();
    private char currentChar = ' ';
    private boolean EOF = false;
    private String lineSeparators = System.lineSeparator();
    //private boolean nextChar = (char) 0;

    private boolean isNumeric(String word) {
        try {
            Integer.parseInt(word);
            return true;
        } catch(NumberFormatException e) {
            return false;
        }
    }

    // private boolean isLineSeparator(char c) throws IOException {
    //  in.mark(lineSeparators.length());
    //  boolean answer = ((int) c == lineSeparators.charAt(0));
    //  for (int i = 1; i < lineSeparators.length(); i++) {
    //      answer = answer && in.read() == (int) lineSeparators.charAt(i);
    //  }
    //  if (!answer) in.reset();
    //  return answer;
    // }

    private boolean isWhitespace(char ch) {
        return Character.isWhitespace(ch);
    }


    private void skipWhitespaces() throws IOException {
        if (!isWhitespace(currentChar)) {
            return;
        }
        int currentCharCode = in.read();
        if (currentCharCode == -1) {
            EOF = true;
        }
        currentChar = (char) currentCharCode;
        while (isWhitespace(currentChar) && !EOF) {
            currentCharCode = in.read();
            if (currentCharCode == -1) {
                EOF = true;
            }
            currentChar = (char) currentCharCode;
        }
    }

    private void getNext() throws IOException {
        if (isWhitespace(currentChar)) {
            return;
        }
        nextWord = new StringBuilder();
        if (EOF) {
            return;
        }
        nextWord.append(currentChar);
        while (!isWhitespace(currentChar) && !EOF) {
            int currentCharCode = in.read();
            if (currentCharCode == -1) {
                EOF = true;
            }
            currentChar = (char) currentCharCode;
            nextWord.append(currentChar);
        }
        nextWord.deleteCharAt(nextWord.length() - 1);
    }

    public Scanner(InputStream stream) throws IOException {
        in = new BufferedReader(new InputStreamReader(stream));
    }

    public Scanner(String input) throws IOException {
        in = new BufferedReader(new StringReader(input));
    }

    public Scanner(String file, String encoding) throws IOException {
        in = new BufferedReader(new InputStreamReader(
                new FileInputStream(file),
                encoding)
        );
    }

    public boolean hasNext() throws IOException {
        skipWhitespaces();
        if (!EOF && nextWord.length() == 0) {
            getNext();
        }
        return !EOF || nextWord.length() != 0;
    }

    public boolean hasNextInt() throws IOException {
        if (!hasNext()) {
            return false;
        }
        return nextWord.length() != 0 && isNumeric(nextWord.toString());
    }

    public String next() throws NoSuchElementException, IOException {
        if (hasNext()) {
            String currentWord = nextWord.toString();
            nextWord = new StringBuilder();
            return currentWord;
        } else {
            throw new NoSuchElementException();
        }
    }

    public int nextInt() throws NoSuchElementException, IOException {
        if (hasNextInt()) {
            String currentWord = nextWord.toString();
            nextWord = new StringBuilder();
            return Integer.parseInt(currentWord);
        } else {
            throw new NoSuchElementException();
        }
    }

    // public boolean hasNextLine() throws IOException {
    //  return hasNext();
    // }

    public String nextLine() throws IOException {
        StringBuilder output = new StringBuilder(nextWord);
        if (nextWord.length() != 0) {
            output.append(currentChar);
        }
        nextWord = new StringBuilder();
        int currentCharCode = in.read();
        if (currentCharCode == -1) {
            EOF = true;
        }
        currentChar = (char) currentCharCode;
        while (currentChar != '\n' && !EOF) {
            output.append(currentChar);
            currentCharCode = in.read();
            if (currentCharCode == -1) {
                EOF = true;
            }
            currentChar = (char) currentCharCode;
        }
        //currentChar = (char) in.read();
        return output.toString();
    }

    public void close() throws IOException {
        in.close();
    }
}
