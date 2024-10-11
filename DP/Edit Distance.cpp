/*
The edit distance between two strings is the minimum number of operations required to transform one string into the other.
*/
{
    string a, b; cin >> a >> b;
    int n = sz(a), m = sz(b);
    vector<vector<int>>dp(n + 1, vector<int>(m + 1, inf));
    forne(i, 0, n + 1) dp[i][0] = i;
    forne(j, 0, m + 1) dp[0][j] = j;
    forne(i, 1, n + 1) {
        forne(j, 1, m + 1) {
            dp[i][j] = min({ dp[i][j - 1] + 1,dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]),dp[i - 1][j] + 1 });
        }
    }
    cout << dp[n][m] << endl;
}

constexpr int INF = (1e18 - 1);

int edit_distance(const string& s, const string& t) {
    int n = sz(s), m = sz(t);
    vector<int> dp(m + 1);
    iota(all(dp), 0);

    forn(i, n) {
        vector<int> ndp(m + 1, INF);
        ndp[0] = i + 1;
        forn(j, m) {
            ndp[j + 1] = min({ ndp[j] + 1, dp[j + 1] + 1, dp[j] + (s[i] != t[j]) });
        }
        dp.swap(ndp);
    }

    return dp[m];
}
vector<string> construct_edit_distance(const string& s, const string& t) {
    
    int n = sz(s), m = sz(t);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF));

    forn(i, n + 1) dp[i][0] = i;
    forn(j, m + 1) dp[0][j] = j;

    forn(i, n) {
        forn(j, m) {
            dp[i + 1][j + 1] = min({ dp[i + 1][j] + 1, dp[i][j + 1] + 1, dp[i][j] + (s[i] != t[j]) });
        }
    }

    vector<string> left = { s }, right = { t };

    while (n > 0 || m > 0) {
        if (n > 0 && dp[n][m] == dp[n - 1][m] + 1) {
            n--;
            string str = left.back();
            str.erase(str.begin() + n);
            left.push_back(str);
        }
        else if (m > 0 && dp[n][m] == dp[n][m - 1] + 1) {
            m--;
            string str = right.back();
            str.erase(str.begin() + m);
            right.push_back(str);
        }
        else if (n > 0 && m > 0 && dp[n][m] == dp[n - 1][m - 1] + (s[n - 1] != t[m - 1])) {
            n--, m--;
            if (s[n] != t[m]) {
                string str = left.back();
                str[n] = t[m];
                left.push_back(str);
            }
        }
        else {
            assert(false);
        }
    }

    assert(left.back() == right.back());
    right.pop_back();

    while (!right.empty()) {
        left.push_back(right.back());
        right.pop_back();
    }

    return left;
}
