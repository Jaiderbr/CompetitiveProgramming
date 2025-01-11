/*
segment whit the maximum sum
add to segment tree the node struct
T neutro = T();
T oper(T a, T b) {node::get(a, b);}
Check the base ans
*/
constexpr int inf = (1e18);
struct node {
    int lt, rt, sum, ans;
    node() : lt(-inf), rt(-inf), sum(0), ans(-inf) {}
    node(int x) : sum(x) {
        lt = rt = ans = (x);
    }
    static node get(node& a, node& b) {
        node res;
        res.sum = a.sum + b.sum;
        res.lt = max(a.lt, a.sum + b.lt);
        res.rt = max(b.rt, b.sum + a.rt);
        res.ans = max({ a.ans, b.ans, a.rt + b.lt });
        return res;
    }
};

/*
    max(al,al+1,…,ar)−min(al,al+1,…,ar)−(r−l),
*/
constexpr int inf = (1e18);
struct node {
    int len, mxl, mxr, mnl, mnr, ans;
    node() : len(0), mxl(-inf), mxr(-inf), mnl(inf), mnr(inf), ans(0) {}
    node(int pos, int val) : len(1), mxl(val + pos), mxr(val - pos), mnl(val - pos), mnr(val + pos), ans(0) {}

    static node get(node& a, node& b) {
        node res;
        res.len = a.len + b.len;
        res.mxl = max(a.mxl, b.mxl);
        res.mxr = max(a.mxr, b.mxr);
        res.mnl = min(a.mnl, b.mnl);
        res.mnr = min(a.mnr, b.mnr);
        res.ans = max({ a.ans, b.ans, a.mxl - b.mnr, b.mxr - a.mnl });
        return res;
    }
};
