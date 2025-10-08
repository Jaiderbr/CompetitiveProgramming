

// https://github.com/JaiderBR/CompetitiveProgramming/blob/main/Data%20Structure/Mint.cpp
static constexpr int mod = 1e9 + 7;
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

const int mxN = 105;
mint dp[21][mxN][mxN][mxN];
mint factorial[mxN];
mint inverse_factorial[mxN];

void init() {
    factorial[0] = 1;
    forne(i, 1, mxN) factorial[i] = factorial[i - 1] * i;
    forn(i, mxN) inverse_factorial[i] = factorial[i].inv();
}
// https://cp-algorithms.com/combinatorics/binomial-coefficients.html
mint binomial_coefficient(ll n, ll k) {
    return (factorial[n] * inverse_factorial[k]) * inverse_factorial[n - k];
}

mint back(ll n, ll r, ll g, ll b) {
    if (r < 0 || g < 0 || b < 0) return 0;
    if (n == 0) return 1;
    if (dp[n][r][g][b] != -1) return dp[n][r][g][b];
    mint form_1 = 0, form_2 = 0, form_3 = 0;
    form_1 = back(n - 1, r - n, g, b) + back(n - 1, r, g - n, b) + back(n - 1, r, g, b - n);
    if (n % 2 == 0) {
        /*
        R G B (R G) - (R B) - (G B)
        */
        form_2 = binomial_coefficient(n, n / 2) * ((back(n - 1, r - n / 2, g - n / 2, b) + back(n - 1, r - n / 2, g, b - n / 2) + back(n - 1, r, g - n / 2, b - n / 2)));
    }

    if (n % 3 == 0) {
        /*
        n=3 bc_1=3 bc_2=2 = 6
        R G B - R B G - G B R -B G R - G R B - B R G
        */
        mint bc_1 = binomial_coefficient(n, n / 3);
        mint bc_2 = binomial_coefficient(2 * n / 3, n / 3);
        form_3 = (bc_1 * bc_2) * back(n - 1, r - n / 3, g - n / 3, b - n / 3);
    }
    return dp[n][r][g][b] = form_1 + form_2 + form_3;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init();
    ll n, r, g, b; cin >> n >> r >> g >> b;
    forn(i, n + 1) forn(j, r + 1) forn(k, g + 1) forn(l, b + 1) dp[i][j][k][l] = -1;
    // memset(dp, -1, sizeof dp);
    cout << back(n, r, g, b).val() << endl;

    cout << flush;
    return 0;
}