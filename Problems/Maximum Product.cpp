// Find the number from the range [a, b] which has the maximum product of the digits.
pair<int, string> dp[20][2][2][2];
bool vis[20][2][2][2];


pair<int, string> back(string l, string r, int pos, int ta, int tb, int st) {
    if (pos == sz(l)) return { 1, "" };
    if (vis[pos][ta][tb][st]) return dp[pos][ta][tb][st];
    int sta = ta ? l[pos] - '0' : 0, end = tb ? r[pos] - '0' : 9, ans = -1;
    string s = "";
    forne(i, sta, end + 1) {
        int val = i;
        if (st == 0 && i == 0) val = 1;
        pair<int, string> alt = back(l, r, pos + 1, ta & (i == sta), tb & (i == end), st | i > 0);
        if (alt.f * val > ans) {
            ans = alt.f * val;
            if (i == 0 && st == 0) s = alt.s;
            else s = alt.s, s.pb('0' + i);
        }
    }

    vis[pos][ta][tb][st] = 1;
    return dp[pos][ta][tb][st] = { ans, s };
}

pair<int, string> solve(int a, int b) {
    string L = to_string(a), R = to_string(b);
    if (sz(L) < sz(R)) {
        reverse(all(L));
        L += string(sz(R) - sz(L), '0');
        reverse(all(L));
    }
    memset(vis, 0, sizeof(vis));
    pair<int, string> ans = back(L, R, 0, 1, 1, 0);
    reverse(all(ans.s));
    return { ans.f, ans.s };
}
