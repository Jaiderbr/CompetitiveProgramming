/*
Dado un string S, cuantas veces aparece una subsencuencia P en S
ejemplo:
S=AABBJAB
P=AB
ans=7


vector<vector<int>> dp(NS + 1, vector<int>(NP + 1, -1));
int ans = count(s, p, NS, NP, dp);

*/


int count(string& S, string& P, int NS, int NP, vector<vector<int>>& dp) {
    if ((NS == 0 && NP == 0) || NP == 0) return 1;
    if (NS == 0) return 0;
    if (dp[NS][NP] != -1) return dp[NS][NP];

    if (S[NS - 1] == P[NP - 1]) {
        return dp[NS][NP] = count(S, P, NS - 1, NP - 1, dp) + count(S, P, NS - 1, NP, dp);
    }
    else {
        return dp[NS][NP] = count(S, P, NS - 1, NP, dp);
    }
}