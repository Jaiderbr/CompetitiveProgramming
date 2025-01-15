/*
Usage:
        Good values c = 137, modbest=998244353, mod = 10^9 + 7, mod = 1e18 + 9.
        If necessary to check too many pairs of hashes, use two
        different hashes.
        If hashing something other than english characters:
            - Don't have elements with value 0.
            - Use c > max element value.
*/

//#define int int64_t

constexpr int mxN = 1e6 + 7;
vector<int>p(mxN);
void pre(const int c = 137, const int mod = 998244353) {
    p[0] = 1;
    forn(i, mxN - 1) p[i + 1] = (c * p[i]) % mod;
}

struct Hash {
    #warning llamar pre;
    int c, mod;
    vector<int> h;
    Hash(const string& s, const int c = 137, const int mod = 998244353) : c(c), mod(mod), h(sz(s) + 1) {
        h[0] = 0;
        forn(i, sz(s)) h[i + 1] = (c * h[i] + s[i]) % mod;
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    int get(int a, int b) {
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
    }
};

bool same(Hash& Ha, Hash& Hb, int l, int r) {
    int qa = Ha.get(l, r);
    int qb = Hb.get(sz(Hb.h) - 2 - r, sz(Hb.h) - 2 - l);
    return qa == qb;
}
