/*
Math/Sieve.cpp
*/

#define int int64_t
vector<int> segmented_criba(int l, int r) {
    l = max<int>(l, 2ll);
    vector<bool> vis(r - l + 1);
    for (int& pp : prime) {
        if ((int)pp * pp > r) break;
        int mn = (l + pp - 1) / pp;
        if (mn == 1ll) mn++;
        mn *= pp;
        for (int i = mn; i <= r; i += pp) {
            vis[i - l] = true;
        }
    }
    vector<int> ans;
    forn(i, sz(vis)) if (!vis[i]) ans.pb(l + i);
    return ans;
}