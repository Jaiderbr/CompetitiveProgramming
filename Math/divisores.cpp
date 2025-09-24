vector<int>div(int n) {
    vector<int> ans;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ans.pb(i);
            if (i != n / i) ans.pb(n / i);            
        }
    }
    return ans;
}
