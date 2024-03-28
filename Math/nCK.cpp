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
mint nCk(ll n, ll k) {
    return (factorial[n] * inverse_factorial[k]) * inverse_factorial[n - k];
}