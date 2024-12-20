struct FlowEdge {
    int v, u;
    ll cap, flow = 0;
    FlowEdge(int _v, int _u, ll _cap) : v(_v), u(_u), cap(_cap) {}
};

struct Dinic { // O(V^2 * E)
    const ll flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> g;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        g.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, ll cap) {
        edges.eb(v, u, cap);
        edges.eb(u, v, 0);
        g[v].pb(m);
        g[u].pb(m + 1);
        m += 2;
    }

    bool bfs() {
        while (sz(q)) {
            int v = q.front();
            q.pop();
            for (int id : g[v]) {
                if (edges[id].cap - edges[id].flow < 1) continue;
                if (level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, ll pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        for (int& cid = ptr[v]; cid < sz(g[v]); ++cid) {
            int id = g[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll flow() {
        ll f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }

    vector<pair<int,int>> min_cut() {
        vector<pair<int,int>> cut;
        for (auto& e : edges)
            if (level[e.v] != -1 && level[e.u] == -1 && e.cap > 0)
                cut.pb({ e.v, e.u });
        return cut;
    }
};

// Min Vertex Cover: vertices de L con level[v]==-1 y vertices de R con level[v]>0
// Max Independent Set: vertices NO tomados por el Min Vertex Cover