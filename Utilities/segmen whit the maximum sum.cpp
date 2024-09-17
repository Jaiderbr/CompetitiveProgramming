/*
segment whit the maximum sum    
add to segment tree the node struct
T neutro = T();
T oper(T a, T b) {T res; return res.get(a, b);}
*/
struct node {
    int lt, rt, sum, ans;
    node() : lt(0), rt(0), sum(0), ans(0) {}
    node(int x) : sum(x) {
        lt = rt = ans = max(0ll, x);
    }
    node get(node& a, node& b) {
        sum = a.sum + b.sum;
        lt = max(a.lt, a.sum + b.lt);
        rt = max(b.rt, b.sum + a.rt);
        ans = max({ a.ans, b.ans, a.rt + b.lt });
        return *this;
    }
};