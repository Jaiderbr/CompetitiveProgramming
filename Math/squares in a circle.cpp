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
ll get(ll mid){
    ll ans=0;
    for(ll i=1; i*i < mid; i++){
        ans+=4*floor(sqrt( mid-i*i));
    }

    return ans;

}

const int inf= 1e9+7;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int test=1;
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        test=2;
    #endif

    while(test--){
        ll n; cin>>n;
        ll r=4*n, l=1;
        double pre= 1.0*inf;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(get(mid)>n){
                r=mid-1;
                pre=min(pre,sqrt(mid));
            }else l=mid+1;
        }
        cout<<fixed<< setprecision(30)<<pre<<endl;


    }

    cout << flush;
    return 0;
}

