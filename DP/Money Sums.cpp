//  find all money sums you can create using these coins.
    int n; cin >> n;
    vector<int>nums(n), sums;
    forn(i, n) cin >> nums[i];
    vector<vector<bool>>dp(mxN + 1, vector<bool>(n * mxS + 1));
    dp[0][0] = 1;
    forne(i, 1, n + 1) {
        forn(j, mxS * n + 1) {
            dp[i][j] = dp[i - 1][j];
            if (j - nums[i - 1] >= 0 && dp[i - 1][j - nums[i - 1]]) dp[i][j] = 1;
        }
    }

    forn(i, mxS * n + 1) {
        if (i && dp[n][i]) sums.pb(i);
    }

    cout << sz(sums) << endl;
    forn(i, sz(sums)) cout << sums[i] << " \n"[i + 1 == sz(sums)];
    cout << endl;
