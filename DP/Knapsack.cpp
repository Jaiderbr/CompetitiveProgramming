
    int n, x; cin>>n>>x;
    vector<array<int,2>>arr(n);
    forn(i,n) cin>>arr[i][0];
    forn(i,n) cin>>arr[i][1];
 
    vector<vector<int>>dp(n+1,vector<int>(x+1,0));
    forne(i,1,n+1){
        forne(j,1,x+1){
            dp[i][j]=dp[i-1][j];
            if(j-arr[i-1][0]>=0){
                int libro=arr[i-1][1];
                int price=arr[i-1][0];
                dp[i][j]=max(dp[i][j], libro+dp[i-1][j-price]);
             }
 
        }
    }
    cout<<dp[n][x]<<endl;


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