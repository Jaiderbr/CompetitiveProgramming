constexpr int MOD = 1e9 + 7;

int64_t binpow(int64_t a, int64_t b, int64_t m) {
    a %= m;
    int64_t res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
inline int inv_mod(int a) { return binpow(a, MOD - 2, MOD); }
inline int add(int a, int b) { return ((a % MOD) + (b % MOD)) % MOD; }
inline int res(int a, int b) { return ((a % MOD) - (b % MOD) + MOD) % MOD; }
inline int mul(int a, int b) { return ((a % MOD) * (b % MOD)) % MOD; }
inline int divm(int a, int b) { return  mul(a, inv_mod(b)); }