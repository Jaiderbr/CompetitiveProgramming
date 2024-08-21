/*
size() number of different palindrome substr
propagate() number of palindrome substr
lps longest palindrome substr {star, len}
*/

struct paltree {
    vector<vector<int>> t;
    int n, last, sz;
    vector<int> s, len, link, qt;
    pair<int, int> lps{ 0,0 };

    paltree(int N) {
        t.assign(N + 2, vector<int>(26, int()));
        s = len = link = qt = vector<int>(N + 2);
        s[0] = -1, link[0] = 1, len[0] = 0, link[1] = 1, len[1] = -1;
        sz = 2, last = 0, n = 1;
    }

    void add(char c) {
        s[n++] = c -= 'a';
        while (s[n - len[last] - 2] != c) last = link[last];
        if (!t[last][c]) {
            int prev = link[last];
            while (s[n - len[prev] - 2] != c) prev = link[prev];
            link[sz] = t[prev][c];
            len[sz] = len[last] + 2;
            t[last][c] = sz++;
            if (len[sz - 1] > lps.s) {
                lps = { n - len[sz - 1] - 1 ,len[sz - 1] };
            }
        }
        qt[last = t[last][c]]++;
    }
    int size() {
        return sz - 2;
    }

    ll propagate() {
        ll cnt = 0;
        for (int i = n; i > 1; i--) {
            qt[link[i]] += qt[i];
            cnt += qt[i];
        }
        return cnt;
    }

};