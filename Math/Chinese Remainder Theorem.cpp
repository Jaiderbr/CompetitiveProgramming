//ext_gcd(a,b): return {g, x, y} tal que g = gcd(a,b) y a * x + b * y = g.

template<typename T> tuple<T, T, T> ext_gcd(T a, T b) {
    if (!a) return { b, 0, 1 };
    auto [g, x, y] = ext_gcd(b % a, a);
    return { g, y - b / a * x, x };
}

/*
Dadas dos congruencias
x == a (mod n)
x == b (mod m)
con gcd(n ,m) = 1, existe una solucion unica modulo K = n * m.
a = residuo en [0,lcm)
m = lcm de los modulos.
crt<int> c1(a, n), c2(b, m), sol = c1 * c2;
*/

template<typename T = int64_t > struct crt {
    T a, m;
    crt() : a(0), m(1) {}
    crt(T a_, T m_) : a(a_), m(m_) {}
    crt operator * (crt C) {
        auto [g, x, y] = ext_gcd(m, C.m);
        if ((a - C.a) % g) a = -1;
        if (a == -1 or C.a == -1) return crt(-1, 0);
        T lcm = m / g * C.m;
        T ans = a + (x * (C.a - a) / g % (C.m / g)) * m;
        return crt((ans % lcm + lcm) % lcm, lcm);
    }
};
