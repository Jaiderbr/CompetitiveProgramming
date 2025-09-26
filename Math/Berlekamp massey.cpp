/*
"Se le da una secuencia y se puede encontrar la k-esima"
Math/Propiedades del modulo.cpp
*/

// #define int int64_t
struct Berlekamp_massey {

    int m; //length of recurrence
    //a: first terms
    //h: relation
    vector<int> a, h, t_, s, t;

    Berlekamp_massey(vector<int>& x) {
        vector<int> v = BM(x);
        m = sz(v);
        h.resize(m), a.resize(m), s.resize(m), t.resize(m), t_.resize(2 * m);
        forn(i, m) h[i] = v[i], a[i] = x[i];
    }

    vector<int> BM(vector<int>& x) {
        vector<int> ls, cur;
        int lf, ld;
        forn(i, sz(x)) {
            int t = 0;
            forn(j, sz(cur)) t = (t + x[i - j - 1] * (int)cur[j]) % MOD;
            if ((t - x[i]) % MOD == 0) continue;
            if (!sz(cur)) {
                cur.resize(i + 1);
                lf = i;
                ld = (t - x[i]) % MOD;
                continue;
            }
            int k = -(x[i] - t) * inv_mod(ld);
            vector<int> c(i - lf - 1); c.pb(k);
            forn(j, sz(ls)) c.pb(-ls[j] * k % MOD);
            if (sz(c) < sz(cur)) c.resize(sz(cur));
            forn(j, sz(cur)) c[j] = (c[j] + cur[j]) % MOD;
            if (i - lf + sz(ls) >= sz(cur)) ls = cur, lf = i, ld = (t - x[i]) % MOD;
            cur = c;
        }
        forn(i, sz(cur)) cur[i] = (cur[i] % MOD + MOD) % MOD;
        return cur;
    }
    //calculate p*q MOD f
    inline vector<int> mul(vector<int>& p, vector<int>& q) {
        forn(i, 2 * m) t_[i] = 0;
        forn(i, m) if (p[i]) {
            forn(j, m) t_[i + j] = (t_[i + j] + p[i] * q[j]) % MOD;
        }
        for (int i = 2 * m - 1;i >= m;--i) if (t_[i]) {
            forn(j, m) t_[i - j - 1] = (t_[i - j - 1] + t_[i] * h[j]) % MOD;
        }
        forn(i, m) p[i] = t_[i];
        return p;
    }

    inline int magic(int k) {
        if (k < sz(a)) return a[k];
        forn(i, m) s[i] = t[i] = 0;
        s[0] = 1;
        if (m != 1) t[1] = 1;
        else t[0] = h[0];

        while (k) {
            if (k & 1LL) s = mul(s, t);
            t = mul(t, t); k /= 2;
        }
        int su = 0;
        forn(i, m) su = (su + s[i] * a[i]) % MOD;
        return (su % MOD + MOD) % MOD;
    }

};
