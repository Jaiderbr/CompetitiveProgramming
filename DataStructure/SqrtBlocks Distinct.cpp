template<typename T>
struct SqrtBlocks_Distinct {
	int n, blk_sz, blk_n;
	vector<T> st;
	vector<int> prv, blk_max;
	map<T, set<int>> positions;

	SqrtBlocks_Distinct(vector<T>& a) {
		n = sz(a), st = a;
		blk_sz = sqrt(n) + 1;
		blk_n = (n + blk_sz - 1) / blk_sz;

		prv.assign(n, -1);
		blk_max.assign(blk_n, -1);

		forn(i, n) positions[st[i]].insert(i);
		forn(i, n) {
			auto& s = positions[st[i]];
			auto it = s.find(i);
			if (it != s.begin()) prv[i] = *prev(it);
		}
		forn(b, blk_n) rebuild_max(b);
	}

	void rebuild_max(int b) {
		blk_max[b] = -1;
		int l = b * blk_sz, r = min(n - 1, l + blk_sz - 1);
		forne(i, l, r + 1) blk_max[b] = max(blk_max[b], prv[i]);
	}
	void set_prv(int p, int val) {
		prv[p] = val;
		rebuild_max(p / blk_sz);
	}
	int prev_in(set<int>& s, int k) {
		auto it = s.find(k);
		return (it != s.begin()) ? *prev(it) : -1;
	}
	int next_in(set<int>& s, int k) {
		auto it = next(s.find(k));
		return (it != s.end()) ? *it : -1;
	}

	void update(int pos, T val) {
		if (st[pos] == val) return;
		auto& sold = positions[st[pos]];
		int p_old = prev_in(sold, pos);
		int nx_old = next_in(sold, pos);
		sold.erase(pos);
		if (nx_old != -1) set_prv(nx_old, p_old);
		auto& snew = positions[val];
		snew.insert(pos);
		int p_new = prev_in(snew, pos);
		int nx_new = next_in(snew, pos);
		set_prv(pos, p_new);
		if (nx_new != -1) set_prv(nx_new, pos);
		st[pos] = val;
	}

	// todos distintos en [l,r] <=> max(prv[l..r]) < l
	bool query(int l, int r) {
		int res = -1;
		int bl = l / blk_sz, br = r / blk_sz;
		if (bl == br) {
			forne(i, l, r + 1) res = max(res, prv[i]);
			return res < l;
		}
		forne(i, l, (bl + 1) * blk_sz) res = max(res, prv[i]);
		forne(b, bl + 1, br)            res = max(res, blk_max[b]);
		forne(i, br * blk_sz, r + 1)    res = max(res, prv[i]);
		return res < l;
	}
};
