template<typename T>
struct Graph {
    int n;
    vector<vector<T>> adj;
    vector<T> side;
    Graph(int size) {
        n = size;
        adj.resize(n);
        side.resize(n, -1);
    }

    void addEdge(int u, int v, int uno) {
        v -= uno; u -= uno;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool is_bipartite() {
        bool check = true;
        queue<int> q;
        for (int edge = 0; edge < n; ++edge) {
            if (side[edge] == -1) {
                q.push(edge);
                side[edge] = 0;
                while (q.size()) {
                    int curr = q.front();
                    q.pop();
                    for (auto neig : adj[curr]) {
                        if (side[neig] == -1) {
                            side[neig] = (1 ^ side[curr]);
                            q.push(neig);
                        }
                        else {
                            check &= (side[neig] != side[curr]);
                        }
                    }
                }
            }
        }
        return check;
    }
};
