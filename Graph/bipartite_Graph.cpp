
class Graph {
    int n;
    vector<vector<int>> adj;
    vector<int> side;

public:
    explicit Graph(int size) {
        n = size;
        adj.resize(n);
        side.resize(n, -1);
    }

    void addEdge(int u, int v) {
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    bool is_bipartite() {
        bool check = true;
        queue<int> q;
        for (int current_edge = 0; current_edge < n; ++current_edge) {
            if (side[current_edge] == -1) {
                q.push(current_edge);
                side[current_edge] = 0;
                while (q.size()) {
                    int current = q.front();
                    q.pop();
                    for (auto neighbour : adj[current]) {
                        if (side[neighbour] == -1) {
                            side[neighbour] = (1 ^ side[current]);
                            q.push(neighbour);
                        }
                        else {
                            check &= (side[neighbour] != side[current]);
                        }
                    }
                }
            }
        }
        return check;
    }
};


