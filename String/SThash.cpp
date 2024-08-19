
/*
query = or.query(l, r)  ror.query(n - 1 - r, n - 1 - l)
udp   = or.upd(pos, a)  ror.upd(n - 1 - pos, a);

LLAMAR PRECAL!!!!!!!!!!!!!!!!!!!!!!!!!!

*/
const int MAX = 2e5 + 6;
const int MOD = 1e9 + 7;
const int BASE = 137;

int BP[MAX];
void precal() {
    BP[0] = 1;
    BP[1] = 1;
    for (int i = 1;i < MAX;i++) {
        BP[i] = (BP[i - 1] * BASE) % MOD;
    }
}
template<typename T>
struct SThash {
    struct node {
        int tam;
        int h;
        node() {}
    };
    int n;
    vector<node>tree;
    SThash(string& s) {
        n = sz(s);
        vector<T> a(n);
        tree.resize(n * 4);
        for (int i = 0;i < n;i++) a[i] = s[i];
        build(1, 0, n - 1, a);
    }

    node Merge(node a, node b) {
        node ret;
        ret.h = ((a.h * BP[b.tam]) + b.h) % MOD;
        ret.tam = a.tam + b.tam;
        return ret;
    }

    void build(int v, int tl, int tr, vector<T>& a) {
        if (tl == tr) {
            tree[v].h = a[tl];
            tree[v].tam = 1;
            return;
        }
        int mid = (tl + tr) >> 1;
        build(v * 2, tl, mid, a);
        build(v * 2 + 1, mid + 1, tr, a);
        tree[v] = Merge(tree[v * 2], tree[v * 2 + 1]);
    }


    void upd(int v, int tl, int tr, int id, int val) {
        if (tl > id or tr < id) return;
        if (tl == tr and tr == id) {
            tree[v].h = val;
            return;
        }
        int mid = (tl + tr) >> 1;
        upd(v * 2, tl, mid, id, val);
        upd(v * 2 + 1, mid + 1, tr, id, val);
        tree[v] = Merge(tree[v * 2], tree[v * 2 + 1]);
    }

    node query(int v, int tl, int tr, int l, int r) {
        if (tl >= l and tr <= r) return tree[v];
        int mid = (tl + tr) / 2;
        if (mid < l) return query(v + v + 1, mid + 1, tr, l, r);
        else if (mid >= r) return query(v + v, tl, mid, l, r);
        else return Merge(query(v + v, tl, mid, l, r), query(v + v + 1, mid + 1, tr, l, r));
    }
    void upd(int pos, int val) { upd(1, 0, n - 1, pos, val); }
    int query(int l, int r) { return query(1, 0, n - 1, l, r).h; }
};
