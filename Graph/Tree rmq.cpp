// Minimum/Maximum query on paths.
// build - O(n log(n))
// query - O(log(n))

int n;
constexpr int INF = ;
namespace linetree {
    int id[MAX], seg[2 * MAX], pos[MAX];
    vector<int> v[MAX], val[MAX];
    vector<pair<int, pair<int, int> >> ar;

    void add(int a, int b, int p) { ar.pb({ p, {a, b} }); }
    void build() {
        sort(ar.rbegin(), ar.rend());
        for (int i = 0; i < n; i++) id[i] = i, v[i] = { i }, val[i].clear();
        for (auto i : ar) {
            int a = id[i.s.f], b = id[i.s.s];
            if (a == b) continue;
            if (sz(v[a]) < sz(v[b])) swap(a, b);
            for (auto j : v[b]) id[j] = a, v[a].pb(j);
            val[a].pb(i.f);
            for (auto j : val[b]) val[a].pb(j);
            v[b].clear(), val[b].clear();
        }
        vector<int> vv;
        for (int i = 0; i < n; i++) for (int j = 0; j < sz(v[i]); j++) {
            pos[v[i][j]] = sz(vv);
            if (j + 1 < sz(v[i])) vv.pb(val[i][j]);
            else vv.pb(0);
        }
        for (int i = n; i < 2 * n; i++) seg[i] = vv[i - n];
        for (int i = n - 1; i; i--) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }
    int query(int a, int b) {
        if (id[a] != id[b]) return 0; // They are not connected.
        a = pos[a], b = pos[b];
        if (a > b) swap(a, b);
        b--;
        int ans = INF;
        for (a += n, b += n; a <= b; ++a /= 2, --b /= 2) ans = min<int>({ ans, seg[a], seg[b] });
        return ans;
    }
};
