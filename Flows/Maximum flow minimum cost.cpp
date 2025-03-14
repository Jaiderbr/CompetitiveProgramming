struct mcmf {
    const ll INF = LONG_LONG_MAX;
    struct Edge { int to, rev; ll flo, cap, cost; };
    int n;
    vector<ll> p, dist;
    vector<pair<int, int>> pre;
    vector<vector<Edge>> g;

    mcmf(int m) : n(m), p(n), dist(n), pre(n), g(n) {}

    void add_edge(int v, int u, ll cap, ll cost) {
        g[v].pb({ u, sz(g[u]), 0, cap, cost });
        g[u].pb({ v, sz(g[v]) - 1, 0, 0, -cost });
    }

    bool path(int s, int t) {
        dist.assign(n, INF);
        using T = pair<ll, int>;
        priority_queue<T, vector<T>, greater<T>> todo;
        todo.push({ dist[s] = 0, s });
        while (sz(todo)) {
            T x = todo.top(); todo.pop();
            if (x.f > dist[x.s]) continue;
            for (auto& e : g[x.s]) {
                if (e.flo < e.cap && dist[e.to] > x.f + e.cost + p[x.s] - p[e.to]) {
                    dist[e.to] = x.f + e.cost + p[x.s] - p[e.to];
                    pre[e.to] = { x.s, e.rev };
                    todo.push({ dist[e.to], e.to });
                }
            }
        }
        return dist[t] != INF;
    }

    pair<ll, ll> calc(int s, int t) {
        forn(_, n) forn(i, n) for (auto& e : g[i])
            if (e.cap) p[e.to] = min(p[e.to], p[i] + e.cost);
        ll totFlow = 0, totCost = 0;
        while (path(s, t)) {
            forn(i, n) p[i] += dist[i];
            ll df = INF;
            for (int x = t; x != s; x = pre[x].f) {
                Edge& e = g[pre[x].f][g[x][pre[x].s].rev];
                df = min(df, e.cap - e.flo);
            }
            totFlow += df; totCost += (p[t] - p[s]) * df;
            for (int x = t; x != s; x = pre[x].f) {
                Edge& e = g[x][pre[x].s]; e.flo -= df;
                g[pre[x].f][e.rev].flo += df;
            }
        }
        return { totFlow, totCost };
    }
};