struct node { int start, end, maxLen; };

struct STregularBracket {
    vector<node> seg;
    int size;

    STregularBracket(string S) {
        S = "0" + S;
        size = S.size();
        seg.resize(4 * size);
        build(1, 1, size - 1, S);
    }

    void build(int idx, int s, int e, string& S) {
        if (s == e) {
            if (S[s] == '(') seg[idx] = { 1, 0, 0 };
            else             seg[idx] = { 0, 1, 0 };
            return;
        }
        int m = (s + e) / 2;
        build(idx << 1, s, m, S);
        build(idx << 1 | 1, m + 1, e, S);
        pull(idx);
    }

    void pull(int idx) {
        node& L = seg[idx << 1], & R = seg[idx << 1 | 1], & P = seg[idx];
        P.start = R.start;
        P.end = L.end;
        P.maxLen = L.maxLen + R.maxLen;
        int pares = min(L.start, R.end);
        P.maxLen += pares * 2;
        int dif = L.start - R.end;
        if (dif > 0) P.start += dif;
        else         P.end -= dif;
    }

    node query(int idx, int s, int e, int l, int r) {
        if (l > e || s > r) return { 0, 0, 0 };
        if (s >= l && e <= r) return seg[idx];
        int m = (s + e) / 2;
        node p1 = query(idx << 1, s, m, l, r);
        node p2 = query(idx << 1 | 1, m + 1, e, l, r);
        node ans;
        ans.start = p2.start;
        ans.end = p1.end;
        ans.maxLen = p1.maxLen + p2.maxLen;
        int pares = min(p1.start, p2.end);
        ans.maxLen += pares * 2;
        int dif = p1.start - p2.end;
        if (dif > 0) ans.start += dif;
        else         ans.end -= dif;
        return ans;
    }

    void update(int idx, int s, int e, int pos, char val) {
        if (s == e) {
            if (val == '(') seg[idx] = { 1, 0, 0 };
            else             seg[idx] = { 0, 1, 0 };
            return;
        }
        int m = (s + e) / 2;
        if (pos <= m) update(idx << 1, s, m, pos, val);
        else          update(idx << 1 | 1, m + 1, e, pos, val);
        pull(idx);
    }

    // [1, n]
    node query(int l, int r) { return query(1, 1, size - 1, l, r); }
    void update(int pos, char val) { update(1, 1, size - 1, pos, val); }
};