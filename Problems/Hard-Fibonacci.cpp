//https://vjudge.net/problem/SPOJ-FIBHARD

#include <bits/stdc++.h>
using namespace std;
#define endl     '\n' 
#define f        first
#define s        second
#define ins      insert
#define pb       push_back
#define eb       emplace_back
#define sz(x)    int((x).size())
#define all(x)   begin(x), end(x)
typedef long long ll;
typedef unsigned long long ull;
#define forn(i, n) for (int i = 0; i < n; ++i)
#define each(i, x) for (auto &&i : x)
#define forne(i,x,n) for (int i = x; i < n; ++i)
#define show(x) for (auto &&i : x) {cerr << i <<' ';} cerr<< endl;


void dbg_out() { cerr << ']' << endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << H;if (sizeof...(T)) cerr << ',' << ' '; dbg_out(T...); }
#ifdef LOCAL 
#define dbg(...) cerr << '|' << __LINE__ << '|'<< '{' << #__VA_ARGS__ << '}'<<':'<<' '<<'[', dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
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