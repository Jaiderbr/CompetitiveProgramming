// manacher receives a vector of T and returns the vector with the size of the palindromes
// ret[2*i] = size of the largest palindrome centered at i
// ret[2*i+1] = size of the largest palindrome centered at i and i+1
//
// Complexities:
// manacher - O(n)
// palindrome - <O(n), O(1)>
// pal_end - O(n)

template<typename T> vector<int> manacher(const T& s) {
    int l = 0, r = -1, n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i);
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1); k++;
        while (i + k <= n && i - k >= 0 && s[i + k - 1] == s[i - k]) k++;
        d2[i] = --k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
    vector<int> ret(2 * n - 1);
    for (int i = 0; i < n; i++) ret[2 * i] = 2 * d1[i] - 1;
    for (int i = 0; i < n - 1; i++) ret[2 * i + 1] = 2 * d2[i + 1];
    return ret;
}

// checks if string s[i..j] is palindrome
template<typename T> struct palindrome {
    vector<int> man;

    palindrome(const T& s) : man(manacher(s)) {}
    bool query(int i, int j) {
        return man[i + j] >= j - i + 1;
    }
};

// size of the largest palindrome ending in each position
template<typename T> vector<int> pal_end(const T& s) {
    vector<int> ret(s.size());
    palindrome<T> p(s);
    ret[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        ret[i] = min(ret[i - 1] + 2, i + 1);
        while (!p.query(i - ret[i] + 1, i)) ret[i]--;
    }
    return ret;
}

//expansion 
int odd(int d, int i, int n) {
    // d=(manacher[2 * i], i)
    int l = i - (d - 1) / 2;
    int r = i + (d - 1) / 2;

    while (l >= 0 && r < n) {
        //process 
        l -= 1; r += 1;
    }
    return ((r - 1) - (l + 1) + 2) / 2;
}
int even(int d, int i, int n) {
    // d=(manacher[2 * i+1], i)
    if (i == n - 1) return 0;
    if (d == 0) d = 2;
    int l = i - d / 2 + 1;
    int r = i + d / 2;

    while (l >= 0 && r < n) {
        //process
        l -= 1; r += 1;
    }
    return ((r - 1) - (l + 1) + 2) / 2;
}


// largest palindrome
string manacher(const string& s) {
    if (sz(s) == 0) return "";

    string curr = "";
    for (auto&& i : s) {
        curr += i;
        curr += "#";
    }

    curr = "@#" + curr + "&";
    vector<ll> pali(sz(curr), 0);
    ll center = 0;
    ll R = 0;
    for (ll i = 1; i < sz(curr) - 1; i++) {
        if (i < R) pali[i] = min(pali[2 * center - i], R - i);
        while (curr[i + (pali[i] + 1)] == curr[i - (pali[i] + 1)]) pali[i]++;
        if (i + pali[i] > R) {
            center = i;
            R = i + pali[i];
        }
    }
    ll HC = 0, CI = 0;
    for (ll i = 1; i < sz(curr) - 1; i++) {
        if (pali[i] > HC) {
            HC = pali[i];
            CI = i;
        }
    }
    string ans = "";
    if (HC <= 0) return string(1, s[0]);
    for (ll i = CI - HC + 1; i <= CI + HC - 1; i += 2) ans += curr[i];
    return ans;
}
