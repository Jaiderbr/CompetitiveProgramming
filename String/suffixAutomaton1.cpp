constexpr int MAX = 1e5 + 7;

namespace sam {
    struct node {
        int len, link, cnt, fpos;
        bool acc;
        map<char, int> next;
    };
    int cur, sz;
    vector<node> sa(MAX * 2);
 
    void add(char c) {
        int at = cur;
        sa[cur].fpos = sa[sz].len = sa[cur].len + 1;
        sa[cur].fpos -= 1, cur = sz++;
        while (at != -1 && !sa[at].next.count(c)) sa[at].next[c] = cur, at = sa[at].link;
        if (at == -1) { sa[cur].link = 0; return; }
        int q = sa[at].next[c];
        if (sa[q].len == sa[at].len + 1) { sa[cur].link = q; return; }
        int qq = sz++;
        sa[qq].len = sa[at].len + 1, sa[qq].next = sa[q].next, sa[qq].link = sa[q].link;
        sa[qq].fpos = sa[q].fpos;
        while (at != -1 && sa[at].next[c] == q) sa[at].next[c] = qq, at = sa[at].link;
        sa[q].link = sa[cur].link = qq;
    }
 
    void build(string& s) {
        #warning "clear????";
        sa.assign(MAX * 2, node());
        cur = 0, sz = 0, sa[0].len = 0, sa[0].link = -1, sz++;
        for (auto& i : s) add(i);
        int at = cur;
        while (at) sa[at].acc = 1, at = sa[at].link;
    }
    int64_t distinct_substrings() {
        ll ans = 0;
        for (int i = 1; i < sz; i++) ans += sa[i].len - sa[sa[i].link].len;
        return ans;
    }
    int longest_common_substring(string& S, string& T) {
        build(S);
        int at = 0, l = 0, ans = 0, pos = -1;
        for (int i = 0; i < sz(T); i++) {
            while (at && !sa[at].next.count(T[i])) at = sa[at].link, l = sa[at].len;
            if (sa[at].next.count(T[i])) at = sa[at].next[T[i]], l++;
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
            while (u && !sa[u].next.count(t[i])) u = sa[u].link, l = sa[u].len;
            if (sa[u].next.count(t[i])) u = sa[u].next[t[i]], l++;
            match[u] = max(match[u], l);
        }
        for (int i = MAX - 1; i > 0; --i) match[i] = max(match[i], match[sa[i].link]);
        for (int i = 0; i < MAX; ++i) LCS[i] = min(LCS[i], match[i]);
    }
 
    int lcs_n(vector<string>& t) {
        const int INF = 1e7;
        LCS.assign(MAX, INF);
        forn(i, sz(t)) lcsMatch(t[i]);
        return *max_element(all(LCS));
    }
 
    int isSubstr(string& s) {
        int at = 0;
        for (auto& i : s) {
            if (!sa[at].next.count(i)) return 0;
            at = sa[at].next[i];
        }
        return at;
    }
 
    int count_occ(int u) {
        if (sa[u].cnt != 0) return sa[u].cnt;
        sa[u].cnt = sa[u].acc;
        for (auto& v : sa[u].next) sa[u].cnt += count_occ(v.s);
        return sa[u].cnt;
    }
 
    int pos_occ(string& s) {
        int x = sam::isSubstr(s);
        return x ? (abs(sam::sa[x].fpos - sz(s)) + 1) : -1;
    }
 
    ll dp[2 * MAX];
    ll paths(int i) {
        auto& x = dp[i];
        if (x) return x;
        x = 1;
        for (char j = 'a';j <= 'z';j++) {
            if (sa[i].next.count(j)) x += paths(sa[i].next[j]);
        }
        return x;
    }
 
    void kth_substring(int k, int at = 0) { // k=1 : menor substring lexicog.
        for (int i = 0; i < 26; i++) if (k && sa[at].next.count(i + 'a')) {
            if (paths(sa[at].next[i + 'a']) >= k) {
                cout << char(i + 'a');
                kth_substring(k - 1, sa[at].next[i + 'a']);
                return;
            }
            k -= paths(sa[at].next[i + 'a']);
        }
    }
};
