
//find all x -> x^k = a mod n
vector<int> discrete_root(int k, int a, int n) {
    int g = primitive_root(n);
    int gk = binpow(g, k, n);
    int y = discrete_log(gk, a, n);
    int x = binpow(g, y, n);//first solution
    int phin = phi(n);
    int delta = phin / __gcd(k, phin);

    vector<int> v;
    for (int i = 0; i < n - 1; i += delta) {
        x = binpow(g, y + i, n);
        v.pb(x);
    }
    return v;
}