// #include <complex> ...?

/*
usage complex<double> como tipo de dato
vector<complex<double>> a(k + 1), b(k + 1);
vector<complex<double>> c = convolution(a, b);
(int)(c[i].real() + 0.5) para redondear
*/


void get_roots(bool f, int n, vector<complex<double>>& roots) {
    const static double PI = acosl(-1);
    forn(i, n / 2) {
        double alpha = i * ((2 * PI) / n);
        if (f) alpha = -alpha;
        roots[i] = { cos(alpha), sin(alpha) };
    }
}
template<typename T> void fft(vector<T>& a, bool f, int N, vector<int>& rev) {
    forn(i, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
    int l, r, m;
    vector<T> roots(N);
    for (int n = 2; n <= N; n *= 2) {
        get_roots(f, n, roots);
        for (int pos = 0; pos < N; pos += n) {
            l = pos + 0, r = pos + n / 2, m = 0;
            while (m < n / 2) {
                auto t = roots[m] * a[r];
                a[r] = a[l] - t;
                a[l] = a[l] + t;
                l++, r++, m++;
            }
        }
    }
    if (f) {
        auto invN = T(1) / T(N);
        forn(i, N) a[i] = a[i] * invN;
    }
}

template<typename T> vector<T> convolution(vector<T>& a, vector<T>& b) {
    vector<T> l(all(a)), r(all(b));
    int N = sz(l) + sz(r) - 1;
    int n = 1, log_n = 0;
    while (n <= N) n *= 2, log_n++;
    vector<int> rev(n);
    forn(i, n) {
        rev[i] = 0;
        forn(j, log_n) if (i >> j & 1) {
            rev[i] |= 1 << (log_n - 1 - j);
        }
    }
    assert(N <= n);
    l.resize(n);
    r.resize(n);
    fft(l, false, n, rev);
    fft(r, false, n, rev);
    forn(i, n) l[i] *= r[i];
    fft(l, true, n, rev);
    l.resize(N);
    return l;
}
