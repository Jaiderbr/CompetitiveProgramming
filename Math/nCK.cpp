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
    friend bool operator==(mint a, mint b) { return a.x == b.x; }
    friend bool operator!=(mint a, mint b) { return a.x != b.x; }
};


const int mxN = 1e6 + 7; // max value of  N,K
mint fact[mxN];
mint inv_fact[mxN];
void init() {
    fact[0] = 1;
    forne(i, 1, mxN) fact[i] = fact[i - 1] * i;
    forn(i, mxN) inv_fact[i] = fact[i].inv();
}
// https://cp-algorithms.com/combinatorics/binomial-coefficients.html

mint nCk(ll n, ll k) {
    return (fact[n] * inv_fact[k]) * inv_fact[n - k];
}