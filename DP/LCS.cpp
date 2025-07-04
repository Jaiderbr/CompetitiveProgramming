constexpr int mxN = 105;
vector<vector<int>> dp(mxN, vector<int>(mxN, -1));
// n=sz(s), m=sz(p)
int cntsub(const string& s, const string& p, int n, int m) {
    if ((n == 0 && m == 0) || m == 0) return 1;
    if (n == 0) return 0;
    int& ans = dp[n][m];
    if (~ans) return ans;
    if (s[n - 1] == p[m - 1]) {
        return ans = cntsub(s, p, n - 1, m - 1) + cntsub(s, p, n - 1, m);
    }
    else {
        return ans = cntsub(s, p, n - 1, m);
    }
}

bool issub(const string& str, const string& sub) {
    int idx = 0;
    for (auto&& i : str) {
        if (idx < sz(sub) && i == sub[idx]) {
            idx++;
        }
    }
    return idx == sz(sub);
}

//quadratic_memory
int lcs(const string& s, const string& t) {
    int n = sz(s);
    int m = sz(t);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    forn(i, n) {
        forn(j, m) {
            dp[i + 1][j + 1] = max({ dp[i + 1][j], dp[i][j + 1], dp[i][j] + (s[i] == t[j]) });
        }
    }
    return dp[n][m];
}

//best
int lcs(const string& s, const string& t) {
    int n = sz(s);
    int m = sz(t);
    vector<int> dp(m + 1, 0);
    forn(i, n) {
        vector<int> newdp(m + 1, 0);
        forn(j, m) {
            newdp[j + 1] = max({ newdp[j], dp[j + 1], dp[j] + (s[i] == t[j]) });
        }
        dp.swap(newdp);
    }
    return dp[m];
}

//construct lcs
string clcs(const string& s, const string& t) {
    int n = sz(s);
    int m = sz(t);
    vector<int> dp(m + 1, 0);
    vector<vector<bool>> pre(n + 1, vector<bool>(m + 1, false));
    forn(i, n) {
        vector<int> newdp(m + 1, 0);
        forn(j, m) {
            newdp[j + 1] = max({ newdp[j], dp[j + 1], dp[j] + (s[i] == t[j]) });
            pre[i + 1][j + 1] = newdp[j + 1] == newdp[j];
        }
        dp.swap(newdp);
    }
    int a = n, b = m;
    string common;
    while (a > 0 && b > 0) {
        if (s[a - 1] == t[b - 1]) {
            common += s[a - 1];
            a--; b--;
            continue;
        }
        if (pre[a][b]) b--;
        else a--;
    }
    reverse(all(common));
    return common;
}

//best: construct lcs with  Hirschberg Algorithm 
string clcsh(const string_view& s, const string_view& t) {
    int n = sz(s), int m = sz(t);
    if (n == 0 || m == 0) return "";
    if (n == 1) return t.find(s[0]) == string::npos ? "" : string(1, s[0]);
    int mid = n >> 1;
    vector<int> dp_ff(m + 1, 0);
    vector<int> dp_ss(m + 1, 0);
    vector<int> newdp(m + 1, 0);

    forn(i, mid) {
        forn(j, m) newdp[j + 1] = max({ newdp[j], dp_ff[j + 1], dp_ff[j] + (s[i] == t[j]) });
        dp_ff.swap(newdp);
    }

    newdp.assign(m + 1, 0);
    for (int i = n - 1; i >= mid; i--) {
        for (int j = m - 1; j >= 0; j--) {
            newdp[j] = max({ newdp[j + 1], dp_ss[j], dp_ss[j + 1] + (s[i] == t[j]) });
        }
        dp_ss.swap(newdp);
    }
    int splt = 0;
    forne(j, 1, m + 1) {
        if (dp_ff[j] + dp_ss[j] > dp_ff[splt] + dp_ss[splt]) {
            splt = j;
        }
    }
    dp_ff.clear();
    dp_ss.clear();
    newdp.clear();
    return (clcsh(s.substr(0, mid), t.substr(0, splt)) + clcsh(s.substr(mid), t.substr(splt)));
}

// lcs con tolerncia de 1% de eliminaciones al inicio
int lcs(const string& s, const string& t) {
    int n = sz(s);
    int poda = (n * 1) / 100 + 1;
    int ans = 0;
    vector<vector<int>> dp(poda + 1, vector<int>(poda + 1, 0));
    forn(i, poda + 1) {
        forn(j, poda + 1) {
            while (i + dp[i][j] < n && j + dp[i][j] < n && s[i + dp[i][j]] == t[j + dp[i][j]]) dp[i][j]++;
            if (i + 1 <= poda) dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (j + 1 <= poda) dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}