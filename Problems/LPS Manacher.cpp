// longest palindromic in range [i, j] in O(1) 

//include "../String/Manacher.cpp"

constexpr int mxN = 1001;
int best[mxN][mxN];

main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    string s; cin >> s;

    palindrome<string> pal(s);
    forn(i, n) best[i][i] = 1;

    forne(len, 2, n + 1) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            best[i][j] = max(best[i + 1][j], best[i][j - 1]);
            if (pal.query(i, j)) best[i][j] = len;
        }
    }

    int q, l, r; cin >> q;

    while (q--) {
        cin >> l >> r;
        cout << best[l - 1][r - 1] << endl;
    }

    cout << flush;
    return 0;
}
