// Dado un patron S y un texto T, se desea conocer los indices de las ocurrencias del patron S en el texto T.

vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31;
    const int m = 1e9 + 9;
    int S = sz(s), T = sz(t);

    vector<int64_t> p_pow(max(S, T)), h(T + 1, 0);
    p_pow[0] = 1;
    int64_t h_s = 0;
    forne(i, 1, sz(p_pow)) p_pow[i] = (p_pow[i - 1] * p) % m;
    forn(i, T) h[i + 1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m;
    forn(i, S) h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;

    vector<int> occ;
    for (int i = 0; i + S - 1 < T; i++) {
        int64_t cur_h = (h[i + S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m) occ.pb(i);
    }
    return occ;
}