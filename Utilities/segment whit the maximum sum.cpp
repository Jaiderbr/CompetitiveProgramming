/*
segment whit the maximum sum    
add to segment tree the node struct
T neutro = T();
T oper(T a, T b) {node::get(a, b);}
Check the base ans
*/
constexpr int inf=(1e18);
struct node {
    int lt, rt, sum, ans;
    node() : lt(-inf), rt(-inf), sum(0), ans(-inf) {}
    node(int x) : sum(x) {
        lt = rt = ans = (x);
    }
    static node get(node &a, node&b) {
        node res;
        res.sum = a.sum + b.sum;
        res.lt = max(a.lt, a.sum + b.lt);
        res.rt = max(b.rt, b.sum + a.rt);
        res.ans = max({ a.ans, b.ans, a.rt + b.lt });
        return res;
    }
};
