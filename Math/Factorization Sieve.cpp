#define int int64_t
constexpr int MAX = 1e6;
int primediv[MAX]; //10^6
vector<int> primes;

void sieve() {
    forn(i, MAX) primediv[i] = i;
    int root = sqrt(MAX) + 1;
    forne(i, 2, MAX) {
        if (primediv[i] != i) continue;
        primes.pb(i);
        if (i > root) continue;
        for (int j = i * i; j < MAX; j += i) primediv[j] = i;
    }
}

map<int, int> factorize(int n) { //n <= 10^12
    map<int, int> factors;
    for (int i = 0; i < primes.size() && n >= MAX; ++i) {
        while (n % primes[i] == 0) {
            factors[primes[i]]++;
            n /= primes[i];
        }
    }
    if (n >= MAX) {
        factors[n]++;
        return factors;
    }
    while (n > 1) {
        factors[primediv[n]]++;
        n /= primediv[n];
    }
    return factors;
}