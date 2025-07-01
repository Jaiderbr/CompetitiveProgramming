// constexpr int mxN = 2500 + 50;
constexpr int inf = 1e9 + 7;
vector<int>adj[mxN];
int n, m;
int cycle_len(int start) {
    int ans = inf;

    vector<int> dist(n, -1);
    queue<int> bfs;

    dist[start] = 0;
    bfs.push(start);

    while (!bfs.empty()) {
        int node = bfs.front();
        bfs.pop();
        for (int adj_node : adj[node]) {
            if (dist[adj_node] == -1) {
                dist[adj_node] = dist[node] + 1;
                bfs.push(adj_node);
            }
            else if (dist[adj_node] >= dist[node]) {
                ans = min(ans, 1 + dist[adj_node] + dist[node]);
            }
        }
    }
    return ans;
}