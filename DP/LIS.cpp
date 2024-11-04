int lis(vector<int>& a) {
    vector<int>dp;
    forn(i, sz(a)) {
        auto it = lower_bound(all(dp), a[i]);
        if (it != dp.end()) *it = a[i];
        else dp.pb(a[i]);
    }
    return sz(dp);

}


int lis_2(int n, vector<int>& A, vector<int>& B) {

    vector<vector<int>>C(inf, vector<int>());
    reverse(all(A)); reverse(all(B));
    for (int i = n - 1; i >= 0; i--) C[B[i]].pb(i);

    STree<int> dp(n); // Stree de max, neutro = INT_MIN

    for (int j = 0; j < n; j++) {
        for (auto&& i : C[A[j]]) {
            int mx_pre = dp.query(0, i);
            if (mx_pre != INT_MIN) dp.upd(i, mx_pre + 1);
            else dp.upd(i, 1);
        }
    }
    return dp.query(0, n);
}