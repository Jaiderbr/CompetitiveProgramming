struct HPTK {
    int nL, nR;
    vector<vector<int>> adj;
    vector<int> mL, mR, dist;

    const int INF = 1000000007;

    HPTK(int nLeft_, int nRight_) {
        nL = nLeft_, nR = nRight_;
        adj.assign(nL, {});
        mL.assign(nL, -1);
        mR.assign(nR, -1);
        dist.assign(nL, 0);
    }

    void add(int u, int v) { adj[u].pb(v); }
    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; u++) {
            if (mL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            }
            else dist[u] = INF;
        }
        bool f = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] >= INF) continue;
            for (int v : adj[u]) {
                int u2 = mR[v];
                if (u2 != -1) {
                    if (dist[u2] == INF) {
                        dist[u2] = dist[u] + 1;
                        q.push(u2);
                    }
                }
                else f = 1;
            }
        }
        return f;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = mR[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                mL[u] = v; mR[v] = u;
                return 1;
            }
        }
        dist[u] = INF;
        return 0;
    }

    int maxMatching() {
        int m = 0;
        while (bfs()) {
            for (int u = 0; u < nL; u++) {
                if (mL[u] == -1) {
                    if (dfs(u)) m++;
                }
            }
        }
        return m;
    }

    vector<pair<int, int>> getMatchingEdges() {
        vector<pair<int, int>> res;
        for (int u = 0; u < nL; u++) {
            if (mL[u] != -1) {
                res.pb({ u, mL[u] });
            }
        }
        return res;
    }

};
