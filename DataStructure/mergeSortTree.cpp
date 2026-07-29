template <typename T = int> struct ms_tree {
    vector<tuple<T, T, int>> v;
    int n;
    vector<vector<tuple<T, T, int>>> t; // {y, idx, left}
    vector<T> vy;

    ms_tree(vector<pair<T, T>>& vv) : n(vv.size()), t(4 * n), vy(n) {
        for (int i = 0; i < n; i++) v.push_back({ vv[i].first, vv[i].second, i });
        sort(v.begin(), v.end());
        build(1, 0, n - 1);
        for (int i = 0; i < n; i++) vy[i] = get<0>(t[1][i + 1]);
    }
    ms_tree(vector<T>& vv, bool inv = false) { // inv: inverte indice e valor
        vector<pair<T, T>> v2;
        for (int i = 0; i < (int)vv.size(); i++) inv ? v2.push_back({ vv[i], i }) : v2.push_back({ i, vv[i] });
        *this = ms_tree(v2);
    }
    void build(int p, int l, int r) {
        t[p].push_back({ get<0>(v[l]), get<0>(v[r]), 0 }); // {min_x, max_x, 0}
        if (l == r) return t[p].push_back({ get<1>(v[l]), get<2>(v[l]), 0 });
        int m = (l + r) / 2;
        build(2 * p, l, m), build(2 * p + 1, m + 1, r);

        int L = 0, R = 0;
        while (t[p].size() <= r - l + 1) {
            int left = get<2>(t[p].back());
            if (L > m - l or (R + m + 1 <= r and t[2 * p + 1][1 + R] < t[2 * p][1 + L])) {
                t[p].push_back(t[2 * p + 1][1 + R++]);
                get<2>(t[p].back()) = left;
                continue;
            }
            t[p].push_back(t[2 * p][1 + L++]);
            get<2>(t[p].back()) = left + 1;
        }
    }

    int get_l(T y) { return lower_bound(vy.begin(), vy.end(), y) - vy.begin(); } // primeiro >= y
    int get_r(T y) { return upper_bound(vy.begin(), vy.end(), y) - vy.begin(); } // primeiro > y

    // dfs generico: conta elementos com x em [x1,x2] cujo "rank" (posicao no y-sorted)
    // esta em [l, r)
    int dfs_count(int p, int l, int r, T x1, T x2) {
        if (l == r or x2 < get<0>(t[p][0]) or get<1>(t[p][0]) < x1) return 0;
        if (x1 <= get<0>(t[p][0]) and get<1>(t[p][0]) <= x2) return r - l;
        int nl = get<2>(t[p][l]), nr = get<2>(t[p][r]);
        return dfs_count(2 * p, nl, nr, x1, x2) + dfs_count(2 * p + 1, l - nl, r - nr, x1, x2);
    }
    // between [a,b]
    int count(T x1, T x2, T y1, T y2) {
        if (x1 > x2) return 0;
        return dfs_count(1, get_l(y1), get_r(y2), x1, x2);
    }

    // >
    int count_greater(T x1, T x2, T val) {
        if (x1 > x2) return 0;
        return dfs_count(1, get_r(val), n, x1, x2);
    }
    // >=
    int count_ge(T x1, T x2, T val) {
        if (x1 > x2) return 0;
        return dfs_count(1, get_l(val), n, x1, x2);
    }
    // <
    int count_less(T x1, T x2, T val) {
        if (x1 > x2) return 0;
        return dfs_count(1, 0, get_l(val), x1, x2);
    }
    // <=
    int count_le(T x1, T x2, T val) {
        if (x1 > x2) return 0;
        return dfs_count(1, 0, get_r(val), x1, x2);
    }
    // ==
    int count_equal(T x1, T x2, T val) {
        if (x1 > x2) return 0;
        return dfs_count(1, get_l(val), get_r(val), x1, x2);
    }

    void dfs_report(int p, int l, int r, T x1, T x2, vector<int>& ret) {
        if (l == r or x2 < get<0>(t[p][0]) or get<1>(t[p][0]) < x1) return;
        if (x1 <= get<0>(t[p][0]) and get<1>(t[p][0]) <= x2) {
            for (int i = l; i < r; i++) ret.push_back(get<1>(t[p][i + 1]));
            return;
        }
        int nl = get<2>(t[p][l]), nr = get<2>(t[p][r]);
        dfs_report(2 * p, nl, nr, x1, x2, ret);
        dfs_report(2 * p + 1, l - nl, r - nr, x1, x2, ret);
    }

    // between [a,b]
    vector<int> report(T x1, T x2, T y1, T y2) {
        vector<int> ret;
        if (x1 > x2) return ret;
        dfs_report(1, get_l(y1), get_r(y2), x1, x2, ret);
        return ret;
    }

    // >
    vector<int> report_greater(T x1, T x2, T val) {
        vector<int> ret;
        if (x1 > x2) return ret;
        dfs_report(1, get_r(val), n, x1, x2, ret);
        return ret;
    }
    // >=
    vector<int> report_ge(T x1, T x2, T val) {
        vector<int> ret;
        if (x1 > x2) return ret;
        dfs_report(1, get_l(val), n, x1, x2, ret);
        return ret;
    }
    // <
    vector<int> report_less(T x1, T x2, T val) {
        vector<int> ret;
        if (x1 > x2) return ret;
        dfs_report(1, 0, get_l(val), x1, x2, ret);
        return ret;
    }
    // <=
    vector<int> report_le(T x1, T x2, T val) {
        vector<int> ret;
        if (x1 > x2) return ret;
        dfs_report(1, 0, get_r(val), x1, x2, ret);
        return ret;
    }
    // ==
    vector<int> report_equal(T x1, T x2, T val) {
        vector<int> ret;
        if (x1 > x2) return ret;
        dfs_report(1, get_l(val), get_r(val), x1, x2, ret);
        return ret;
    }
    int kth(T y1, T y2, int k) {
        function<int(int, int, int)> dfs = [&](int p, int l, int r) {
            if (k >= r - l) {
                k -= r - l;
                return -1;
            }
            if (r - l == 1) return get<1>(t[p][l + 1]);
            int nl = get<2>(t[p][l]), nr = get<2>(t[p][r]);
            int left = dfs(2 * p, nl, nr);
            if (left != -1) return left;
            return dfs(2 * p + 1, l - nl, r - nr);
            };
        return dfs(1, get_l(y1), get_r(y2));
    }
};
