struct node {
    int start, end, maxLen;
};
struct STregularBracket {
    vector<node> seg;
    int size;

    STregularBracket(string S) {
        S = "0" + S;
        size = sz(S);
        seg.resize(4 * size);
        build(1, 1, size - 1, S);
    }

    void build(int idx, int s, int e, string& S) {
        if (s == e) {
            if (S[s] == '(') seg[idx] = { 1, 0 };
            else seg[idx] = { 0, 1 };
            return;
        }
        build(idx << 1, s, (s + e) / 2, S);
        build(idx << 1 | 1, (s + e) / 2 + 1, e, S);
        seg[idx] = { seg[idx << 1 | 1].start, seg[idx << 1].end };
        int dif = seg[idx << 1].start - seg[idx << 1 | 1].end;
        int mini = min(seg[idx << 1].start, seg[idx << 1 | 1].end);
        seg[idx].maxLen += mini * 2 + seg[idx << 1 | 1].maxLen + seg[idx << 1].maxLen;
        if (dif > 0) seg[idx].start += dif;
        else seg[idx].end -= dif;
    }

    node query(int idx, int s, int e, int l, int r) {
        if (l > e || s > r) return { 0, 0 };
        if (s >= l && e <= r) return seg[idx];
        node p1 = query(idx << 1, s, (s + e) / 2, l, r);
        node p2 = query(idx << 1 | 1, (s + e) / 2 + 1, e, l, r);
        node ans = { p2.start, p1.end };
        int dif = p1.start - p2.end;
        ans.maxLen += p1.maxLen + p2.maxLen;
        ans.maxLen += min(p1.start, p2.end) * 2;
        if (dif > 0) ans.start += dif;
        else ans.end -= dif;
        return ans;
    }
    // [1, n]
    node query(int l, int r) { return query(1, 1, size - 1, l, r); }
};