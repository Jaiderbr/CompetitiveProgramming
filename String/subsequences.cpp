struct mint {
    static constexpr int  m = 1e9 + 7;
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
    friend bool operator==(mint a, mint b) { return a.x == b.x; }
    friend bool operator!=(mint a, mint b) { return a.x != b.x; }
};

template<typename T>mint distinctsub(const vector<T>& sub) {
    int n = sz(sub);
    vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, 0));
    dp[0][0] = 1;
    // REPLACE WITH A HASH MAP OR A VECTOR IF APPLICABLE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    map<T, int> last;
    // end_count number of subsequences ending in each ith
    // map<T, int> end_count;
    forn(i, n) {
        forn(j, i + 1) {
            dp[i + 1][j + 1] = dp[i][j];
            dp[i + 1][j] += dp[i][j];
        }
        bool ok = last.find(sub[i]) != last.end();

        if (ok) {
            int prev = last[sub[i]];
            forn(j, i + 1) {
                dp[i + 1][j + 1] -= dp[prev][j];//delete repeated
            }
        }
        // forn(j, i + 1) {
        //     end_count[sub[i] - 'a'] += dp[i][j].x;
        //     if (ok) {
        //         end_count[sub[i] - 'a'] -= dp[last[sub[i] - 'a']][j].x;
        //     }
        // }

        last[sub[i]] = i;
    }

    // number of subsequences for each ith
    // vector<int> numdist(n + 1, 0);
    // forne(j, 1, n + 1) numdist[j] = dp[n][j].x;

    //number of distinct subsequences
    mint ans = 0;
    forne(i, 1, n + 1) ans += dp[n][i];

    return ans;
}