vector<int> suffix_array(string s) {
    s += "$";
    int MAX = 260, n = sz(s), N = max(n, MAX);
    vector<int> sa(n), ra(n);
    for (int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for (int k = 0; k < n; k ? k *= 2 : k++) {
        vector<int> nsa(sa), nra(n), cnt(N);
        for (int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n, cnt[ra[i]]++;
        for (int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i + 1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
        for (int i = 1, r = 0; i < n; i++) nra[sa[i]] = r += ra[sa[i]] != ra[sa[i - 1]] || ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n];
        ra = nra;
        if (ra[sa[n - 1]] == n - 1) break;
    }
    return vector<int>(sa.begin() + 1, sa.end());
}

vector<int> kasai(string s, vector<int> sa) {
    int n = sz(s), k = 0;
    vector<int> ra(n + 1), lcp(n);
    for (int i = 0; i < n; i++) ra[sa[i]] = i;
    for (int i = 0; i < n; i++, k -= !!k) {
        if (ra[i] == n - 1) { k = 0; continue; }
        int j = sa[ra[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[ra[i]] = k;
    }
    return lcp;
}
/*
find the number of occurrences of the string t in the string s
*/
int find_str(string& s, string& t, vector<int>& sa) {
    int n = sz(s);
    if (sz(t) > n) return 0;
    int L = 0, R = n - 1;
    int nL, nR;
    for (int i = 0; i < sz(t); i++) {
        int l = L, r = R + 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (i + sa[m] >= n || s[i + sa[m]] < t[i]) l = m + 1;
            else r = m;
        }
        if (l == R + 1 || s[i + sa[l]] > t[i]) return 0;
        nL = l, l = L, r = R + 1;

        while (l < r) {
            int m = (l + r) / 2;
            if (i + sa[m] >= n || s[i + sa[m]] <= t[i]) l = m + 1;
            else r = m;
        }
        l--;
        nR = l, L = nL, R = nR;
    }
    return (nL <= nR ? nR - nL + 1 : 0);
}
/*
find the longest common substring what
appear in the string s at least least twice
*/
string lcs(vector<int>& sa, vector<int>& ka, string& s) {
    int idx = max_element(all(ka)) - begin(ka);
    return (ka[idx] > 0 ? s.substr(sa[idx], ka[idx]) : "-1");
}
/*
Find the longest common substring of two given strings s and t
create a new string s + '#' + t
compute the suffix array of the new string
compute the LCP array of the new string
pos_t = (i_s ? sa[i + 1] - (n + 1) : sa[i] - (n + 1));
*/
string find_lcs(string& s, string& t, vector<int>& sa, vector<int>& lcp) {
    int best = 0, n = sz(s), pos = INT_MAX;
    for (int i = 0; i < sz(lcp) - 1; i++) {
        bool i_s = (0 <= sa[i] && sa[i] <= n - 1);
        bool j_s = (0 <= sa[i + 1] && sa[i + 1] <= n - 1);
        if (i_s != j_s && best < lcp[i]) {
            best = lcp[i];
            pos = min(sa[i], sa[i + 1]);
        }
    }
    return pos == INT_MAX ? "" : s.substr(pos, best);
}
vector<int>substr_begin_by_letter(const string& s, const vector<int>& sa, const vector<int>& lcp) {
    vector<int>abc(26);
    int n = sz(s);
    forn(i, n) abc[s[sa[i]] - 'a'] += n - sa[i] - lcp[i];
    return abc;
}
int dis_substr(const string& s, const vector<int>& sa, const vector<int>& lcp) {
    int n = sz(s), ans = 0;
    forn(i, n) ans += n - sa[i] - lcp[i];
    return ans;
}

/*
Se llama subsecuencia "Refrain" si el producto de su longitud y 
el numero de ocurrencias en la matriz es el máximo posible.

ejmplo:
8 3
1 2 1 2 1 1 2 1
Output:
9
3
1 2 1
*/
pair<int, string> findRefrain(const string& s, const vector<int>& lcp, const vector<int>& suffix) {
    stack<int> monoStack;
    const int n = sz(lcp);
    int maxArea = sz(s);
    string res = s;
    forn(i, n + 1) {
        int x = (i == n ? 0 : lcp[i]);
        while (!monoStack.empty() && lcp[monoStack.top()] > x) {
            int tp = monoStack.top();
            monoStack.pop();
            int h = lcp[tp], w = (monoStack.empty() ? i : i - 1 - monoStack.top());
            int area = h * (w + 1);
            if (area > maxArea) {
                maxArea = area;
                res = s.substr(suffix[i - w], h);
            }
        }
        monoStack.push(i);
    }
    return { maxArea, res };
}
