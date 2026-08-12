// constexpr int MAX = 3e5 + 100;

vector<int> g[MAX];
int dis[MAX], par[MAX];

pair<int, vector<int>> center() {
    int f, df;
    function<void(int)> dfs = [&](int v) {
        if (dis[v] > df) f = v, df = dis[v];
        for (int u : g[v]) if (u != par[v])
            dis[u] = dis[v] + 1, par[u] = v, dfs(u);
        };

    f = df = par[0] = -1, dis[0] = 0;
    dfs(0);
    int root = f;
    f = df = par[root] = -1, dis[root] = 0;
    dfs(root);

    vector<int> c_node;
    while (f != -1) {
        if (dis[f] == df / 2 or dis[f] == (df + 1) / 2) c_node.pb(f);
        f = par[f];
    }

    return { df, c_node };
}

