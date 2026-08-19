// build - O(n log(n))
// lca - O(log(n))

constexpr int MAX = 2e5 + 10;
constexpr int MAX2 = __lg(MAX) + 1;
vector<vector<int> > g(MAX);
int n, p;
int pai[MAX2][MAX];
int in[MAX], out[MAX];

void dfs(int k) {
    in[k] = p++;
    for (int i = 0; i < (int)g[k].size(); i++) {
        if (in[g[k][i]] == -1) { pai[0][g[k][i]] = k; dfs(g[k][i]); }
    }
    out[k] = p++;
}

void build(int raiz) {
    for (int i = 0; i < n; i++) pai[0][i] = i;
    p = 0, memset(in, -1, sizeof in);
    dfs(raiz);

    // parent preprocessing
    for (int k = 1; k < MAX2; k++) for (int i = 0; i < n; i++) {
        pai[k][i] = pai[k - 1][pai[k - 1][i]];
    }
}

bool anc(int a, int b) { // if a is an ancestor of b
    return in[a] <= in[b] and out[a] >= out[b];
}

int lca(int a, int b) {
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;
    // move up
    for (int k = MAX2 - 1; k >= 0; k--)
        if (!anc(pai[k][a], b)) a = pai[k][a];

    return pai[0][a];
}


//------------------------------------------------------------
// build - O(n)
// kth, lca, dist - O(log(n))

constexpr int MAX = 2e5 + 5;
int depth[MAX], parent[MAX], pp[MAX];
 
void set_root(int i) { parent[i] = pp[i] = i, depth[i] = 0; }
 
void add_leaf(int i, int u) {
    parent[i] = u, depth[i] = depth[u] + 1;
    pp[i] = 2 * depth[pp[u]] == depth[pp[pp[u]]] + depth[u] ? pp[pp[u]] : u;
}
 
int kth(int i, int k) {
    int dd = max<int>(0, depth[i] - k);
    while (depth[i] > dd) i = depth[pp[i]] >= dd ? pp[i] : parent[i];
    return i;
}
 
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    while (depth[a] > depth[b]) a = depth[pp[a]] >= depth[b] ? pp[a] : parent[a];
    while (a != b) {
        if (pp[a] != pp[b]) a = pp[a], b = pp[b];
        else a = parent[a], b = parent[b];
    }
    return a;
}
 
int dist(int a, int b) { return depth[a] + depth[b] - 2 * depth[lca(a, b)]; }
 
vector<int> g[MAX];
 
void build(int i, int pai = -1) {
    if (pai == -1) set_root(i);
    for (int j : g[i]) if (j != pai) {
        add_leaf(j, i);
        build(j, i);
    }
}

