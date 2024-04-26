template<typename T>
struct FloydW {
    vector<vector<T>> g;
    int n;
    int64_t INF = 1e18 + 7; //mxW 
    FloydW(int N) {
        this->n = N;
        g.resize(N, vector<T>(N, INF));
        forn(i, N) forn(j, N) if (i == j) g[i][j] = 0;
    }
    void addEdge(int u, int v, T w, int uno) {
        u -= uno; v -= uno;
        g[u][v] = min(g[u][v], w);
        g[v][u] = min(g[v][u], w);
    }

    void init() {
        forn(k, n) {
            forn(i, n) {
                forn(j, n) {
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }

    T query(int u, int v) {
        return g[u][v] == INF ? -1 : g[u][v];
    }

};