struct mint {
    static constexpr int  m = 1e9 + 7;
    //static inline int  m = 998244353; //to change mod
    int x;
    mint() : x(0) {}
    mint(long long x_) :x(x_% m) { if (x < 0) x += m; }
    int val() { return x; }
    mint& operator+=(mint b) { if ((x += b.x) >= m) x -= m; return *this; }
    mint& operator-=(mint b) { if ((x -= b.x) < 0) x += m; return *this; }
    mint& operator*=(mint b) { x = (long long)(x)*b.x % m; return *this; }
    mint pow(long long e) const {
        mint r = 1, b = *this;
        while (e) {
            if (e & 1) r *= b;
            b *= b;
            e >>= 1;
        }
        return r;
    }
    mint inv() { return pow(m - 2); }
    mint& operator/=(mint b) { return *this *= b.pow(m - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend bool operator<(mint a, mint b) { return a.x < b.x; }
    friend bool operator==(mint a, mint b) { return a.x == b.x; }
    friend bool operator!=(mint a, mint b) { return a.x != b.x; }
};
// Find the number of distinct subsequences of a given string.
// distinct subsequences ending at each of the 26 letters of the alphabet.
template<typename T>int distinctsub(const T& sub) {
    int n = sz(sub);
    vector<mint> dp(n + 1, 0);
    vector<int>last(26, -1);
    // vector<mint>end_count(26, 0);
    dp[0] = 1;
    forn(i, n) {
        dp[i + 1] += 2 * dp[i];
        // end_count[sub[i] - 'a'] += dp[i];
        if (~last[sub[i] - 'a']) {
            dp[i + 1] -= dp[last[sub[i] - 'a']];
            // end_count[sub[i] - 'a'] -= dp[last[sub[i] - 'a']];
        }
        last[sub[i] - 'a'] = i;
    }
    return dp[n].x - 1;
}

// find the number of distinct subsequences of a given string.
// number of distinct subsequences of each length from 1 to n
// number of distinct subsequences of size i -> dp[n][i]
template<typename T>int distinctsub(const T& sub) {
    int n = sz(sub);
    vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, 0));
    dp[0][0] = 1;
    vector<int> last(26, -1);
    // vector<mint> end_count(26, 0);
    forn(i, n) {
        forn(j, i + 1) {
            dp[i + 1][j + 1] = dp[i][j];
            dp[i + 1][j] += dp[i][j];
            // end_count[sub[i] - 'a'] += dp[i][j].x;
        }
        if (~last[sub[i] - 'a']) {
            forn(j, i + 1) {
                dp[i + 1][j + 1] -= dp[last[sub[i] - 'a']][j];
                // end_count[sub[i] - 'a'] -= dp[last[sub[i] - 'a']][j].x;
            }
        }
        last[sub[i] - 'a'] = i;
    }

    mint ans = 0;
    forne(i, 1, n + 1) ans += dp[n][i];
    return ans.x;
}