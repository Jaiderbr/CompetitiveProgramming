template<typename T>
struct SqrtBlocks {
    int n, blk_sz, blk_n;
    vector<T> st;
    vector<vector<T>> blocks;

    SqrtBlocks(vector<T>& a) {
        n = sz(a), st = a;
        blk_sz = sqrt(n) + 1, blk_n = (n + blk_sz - 1) / blk_sz;
        blocks.resize(blk_n);
        forn(i, n) blocks[i / blk_sz].pb(st[i]);
        forn(i, blk_n) sort(all(blocks[i]));
    }

    void update(int pos, int val) {
        int blk = pos / blk_sz;
        auto& b = blocks[blk];
        auto it = lower_bound(all(b), st[pos]);
        b.erase(it);
        b.insert(lower_bound(all(b), val), val);
        st[pos] = val;
    }
    // >
    T query_greater(int l, int r, int val) {
        T res = 0;
        int bl = l / blk_sz, br = r / blk_sz;
        if (bl == br) {
            forne(i, l, r + 1) res += (st[i] > val);
            return res;
        }
        int end_l = (bl + 1) * blk_sz;
        forne(i, l, end_l) res += (st[i] > val);
        forne(b, bl + 1, br) res += end(blocks[b]) - upper_bound(all(blocks[b]), val);
        int start_r = br * blk_sz;
        forne(i, start_r, r + 1) res += (st[i] > val);
        return res;
    }

    // >= 
    T query_ge(int l, int r, int val) {
        T res = 0;
        int bl = l / blk_sz, br = r / blk_sz;
        if (bl == br) {
            forne(i, l, r + 1) res += (st[i] >= val);
            return res;
        }
        int end_l = (bl + 1) * blk_sz;
        forne(i, l, end_l) res += (st[i] >= val);
        forne(b, bl + 1, br) res += end(blocks[b]) - lower_bound(all(blocks[b]), val);
        int start_r = br * blk_sz;
        forne(i, start_r, r + 1) res += (st[i] >= val);
        return res;
    }

    // <
    T query_less(int l, int r, int val) {
        T res = 0;
        int bl = l / blk_sz, br = r / blk_sz;
        if (bl == br) {
            forne(i, l, r + 1) res += (st[i] < val);
            return res;
        }
        int end_l = (bl + 1) * blk_sz;
        forne(i, l, end_l) res += (st[i] < val);
        forne(b, bl + 1, br) res += lower_bound(all(blocks[b]), val) - begin(blocks[b]);
        int start_r = br * blk_sz;
        forne(i, start_r, r + 1) res += (st[i] < val);
        return res;
    }

    // <=
    T query_le(int l, int r, int val) {
        T res = 0;
        int bl = l / blk_sz, br = r / blk_sz;
        if (bl == br) {
            forne(i, l, r + 1) res += (st[i] <= val);
            return res;
        }
        int end_l = (bl + 1) * blk_sz;
        forne(i, l, end_l) res += (st[i] <= val);
        forne(b, bl + 1, br) res += upper_bound(all(blocks[b]), val) - begin(blocks[b]);
        int start_r = br * blk_sz;
        forne(i, start_r, r + 1) res += (st[i] <= val);
        return res;
    }

    // ==
    T query_equal(int l, int r, int val) {
        T res = 0;
        int bl = l / blk_sz, br = r / blk_sz;
        if (bl == br) {
            forne(i, l, r + 1) res += (st[i] == val);
            return res;
        }
        int end_l = (bl + 1) * blk_sz;
        forne(i, l, end_l) res += (st[i] == val);
        forne(b, bl + 1, br) res += upper_bound(all(blocks[b]), val) - lower_bound(all(blocks[b]), val);
        int start_r = br * blk_sz;
        forne(i, start_r, r + 1) res += (st[i] == val);
        return res;
    }

    // between [a,b]
    T query_between(int l, int r, int a, int b) {
        T res = 0;
        int bl = l / blk_sz, br = r / blk_sz;
        if (bl == br) {
            forne(i, l, r + 1) res += (st[i] >= a && st[i] <= b);
            return res;
        }
        int end_l = (bl + 1) * blk_sz;
        forne(i, l, end_l) res += (st[i] >= a && st[i] <= b);
        forne(bk, bl + 1, br) res += upper_bound(all(blocks[bk]), b) - lower_bound(all(blocks[bk]), a);
        int start_r = br * blk_sz;
        forne(i, start_r, r + 1) res += (st[i] >= a && st[i] <= b);
        return res;
    }
};