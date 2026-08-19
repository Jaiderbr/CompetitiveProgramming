constexpr int MAX = ;
int sz[MAX], cor[MAX], cnt[MAX];
vector<int> g[MAX];

void build(int k, int d = 0) {
    sz[k] = 1;
    for (auto& i : g[k]) {
        build(i, d + 1); sz[k] += sz[i];
        if (sz[i] > sz[g[k][0]]) swap(i, g[k][0]);
    }
}

void compute(int k, int x, bool dont = 1) {
    // x = 1 add, -1 remove
    cnt[cor[k]] += x;


    // process ?? 

    for (int i = dont; i < g[k].size(); i++)
        compute(g[k][i], x, 0);
}

void solve(int k, bool keep = 0) {
    for (int i = int(g[k].size()) - 1; i >= 0; i--) solve(g[k][i], !i);
    compute(k, 1);

    // now cnt[i] has how many times the color i appears in the subtree of k

    if (!keep) {
        compute(k, -1, 0);
        // remove the counts of the subtree of k ??
    }
}
