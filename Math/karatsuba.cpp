/*
Multiplica dos polinomios A y B
Devuelve un vector C, donde C[i] = coeficiente de x^i en A*B
good: n ~ 2e5
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target ("avx,avx2")
template<typename T> void kar(T* a, T* b, int n, T* r, T* tmp) {
    if (n <= 64) {
        forn(i, n) forn(j, n) r[i + j] += a[i] * b[j];
        return;
    }
    int mid = n / 2;
    T* atmp = tmp, * btmp = tmp + mid, * E = tmp + n;
    memset(E, 0, sizeof(E[0]) * n);
    forn(i, mid) {
        atmp[i] = a[i] + a[i + mid];
        btmp[i] = b[i] + b[i + mid];
    }
    kar(atmp, btmp, mid, E, tmp + 2 * n);
    kar(a, b, mid, r, tmp + 2 * n);
    kar(a + mid, b + mid, mid, r + n, tmp + 2 * n);
    forn(i, mid) {
        T temp = r[i + mid];
        r[i + mid] += E[i] - r[i] - r[i + 2 * mid];
        r[i + 2 * mid] += E[i + mid] - temp - r[i + 3 * mid];
    }
}

template<typename T> vector<T> karatsuba(vector<T> a, vector<T> b) {
    int n = max(sz(a), sz(b));
    while (n & (n - 1)) n++;
    a.resize(n), b.resize(n);
    vector<T> ret(2 * n), tmp(4 * n);
    kar(&a[0], &b[0], n, &ret[0], &tmp[0]);
    return ret;
}
