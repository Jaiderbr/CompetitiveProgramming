/*
The edit distance between two strings is the minimum number of operations required to transform one string into the other.
*/

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
