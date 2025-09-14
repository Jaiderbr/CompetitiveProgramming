// tomado de : https://tinyurl.com/2rznfrs3

#define int int64_t
#define MAX 200005
namespace seg {
	int seg[4 * MAX], lazy[4 * MAX];
	int n, * v;

	int build(int p = 1, int l = 0, int r = n - 1) {
		lazy[p] = 0; // lazy[p] = 1;
		if (l == r) return seg[p] = v[l];
		int m = (l + r) / 2;
		return seg[p] = build(2 * p, l, m) + build(2 * p + 1, m + 1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p] += lazy[p] * (r - l + 1);
		if (l != r) lazy[2 * p] += lazy[p], lazy[2 * p + 1] += lazy[p];
		lazy[p] = 0;
		// seg[p] *= pow(lazy[p], r - l + 1); || seg[p] = lazy[p] * seg[p];				
		// if (l != r) lazy[2*p] *= lazy[p], lazy[2*p+1] *= lazy[p];
		// lazy[p] = 1;
	}
	int query(int a, int b, int p = 1, int l = 0, int r = n - 1) {
		prop(p, l, r);
		if (a <= l and r <= b) return seg[p];
		if (b < l or r < a) return 0;
		int m = (l + r) / 2;

		return query(a, b, 2 * p, l, m) + query(a, b, 2 * p + 1, m + 1, r);
	}
	int update(int a, int b, int x, int p = 1, int l = 0, int r = n - 1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] += x; // lazy[p] *= x;
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l + r) / 2;
		return seg[p] = update(a, b, x, 2 * p, l, m) + update(a, b, x, 2 * p + 1, m + 1, r);
	}
};

namespace hld {
	vector<pair<int, int> > g[MAX];
	int pos[MAX], sz[MAX];
	int sobe[MAX], pai[MAX];
	int h[MAX], v[MAX], t;

	void build_hld(int k, int p = -1, int f = 1) {
		v[pos[k] = t++] = sobe[k]; sz[k] = 1;
		for (auto& i : g[k]) if (i.first != p) {
			auto [u, w] = i;
			sobe[u] = w; pai[u] = k;
			h[u] = (i == g[k][0] ? h[k] : u);
			build_hld(u, k, f); sz[k] += sz[u];

			if (sz[u] > sz[g[k][0].first] or g[k][0].first == p)
				swap(i, g[k][0]);
		}
		if (p * f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
		build_hld(root);
		seg::build(t, v);
	}
	int query_path(int a, int b) {
		if (a == b) return 0;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b] + 1, pos[a]);
		return seg::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b, int x) {
		if (a == b) return;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg::update(pos[b] + 1, pos[a], x);
		seg::update(pos[h[a]], pos[a], x); update_path(pai[h[a]], b, x);
	}
	int query_subtree(int a) {
		if (sz[a] == 1) return 0;
		return seg::query(pos[a] + 1, pos[a] + sz[a] - 1);
	}
	void update_subtree(int a, int x) {
		if (sz[a] == 1) return;
		seg::update(pos[a] + 1, pos[a] + sz[a] - 1, x);
	}
	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}
