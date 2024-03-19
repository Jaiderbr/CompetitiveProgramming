
ll Knapsack(ll n, ll cty,  vector<ll>& W,vector<ll>& V) {
    vector<vector<ll>> dp(n + 1, vector<ll>(cty + 1, 0));
    forn(i,n+1){
        forn(j,cty+1){
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (W[i - 1] <= j) dp[i][j] = max(dp[i - 1][j], V[i - 1] + dp[i - 1][j - W[i - 1]]);
            else dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][cty];
}

const ll inf=1e18+7;

ll Knapsack(ll n, ll cty,  vector<ll>& W,vector<ll>& V) {
    ll sum=accumulate(all(V),0LL);
    vector<ll>dp(sum+1,inf);
    dp[0]=0;
    forn(i, n){
        for(int j = sum-V[i]; j >= 0; j--){
            dp[j+V[i]]= min(dp[j+V[i]], dp[j]+W[i]);
        }
    }
    ll ans=0;
    forn(i,sum+1){
        if(dp[i]<= cty) ans=max(ans,ll(i));
    }
    return ans;
}