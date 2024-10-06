/*
12345168 = 123+45=168
199100 = 1+99=100
*/

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

constexpr int mxN = 1e6 + 7, mod = 998244353;
vector<int>p(mxN);
void pre(int c, int mod) {
    p[0] = 1;
    for (int i = 0; i < mxN - 1; i++) {
        p[i + 1] = (c * p[i]) % mod;
    }
}

struct Hash {
    #warning llamar pre;
    ll c, mod;
    vector<int> h;
    Hash(const string& s, const int c, const int mod) : c(c), mod(mod), h(sz(s) + 1) {
        h[0] = 0;
        for (int i = 0; i < sz(s); i++) {
            h[i + 1] = (c * h[i] + s[i] - '0') % mod;
        }
    }
    // Returns hash of interval s[a ... b] (where 0 <= a <= b < sz(s))
    ll get(int a, int b) {
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
    }
};

bool same(Hash& Ha, Hash& Hb, int l, int r) {
    int qa = Ha.get(l, r);
    int qb = Hb.get(sz(Hb.h) - 2 - r, sz(Hb.h) - 2 - l);
    return qa == qb;
}

main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    pre(10, mod);

    string s; cin >> s;
    Hash ha(s, 10, mod);
    int n = sz(s);

    auto ok = [&](int i, int j) {
        i--, j--;
        if (i - 1 < 0) return;
        int a = ha.get(0, i - 1), b = ha.get(i, j - 1), c = ha.get(j, n - 1);
        if (((a + b) % mod) == c && ((s[i] != '0' ? 1 : i == j - 1)) && ((s[j] != '0' ? 1 : j == n - 1))) {
            cout << string(begin(s), begin(s) + i) << "+" << string(begin(s) + i, begin(s) + j) << "=" << string(begin(s) + j, end(s)) << endl;
            exit(0);
        }
        };

    forne(i, n / 3, ((n / 2) + 1)) {
        ok(i, n - i + 1);
        ok(i + 1, n - i + 1);
        ok(n - i * 2 + 2, n - i + 1);
        ok(n - i * 2 + 1, n - i + 1);
    }







    cout << flush;
    return 0;
}