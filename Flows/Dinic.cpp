constexpr int INF = ((1ULL << 63) - 1) >> 1;

struct Dinic {
    const bool scaling = 0;     // con scaling -> O(nm log(MAXCAP)),
    int lim;                    // con constante alta
    struct edge {
        int to, cap, rev, flow;
        bool res;
        edge(int to_, int cap_, int rev_, bool res_) : to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
    };

    vector<vector<edge>> g;
    vector<int> lev, beg;
    int64_t F;
    Dinic(int n) : g(n), F(0) {}

    void add(int a, int b, int c) {
        g[a].eb(b, c, sz(g[b]), 0);
        g[b].eb(a, 0, sz(g[a]) - 1, 1);
    }
    bool bfs(int s, int t) {
        lev = vector<int>(sz(g), -1); lev[s] = 0;
        beg = vector<int>(sz(g), 0);
        queue<int> q; q.push(s);
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (auto& i : g[u]) {
                if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
                if (scaling and i.cap - i.flow < lim) continue;
                lev[i.to] = lev[u] + 1;
                q.push(i.to);
            }
        }
        return lev[t] != -1;
    }
    int dfs(int v, int s, int f = INF) {
        if (!f or v == s) return f;
        for (int& i = beg[v]; i < sz(g[v]); i++) {
            auto& e = g[v][i];
            if (lev[e.to] != lev[v] + 1) continue;
            int foi = dfs(e.to, s, min(f, e.cap - e.flow));
            if (!foi) continue;
            e.flow += foi, g[e.to][e.rev].flow -= foi;
            return foi;
        }
        return 0;
    }

    int64_t max_flow(int s, int t) {
        for (lim = scaling ? (1 << 30) : 1; lim; lim /= 2)
            while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
        return F;
    }
};

// Recupera las aristas del corte s-t
vector<pair<int, int>> get_cut(Dinic& g, int s, int t) {
    g.max_flow(s, t);
    vector<pair<int, int>> cut;
    vector<int> vis(sz(g.g), 0), st = { s };
    vis[s] = 1;
    while (sz(st)) {
        int u = st.back(); st.pop_back();
        for (auto e : g.g[u]) if (!vis[e.to] and e.flow < e.cap)
            vis[e.to] = 1, st.pb(e.to);
    }
    for (int i = 0; i < sz(g.g); i++) for (auto e : g.g[i])
        if (vis[i] and !vis[e.to] and !e.res) cut.eb(i, e.to);
    return cut;
}