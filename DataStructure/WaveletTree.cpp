struct WaveletTree {
    int lo, hi;
    WaveletTree* left = nullptr, * right = nullptr;
    vector<int> freq, pref;

    // Build from [from, to) with values in [x, y] x = min value, y = max value
    WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) : lo(x), hi(y) {
        if (from >= to) return;
        int mid = (lo + hi) >> 1;
        auto f = [mid](int v) { return v <= mid; };

        int sz = to - from;
        freq.reserve(sz + 1);
        freq.push_back(0);
        pref.reserve(sz + 1);
        pref.push_back(0);

        for (auto it = from; it != to; ++it) {
            freq.push_back(freq.back() + f(*it));
            pref.push_back(pref.back() + *it);
        }

        if (lo == hi) return;

        auto pivot = stable_partition(from, to, f);
        left = new WaveletTree(from, pivot, lo, mid);
        right = new WaveletTree(pivot, to, mid + 1, hi);
    }

    // k-th smallest in [l,r]
    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;

        int lb = freq[l - 1], rb = freq[r];
        int inLeft = rb - lb;
        if (k <= inLeft) return left->kth(lb + 1, rb, k);
        else return right->kth(l - lb, r - rb, k - inLeft);
    }

    // number of elements == k in [l,r]
    int eq(int l, int r, int k) {
        if (l > r || k < lo || k > hi) return 0;
        if (lo == hi) return r - l + 1;

        int lb = freq[l - 1], rb = freq[r];
        int mid = (lo + hi) >> 1;
        if (k <= mid) return left->eq(lb + 1, rb, k);
        else return right->eq(l - lb, r - rb, k);
    }

    // number of elements <= k in [l,r]
    int le(int l, int r, int k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;

        int lb = freq[l - 1], rb = freq[r];
        return left->le(lb + 1, rb, k) + right->le(l - lb, r - rb, k);
    }

    // number of elements < k in [l,r]
    int lt(int l, int r, int k) {
        if (l > r || k <= lo) return 0;
        if (hi < k) return r - l + 1;

        int lb = freq[l - 1], rb = freq[r];
        return left->lt(lb + 1, rb, k) + right->lt(l - lb, r - rb, k);
    }

    // number of elements >= k in [l,r]
    int ge(int l, int r, int k) {
        if (l > r || k > hi) return 0;
        if (k <= lo) return r - l + 1;

        int lb = freq[l - 1], rb = freq[r];
        return left->ge(lb + 1, rb, k) + right->ge(l - lb, r - rb, k);
    }

    // number of elements > k in [l,r]
    int gt(int l, int r, int k) {
        if (l > r || k >= hi) return 0;
        if (k < lo) return r - l + 1;

        int lb = freq[l - 1], rb = freq[r];
        int mid = (lo + hi) >> 1;
        if (k < mid) return left->gt(lb + 1, rb, k) + right->count(l - lb, r - rb);
        else return right->gt(l - lb, r - rb, k);
    }

    // helper to count total in node
    int count(int l, int r) {
        if (l > r) return 0;
        return r - l + 1;
    }

    // number of elements in [l,r] between [a,b]
    int between(int l, int r, int a, int b) {
        return le(l, r, b) - lt(l, r, a);
    }

    // sum of elements <= k in [l,r]
    int sum_le(int l, int r, int k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return pref[r] - pref[l - 1];

        int lb = freq[l - 1], rb = freq[r];
        return left->sum_le(lb + 1, rb, k) + right->sum_le(l - lb, r - rb, k);
    }
};