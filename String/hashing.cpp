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
    ll c, mod;
    vector<ll> h, p;
    Hash(const string& s, ll c, ll mod) : c(c), mod(mod), h(sz(s) + 1), p(sz(s) + 1) {
        p[0] = 1;
        h[0] = 0;
        for (int i = 0; i < sz(s); i++) {
            h[i + 1] = (c * h[i] + s[i]) % mod;
            p[i + 1] = (c * p[i]) % mod;
        }
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    ll get(int a, int b) {
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
    }
};
