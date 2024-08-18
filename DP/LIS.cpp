int lis(vector<int>& a) {
    vector<int>dp;
    forn(i, sz(a)) {
        auto it = lower_bound(all(dp), a[i]);
        if (it != dp.end()) *it = a[i];
        else dp.pb(a[i]);
    }
    return sz(dp);

}