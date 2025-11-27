template<typename T> struct Bit {
    array<vector<T>, 2> bit;

    int n;
    Bit(int n2) {
        n = n2;
        bit = { vector<T>(n + 1), vector<T>(n + 1) };
    }
    Bit(int n2, vector<int>& v) {
        n = n2;
        bit = { vector<T>(n + 1), vector<T>(n + 1) };

        for (int i = 1; i <= n; i++)
            bit[1][min(n + 1, i + (i & -i))] += bit[1][i] += v[i - 1];
    }
    T get(int x, int i) {
        T ret = 0;
        for (; i; i -= i & -i) ret += bit[x][i];
        return ret;
    }
    void add(int x, int i, T val) {
        for (; i <= n; i += i & -i) bit[x][i] += val;
    }
    T get2(int p) {
        return get(0, p) * p + get(1, p);
    }
    T query(int l, int r) {
        return get2(r + 1) - get2(l);
    }
    void update(int l, int r, T x) {
        add(0, l + 1, x), add(0, r + 2, -x);
        add(1, l + 1, -x * l), add(1, r + 2, x * (r + 1));
    }
};
