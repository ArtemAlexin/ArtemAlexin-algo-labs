import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class Main {
    public static final long mod = (int)1e9;
    static int[] par;
    static boolean[] used;
    public static int find(int x) {
       if(par[x] == x) return x;
       return par[x] = find(par[x]);
    }
    public static void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x > y)
            par[y] = x;
        else
            par[x] = y;
    }
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), m = in.nextInt();
        Cortesian tree = new Cortesian();
        par = new int[2 * Math.max(m, n) + 2];
        used = new boolean[2 * Math.max(m, n) + 2];
        for(int i = 0; i < used.length; i++) {
            par[i] = i;
            used[i] = false;
        }
        for(int i = 0; i < used.length; i++) {
            tree.insert(i, 0);
        }
        for(int i = 0; i < n; i++) {
            int l = in.nextInt();
            if(!used[l - 1]) {
                tree.find(l).value = i + 1;
                used[l - 1] = true;
                doIt(l - 1);
            } else {
                Node a = tree.find(l);
                int p = find(l - 1);
                p++;
                Pair p1 = tree.split2(tree.root, l - 1);
                int f = p - l + 1;
                Pair p2 = tree.split2(p1.second, f);
                Pair p3 = tree.split2(p2.second, 1);
                p3.first.value = i + 1;
                used[p3.first.x] = true;
                tree.root = Cortesian.merge(Cortesian.merge(p1.first, p3.first), Cortesian.merge(p2.first, p3.second));
                doIt(p3.first.x);
            }
        }
        tree.print(tree.root);
        int i;
        for(i = ans.size() - 1; i >= 0 && ans.get(i) == 0; i--);
        System.out.println(i + 1);
        for(int j = 0; j <= i; j++)
            System.out.print(ans.get(j) + " ");
    }
    public static void doIt(int l) {
        if(l <= used.length && used[l + 1]) {
            merge(l, l + 1);
        }
        if(l > 0 && used[l - 1]) {
            merge(l, l - 1);
        }
    }
    static List<Integer> ans = new ArrayList<>();
    static class Scanner implements AutoCloseable {

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
            } catch (NumberFormatException e) {
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
    public static class Cortesian {
        public Node root;
        private int size;
        public Cortesian() {
            root = null;
            size = 0;
        }

        public Cortesian(Node root) {
            this.root = root;
            this.size = root.size;
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
        private static int size(Node x) {
            if(x == null) return 0;
            return x.size;
        }
        private static long sum(Node x) {
            if(x == null) return 0;
            return x.sum;
        }
        public void print(Node cur) {
            if(cur == null) return;
            print(cur.left);
            ans.add(cur.value);
            print(cur.right);
        }
        private static void update(Node x) {
            if(x == null) return;
            x.size = size(x.left) + size(x.right) + 1;
            x.sum = sum(x.left) + sum(x.right) + x.x;
        }
        public Node find(int s) {
            Node cur = root;
            while(size(cur.left) + 1 != s) {
                if(size(cur.left) < s) {
                    s = s - size(cur.left) - 1;
                    cur = cur.right;
                } else {
                    cur = cur.left;
                }
            }
            return cur;
        }
        public long summurize(int l, int r) {
            Pair a1 = split(root, l - 1);
            Pair a2 = split(a1.second, r);
            long ans = sum(a2.first);
            root = merge(merge(a1.first, a2.first), a2.second);
            return ans;
        }
        public Pair split2(Node root, int size) {
            if(root == null) return new Pair(null, null);
            if(size(root.left) >= size) {
                Pair t = split2(root.left, size);
                root.left = t.second;
                update(root);
                return  new Pair(t.first, root);
            } else {
                Pair t = split2(root.right, size - size(root.left) - 1);
                root.right = t.first;
                update(root);
                return new Pair(root, t.second);
            }
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
        public static Node merge(Node root1, Node root2) {
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
                this.root = merge(merge(t.first, new Node(x, 0)),t.second);
                size++;
            }
        }
        public void insert(int x, int value) {
            if(!exists(x)) {
                Pair t = split(this.root, x);
                this.root = merge(merge(t.first, new Node(x, value)),t.second);
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
        public int num;
        public int size;
        public long sum;
        public int value;
        Node left;
        Node right;
        Node(int x, int value) {
            this.x = x;
            this.y = (int) (Math.random() * 1000000);
            size = 1;
            this.sum = x;
            this.value = value;
        }

        public Node(int x, int y, int i) {
            this.x = x;
            this.y = y;
            num = i;
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

    public static class Pair2 implements Comparable<Pair2>{
        int x;
        int y;
        int id;
        public Pair2(int x, int y, int id) {
            this.x = x;
            this.y = y;
            this.id = id;
        }

        @Override
        public int compareTo(Pair2 o) {
            if(x == o.x) return Integer.compare(y, o.y);
            return Integer.compare(x, o.x);
        }
    }

    public static class Tupple4 {
        int num;
        int par;
        int left;
        int right;

        public Tupple4(int num, int par, int left, int right) {
            this.num = num;
            this.par = par;
            this.left = left;
            this.right = right;
        }
    }
}
