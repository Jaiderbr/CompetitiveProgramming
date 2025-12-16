/*
Debes construirlo con un vector que contenga todos los puntos
que quieres actualizar algún día (los puntos que llamarás actualización)
*/

template<class T = int> struct bit2d {
    vector<T> X;
    vector<vector<T>> Y, t;

    int ub(vector<T>& v, T x) {
        return upper_bound(all(v), x) - v.begin();
    }
    bit2d(vector<pair<T, T>> v) {
        for (auto [x, y] : v) X.pb(x);
        sort(all(X));
        X.erase(unique(all(X)), X.end());

        t.resize(sz(X) + 1);
        Y.resize(sz(t));
        sort(all(v), [](auto a, auto b) {
            return a.s < b.s; });
        for (auto [x, y] : v) for (int i = ub(X, x); i < sz(t); i += i & -i)
            if (!sz(Y[i]) or Y[i].back() != y) Y[i].pb(y);

        for (int i = 0; i < sz(t); i++) t[i].resize(sz(Y[i]) + 1);
    }

    void update(T x, T y, T v) {
        for (int i = ub(X, x); i < sz(t); i += i & -i)
            for (int j = ub(Y[i], y); j < sz(t[i]); j += j & -j) t[i][j] += v;
    }

    T query(T x, T y) {
        T ans = 0;
        for (int i = ub(X, x); i; i -= i & -i)
            for (int j = ub(Y[i], y); j; j -= j & -j) ans += t[i][j];
        return ans;
    }
    T query(T x1, T y1, T x2, T y2) {
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }
};
