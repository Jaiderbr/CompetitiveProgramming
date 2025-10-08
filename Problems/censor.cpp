/*
Dado un string s y n strings t, se pide eliminar todas las ocurrencias de los strings t en s.
https://usaco.guide/adv/string-search/#problem-usaco-533
begintheescapexecutionatthebreakofdawn
2
escape
execution
----------
beginthatthebreakofdawn
*/


/*
Usage:
        Good values c = 137, modbest=998244353, mod = 10^9 + 7, mod = 1e18 + 9.
        If necessary to check too many pairs of hashes, use two
        different hashes.
        If hashing something other than english characters:
            - Don't have elements with value 0.
            - Use c > max element value.
*/

#define int int64_t
constexpr int mxN = 1e6 + 7;
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
    Hash(const string s, const int c, const int mod) : c(c), mod(mod), h(sz(s) + 1) {
        h[0] = 0;
        for (int i = 0; i < sz(s); i++) {
            h[i + 1] = (c * h[i] + s[i]) % mod;
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

const int mod = (1e9 + 7);
main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    pre(137, mod);
#ifndef LOCAL
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);
#endif

    string s, t; cin >> s;

    int mm = (1ULL << 63) - 1, n;
    int mx = -((1ULL << 63) - 1);
    cin >> n;
    set<int>mp, tam;

    forn(i, n) {
        cin >> t;
        mm = min(mm, sz(t));
        mx = max(mx, sz(t));
        tam.ins(sz(t));
        Hash ht(t, 137, mod);
        mp.ins(ht.get(0, sz(t) - 1));
    }

    int c = 137;
    vector<int> h(sz(s) + 10);
    h[0] = 0;

    auto get = [&](int a, int b) -> int {
        return (h[b + 1] - ((h[a] * p[b - a + 1]) % mod) + mod) % mod;
        };
    int i = 0;
    vector<char>ans(sz(s) + 1);
    each(j, s) {
        ans[i] = j;
        h[i + 1] = (c * h[i] + j) % mod;
        if (i >= mm - 1) {
            each(l, tam) {
                if (i >= l - 1) {
                    int cur = get(i - l + 1, i);
                    if (i >= l - 1 && mp.count(cur)) {
                        i = i - l;
                    }
                }
                else break;
            }
        }
        i++;
    }

    forn(j, i) cout << ans[j];

    cout << flush;
    return 0;
}
