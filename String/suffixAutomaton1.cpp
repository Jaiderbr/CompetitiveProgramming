constexpr  int MAX = 2 * 1e5 + 7;

namespace sam {
    int cur, sz, len[2 * MAX], link[2 * MAX], acc[2 * MAX];
    int nxt[2 * MAX][26];

    void add(int c) {
        int at = cur;
        len[sz] = len[cur] + 1, cur = sz++;
        while (at != -1 && !nxt[at][c]) nxt[at][c] = cur, at = link[at];
        if (at == -1) { link[cur] = 0; return; }
        int q = nxt[at][c];
        if (len[q] == len[at] + 1) { link[cur] = q; return; }
        int qq = sz++;
        len[qq] = len[at] + 1, link[qq] = link[q];
        for (int i = 0; i < 26; i++) nxt[qq][i] = nxt[q][i];
        while (at != -1 && nxt[at][c] == q) nxt[at][c] = qq, at = link[at];
        link[cur] = link[q] = qq;
    }
    void clear(int n) {
        memset(nxt, 0, sizeof(nxt));
        forn(i, min(MAX, 2 * n + 7)) acc[i] = len[i] = link[i] = 0;
    }
    void build(string& s) {
        clear(sz(s));
        cur = 0, sz = 0, len[0] = 0, link[0] = -1, sz++;
        for (auto i : s) add(i - 'a');
        int at = cur;
        while (at) acc[at] = 1, at = link[at];
    }


    ll distinct_substrings() {
        ll ans = 0;
        for (int i = 1; i < sz; i++) ans += len[i] - len[link[i]];
        return ans;
    }
    int longest_common_substring(string& S, string& T) {
        build(S);
        int at = 0, l = 0, ans = 0, pos = -1;
        for (int i = 0; i < sz(T); i++) {
            while (at && !nxt[at][T[i] - 'a']) at = link[at], l = len[at];
            if (nxt[at][T[i] - 'a']) at = nxt[at][T[i] - 'a'], l++;
            else at = 0, l = 0;
            if (l > ans) ans = l, pos = i;
        }
        return ans;
        // return T.substr(pos - ans + 1, ans);
    }
    vector<int> LCS, match;
    void lcsMatch(string& t) {
        match.assign(MAX, 0);
        int u = 0, l = 0;
        for (int i = 0; i < sz(t); ++i) {
            while (u && !nxt[u][t[i] - 'a']) u = link[u], l = len[u];
            if (nxt[u][t[i] - 'a']) u = nxt[u][t[i] - 'a'], l++;
            match[u] = max(match[u], l);
        }
        for (int i = MAX - 1; i > 0; --i) match[i] = max(match[i], match[link[i]]);
        for (int i = 0; i < MAX; ++i) LCS[i] = min(LCS[i], match[i]);
    }

    int lcs_n(vector<string>& t) {
        const int INF = 1e7;
        LCS.assign(MAX, INF);
        forn(i, sz(t)) lcsMatch(t[i]);
        return *max_element(all(LCS));
    }


    ll dp[2 * MAX];
    ll paths(int i) {
        auto& x = dp[i];
        if (x) return x;
        x = 1;
        for (int j = 0; j < 26; j++) if (nxt[i][j]) x += paths(nxt[i][j]);
        return x;
    }

    void kth_substring(int k, int at = 0) { // k=1 : menor substring lexicog.
        for (int i = 0; i < 26; i++) if (k && nxt[at][i]) {
            if (paths(nxt[at][i]) >= k) {
                cout << char('a' + i);
                kth_substring(k - 1, nxt[at][i]);
                return;
            }
            k -= paths(nxt[at][i]);
        }
    }
};