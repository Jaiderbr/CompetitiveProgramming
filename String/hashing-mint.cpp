static constexpr int mod = 998244353;
struct mint {
    static constexpr int  m = 998244353;
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
    friend mint operator+ (mint a, mint b) { return a += b; }
    friend mint operator- (mint a, mint b) { return a -= b; }
    friend mint operator/ (mint a, mint b) { return a /= b; }
    friend mint operator* (mint a, mint b) { return a *= b; }
    friend bool operator==(mint a, mint b) { return a.x == b.x; }
    friend bool operator!=(mint a, mint b) { return a.x != b.x; }
    friend bool operator< (mint a, mint b) { return a.x < b.x; }
};

/*
Usage:
        Good values c = 137, mod = 10^9 + 7, mod = 1e18 + 9.
        If necessary to check too many pairs of hashes, use two
        different hashes.
        If hashing something other than english characters:
            - Don't have elements with value 0.
            - Use c > max element value.


*/
struct Hash {
    mint c, mod;
    vector<mint> h, p;
    Hash(const string& s, ll c, ll mod) : c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1) {
        p[0] = 1;
        h[0] = 0;
        forn(i, sz(s)) {
            h[i + 1] = (c * h[i] + s[i]);
            p[i + 1] = (c * p[i]);
        }
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    mint get(int a, int b) {
        return (h[b + 1] - ((h[a] * p[b - a + 1])));
    }
};

bool same(Hash& Ha, Hash& Hb, int l, int r) {
    int qa = Ha.get(l, r).x;
    int qb = Hb.get(sz(Hb.h) - 2 - r, sz(Hb.h) - 2 - l).x;
    return qa == qb;
}