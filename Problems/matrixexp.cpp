//https://codeforces.com/gym/104758/problem/B

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
#define int ll
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


const int MOD = 1e9 + 7;
struct matrix {
  int n, m;
  vector<vector<int>>v;

  matrix(int n, int m, bool ones = false) : n(n), m(m), v(n, vector<int>(m)) {
    if (ones) forn (i, n) v[i][i] = 1;
  }

  matrix operator * (const matrix &o) {
    matrix ans(n, o.m);
    forn (i, n)
      forn (k, m) if (v[i][k])
        forn (j, o.m)
          ans[i][j] = (v[i][k] * o.v[k][j] + ans[i][j]) % MOD;
    return ans;
  }

  vector<int> & operator [] (int i) {
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


void solve(){

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
    if(n < 4){
        cout << b[3 - n][0] << endl;
    }else{
        matrix ans = binpow(a, n - 3) * b;
        cout << ans[0][0] << endl;
    }






}
 main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testcase=1;
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        testcase=4;
    #endif

     //cin >> testcase;
     while (testcase--)solve();








    cout << flush;
    return 0;
}

