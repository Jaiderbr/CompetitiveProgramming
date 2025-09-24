/*
Math/Pow.cpp
Math/Phi.cpp
Math/Factorization Sieve.cpp
Math/Pollards Rho.cpp ...?
*/

//find g -> (g^k == a mod m) for all a -> gcd(a, m)=1
int primitive_root(int m) {
    int phin = phi(m);
    map<int, int> factors = factorize(phin);
    /*
    phollards rho
    phin = m-1? -> m is prime
    vector<int> ffactors = fact(phin);
    sort(all(f)); f.erase(unique(all(f)), f.end());
    */

    forne(i, 1, m + 1) {
        bool ok = true;
        for (auto it : factors) {
            ok = ok && pow(i, phin / it.f, m) != 1;
            if (!ok) break;
        }
        if (ok) return i;
    }
    return -1;
}