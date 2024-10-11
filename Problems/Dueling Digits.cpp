const int mxN = 800 + 7, mxS = 14400 + 7, mod = 1e9 + 7;
int dp[mxN][mxS << 1];
 
int back(int pos, int addA) {
    if (pos == 0) return addA == mxS;
    int& ans = dp[pos][addA];
    if (~ans) return ans;
    ans = 0;
    forn(i, 10) {
        forn(j, 10) {
            if (i == j) continue;
            if ((i == 0 || j == 0) && pos == 1) continue;
            ans = (ans + back(pos - 1, addA + i - j)) % mod;
        }
    }
    return ans;
}
 
void solve() {
 
    int n; cin >> n;
    cout << back(n, mxS) << endl;

}
