// Computa el numero de inversiones para transformar
// l en r (si no es posible, retorna -1)

template<typename T> int inversion_count(vector<T> l, vector<T> r = {}) {
    if (!sz(r)) {
        r = l;
        sort(all(r));
    }
    int n = sz(l);
    vector<int> v(n), bit(n);
    vector<pair<T, int>> w;
    forn(i, n) w.pb({ r[i], i + 1 });
    sort(all(w));
    forn(i, n) {
        auto it = lower_bound(w.begin(), w.end(), make_pair(l[i], int(0)));
        if (it == w.end() or it->first != l[i]) return -1; // no da
        v[i] = it->second;
        it->second = -1;
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = v[i] - 1; j; j -= j & -j) ans += bit[j];
        for (int j = v[i]; j < n; j += j & -j) bit[j]++;
    }

    return ans;
}