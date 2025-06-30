template<typename T>
struct STree {
    int n;
    vector<T> st;
    vector<vector<int>> tree;

    STree(vector<T>& a) {
        n = sz(a);
        st = a;
        tree.resize(n * 4);
        build(1, 0, n - 1);
    }

    void build(int node, int b, int e) {
        if (b == e) {
            tree[node].pb(st[b]);
            return;
        }
        int mid = (b + e) / 2;
        build(node * 2, b, mid); build(node * 2 + 1, mid + 1, e);
        int i = 0, j = 0;
        auto& left = tree[node * 2], & right = tree[node * 2 + 1];
        while (i < sz(left) && j < sz(right)) {
            if (left[i] <= right[j]) tree[node].pb(left[i++]);
            else tree[node].pb(right[j++]);
        }
        while (i < sz(left)) tree[node].pb(left[i++]);
        while (j < sz(right)) tree[node].pb(right[j++]);
    }

    T count_greater(int node, int v) { return tree[node].end() - upper_bound(all(tree[node]), v); }
    T count_ge(int node, int v) { return tree[node].end() - lower_bound(all(tree[node]), v); }
    T count_less(int node, int v) { return lower_bound(all(tree[node]), v) - tree[node].begin(); }
    T count_le(int node, int v) { return upper_bound(all(tree[node]), v) - tree[node].begin(); }
    T count_equal(int node, int v) { return count_le(node, v) - count_less(node, v); }
    T count_between(int node, int a, int b) { return count_le(node, b) - count_less(node, a); }

    template<typename F>
    T query(int node, int b, int e, int i, int j, int v, F func) {
        if (j < b || e < i) return 0;
        if (b >= i && e <= j) return func(node, v);
        int mid = (b + e) / 2;
        return query(node * 2, b, mid, i, j, v, func) + query(node * 2 + 1, mid + 1, e, i, j, v, func);
    }
    // [a,b]
    T query_between(int l, int r, int a, int b) {
        return query(1, 0, n - 1, l, r, 0, [this, a, b](int node, int) { return count_between(node, a, b);});
    }
    // >
    T query_greater(int l, int r, int v) {
        return query(1, 0, n - 1, l, r, v, [this](int node, int val) { return count_greater(node, val); });
    }
    // >=
    T query_ge(int l, int r, int v) {
        return query(1, 0, n - 1, l, r, v, [this](int node, int val) { return count_ge(node, val); });
    }
    // <
    T query_less(int l, int r, int v) {
        return query(1, 0, n - 1, l, r, v, [this](int node, int val) { return count_less(node, val); });
    }
    // <=
    T query_le(int l, int r, int v) {
        return query(1, 0, n - 1, l, r, v, [this](int node, int val) { return count_le(node, val); });
    }
    // ==
    T query_equal(int l, int r, int v) {
        return query(1, 0, n - 1, l, r, v, [this](int node, int val) { return count_equal(node, val); });
    }
    // 0- index
};