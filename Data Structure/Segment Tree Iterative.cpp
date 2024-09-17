template<typename T>
struct STree {
    vector<T> st;
    int n;
    T neutro = T(0);
    T oper(T a, T b) { return a + b; }
    STree(vector<T>& a) {
        n = sz(a);
        st.resize(n * 2);
        forn(i, n) st[n + i] = a[i];
        for (int i = n - 1; i >= 1; i -= 1) st[i] = oper(st[i << 1], st[i << 1 | 1]);
    }

    void upd(int p, T val) {
        for (st[p += n] = val; p > 1; p >>= 1) st[p >> 1] = oper(st[p], st[p ^ 1]);
    }

    T query(int l, int r) { //[l, r)
        T v = neutro;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) v = oper(v, st[l++]);
            if (r & 1) v = oper(v, st[--r]);
        }
        return v;
    }
};