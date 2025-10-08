//https://vjudge.net/problem/SPOJ-FIBHARD

#define int int64_t

constexpr int MOD = 998244353;
constexpr int NMOD = 998244353 + 998244353 + 2;

struct matrix {
    int n, m;
    vector<vector<int>> v;

    matrix(int n, int m, bool ones = false) : n(n), m(m), v(n, vector<int>(m)) {
        if (ones) forn(i, n) v[i][i] = 1;
    }

    matrix operator * (const matrix& o) {
        matrix ans(n, o.m);
        forn(i, n)
            forn(k, m) if (v[i][k])
            forn(j, o.m)
            ans[i][j] = (1ll * v[i][k] * o.v[k][j] + ans[i][j]) % MOD;
        return ans;
    }

    vector<int>& operator [] (int i) {
        return v[i];
    }
};

matrix binpow(matrix b, ll e) {
    matrix ans(b.n, b.m, true);
    while (e) {
        if (e & 1) ans = ans * b;
        b = b * b;
        e >>= 1;
    }
    return ans;
}


void solve() {


    string s; cin >> s;

    int n = 0;
    forn(i, sz(s)) n = ((n * 10) % NMOD + (s[i] - '0')) % NMOD;

    matrix fib(2, 2);
    fib[0][0] = fib[0][1] = fib[1][0] = 1; fib[1][1] = 0;

    matrix res = binpow(fib, n);

    cout << res[0][1] << endl;







}
main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


    int testcase; cin >> testcase; while (testcase--) solve();








    cout << flush;
    return 0;
}