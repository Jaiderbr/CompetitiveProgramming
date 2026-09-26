template<typename T>
struct STree {
    int n;
    vector<T> st, lazy_mul, lazy_add, lazy_set;
    vector<bool> has_set;
    T neutro = T(INT_MAX);

    STree(int m) {
        n = m;
        st.resize(n * 4, 0);
        lazy_mul.resize(n * 4, 1);
        lazy_add.resize(n * 4, 0);
        lazy_set.resize(n * 4, 0);
        has_set.resize(n * 4, false);
    }

    STree(vector<T>& a) {
        n = sz(a);
        st.resize(n * 4);
        lazy_mul.resize(n * 4, 1);
        lazy_add.resize(n * 4, 0);
        lazy_set.resize(n * 4, 0);
        has_set.resize(n * 4, false);
        build(1, 0, n - 1, a);
    }

    T oper(T a, T b) { return (a + b); }

    void build(int v, int tl, int tr, vector<T>& a) {
        if (tl == tr) {
            st[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, a);
        build(v * 2 + 1, tm + 1, tr, a);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }

    void push(int v, int tl, int tr) {
        if (has_set[v]) {
            st[v] = (tr - tl + 1) * lazy_set[v];
            if (tl != tr) {
                has_set[v * 2] = true;
                lazy_set[v * 2] = lazy_set[v];
                lazy_mul[v * 2] = 1;
                lazy_add[v * 2] = 0;

                has_set[v * 2 + 1] = true;
                lazy_set[v * 2 + 1] = lazy_set[v];
                lazy_mul[v * 2 + 1] = 1;
                lazy_add[v * 2 + 1] = 0;
            }
            has_set[v] = false;
            lazy_set[v] = 0;
        }

        if (lazy_mul[v] != 1) {
            st[v] *= lazy_mul[v];
            if (tl != tr) {
                lazy_mul[v * 2] *= lazy_mul[v];
                lazy_add[v * 2] *= lazy_mul[v];

                lazy_mul[v * 2 + 1] *= lazy_mul[v];
                lazy_add[v * 2 + 1] *= lazy_mul[v];
            }
            lazy_mul[v] = 1;
        }

        if (lazy_add[v] != 0) {
            st[v] += (tr - tl + 1) * lazy_add[v];  // min o max sin (tr - tl + 1)
            if (tl != tr) {
                lazy_add[v * 2] += lazy_add[v];
                lazy_add[v * 2 + 1] += lazy_add[v];
            }
            lazy_add[v] = 0;
        }
    }

    void upd_add(int v, int tl, int tr, int l, int r, T val) {
        push(v, tl, tr);
        if (tr < l || tl > r) return;
        if (tl >= l && tr <= r) {
            lazy_add[v] += val;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd_add(v * 2, tl, tm, l, r, val);
        upd_add(v * 2 + 1, tm + 1, tr, l, r, val);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }

    void upd_mul(int v, int tl, int tr, int l, int r, T val) {
        push(v, tl, tr);
        if (tr < l || tl > r) return;
        if (tl >= l && tr <= r) {
            lazy_mul[v] *= val;
            lazy_add[v] *= val;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd_mul(v * 2, tl, tm, l, r, val);
        upd_mul(v * 2 + 1, tm + 1, tr, l, r, val);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }

    void upd_set(int v, int tl, int tr, int l, int r, T val) {
        push(v, tl, tr);
        if (tr < l || tl > r) return;
        if (tl >= l && tr <= r) {
            has_set[v] = true;
            lazy_set[v] = val;
            lazy_mul[v] = 1;
            lazy_add[v] = 0;
            push(v, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd_set(v * 2, tl, tm, l, r, val);
        upd_set(v * 2 + 1, tm + 1, tr, l, r, val);
        st[v] = oper(st[v * 2], st[v * 2 + 1]);
    }

    T query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (tl > r || tr < l) return neutro;
        if (l <= tl && tr <= r) return st[v];
        int tm = (tl + tr) / 2;
        return oper(query(v * 2, tl, tm, l, r), query(v * 2 + 1, tm + 1, tr, l, r));
    }

    void add(int l, int r, T val) { upd_add(1, 0, n - 1, l, r, val); }
    void sub(int l, int r, T val) { upd_add(1, 0, n - 1, l, r, -val); }
    void mul(int l, int r, T val) { upd_mul(1, 0, n - 1, l, r, val); }
    void set_val(int l, int r, T val) { upd_set(1, 0, n - 1, l, r, val); }
    void reset(int l, int r) { upd_set(1, 0, n - 1, l, r, 0); }
    T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
