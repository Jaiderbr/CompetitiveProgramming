    vector<vector<int>>dp(mxN, vector<int>(mxN));
    vector<vector<bool>>pal(mxN, vector<bool>(mxN));
    string s; cin >> s;
    int n = sz(s), q, l, r;

    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = pal[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            pal[i][j] = (pal[i + 1][j - 1] || j - i == 1) & (s[i] == s[j]);
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + pal[i][j];
        }
    }
    cin >> q;
    while (q--) {
        cin >> l >> r;
        cout << dp[l - 1][r - 1] << endl;
    }