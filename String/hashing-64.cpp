#define int int64_t
const int MOD = (1ll << 61) - 1;

int mulmod(int a, int b) {
    const static int L = (1ll << 30) - 1, _31 = (1ll << 31) - 1;
    int l1 = a & L, h1 = a >> 30, l2 = b & L, h2 = b >> 30;
    int m = l1 * h2 + l2 * h1, h = h1 * h2;
    int ans = l1 * l2 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & _31) << 30) + 1;
    ans = (ans & MOD) + (ans >> 61), ans = (ans & MOD) + (ans >> 61);
    return ans - 1;
}

int rnd(int l, int r) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(l, r)(rng);
}

struct Hash {
    static int P;
    vector<int> h, p;
    Hash(string& s) : h(sz(s)), p(sz(s)) {
        p[0] = 1, h[0] = s[0];
        forne(i, 1, sz(s)) p[i] = mulmod(p[i - 1], P), h[i] = (mulmod(h[i - 1], P) + s[i]) % MOD;
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    int get(int l, int r) {
        int hash = h[r] - (l ? mulmod(h[l - 1], p[r - l + 1]) : 0);
        return hash < 0 ? hash + MOD : hash;
    }
};

int Hash::P = rnd(256, MOD - 1);