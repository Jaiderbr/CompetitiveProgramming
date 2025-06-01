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

const double PI = acos(-1);
const double eps = 1e-7;

// se requiere llenar 50% del volumen de un cono truncado
// con radio menor r, radio mayor R y altura h
// se requiere encontrar la altura a la que se debe llenar el cono truncado

void solve() {
    double r, R, h; cin >> r >> R >> h;

    auto get = [&](double r1, double r2, double h) {
        return (PI * h / 3.0) * (r1 * r1 + r1 * r2 + r2 * r2); //volumen cono truncado
        };

    double vol = get(r, R, h);
    double l = 0, hi = h;

    forn(_, 200) {
        double mid = (l + hi) / 2.0;
        double newmid = r + (R - r) * (mid / h); // Radio en la altura mid
        double volmid = get(r, newmid, mid);
        if (volmid < vol / 2.0) l = mid;
        else hi = mid;
    }

    cout << fixed << setprecision(9) << (l + hi) / 2.0 << endl;


}
main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


    int testcase; cin >> testcase; while (testcase--) solve();








    cout << flush;
    return 0;
}
