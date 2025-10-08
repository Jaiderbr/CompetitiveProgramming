//https://codeforces.com/gym/104758/problem/B

/*
The Trinacci sequence is defined as follows:
t(0)=1
t(1)=2
t(2)=3

t(n)=3t(n-1)+2t(n-2)+t(n-3)+3 for n>=3
*/

const int MOD = 1e9 + 7;
struct matrix {
    int n, m;
    vector<vector<int>>v;

    matrix(int n, int m, bool ones = false) : n(n), m(m), v(n, vector<int>(m)) {
        if (ones) forn(i, n) v[i][i] = 1;
    }

    matrix operator * (const matrix& o) {
        matrix ans(n, o.m);
        forn(i, n)
            forn(k, m) if (v[i][k])
            forn(j, o.m)
            ans[i][j] = (v[i][k] * o.v[k][j] + ans[i][j]) % MOD;
        return ans;
    }

    vector<int>& operator [] (int i) {
        return v[i];
    }
};

matrix binpow(matrix b, int e) {
    matrix ans(b.n, b.m, true);
    while (e) {
        if (e & 1) ans = ans * b;
        b = b * b;
        e >>= 1;
    }
    return ans;
}


void solve() {

    matrix a(4, 4), b(4, 4);
    a[0][0] = 4;
    a[0][1] = (-1 + MOD) % MOD;
    a[0][2] = (-1 + MOD) % MOD;
    a[0][3] = (-1 + MOD) % MOD;
    forn(i, 3) a[i + 1][i] = 1;

    b[0][0] = 17;
    b[1][0] = 3;
    b[2][0] = 2;
    b[3][0] = 1;

    int n; cin >> n;
    if (n < 4) {
        cout << b[3 - n][0] << endl;
    }
    else {
        matrix ans = binpow(a, n - 3) * b;
        cout << ans[0][0] << endl;
    }






}
main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testcase = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    testcase = 4;
#endif

    //cin >> testcase;
    while (testcase--)solve();








    cout << flush;
    return 0;
}

