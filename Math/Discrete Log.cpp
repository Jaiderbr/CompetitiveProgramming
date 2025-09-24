// Returns minimum x for which a ^ x % m = b % m, a and m are coprime.
#define int int64_t
constexpr int INF = 1e18;
int discrete_log(int b, int a, int m) {
    if (a == 0) return b ? -1 : 1; // base case?

    a %= m, b %= m;
    int k = 1, shift = 0;
    while (1) {
        int g = __gcd(a, m);
        if (g == 1) break;
        if (b == k) return shift;
        if (b % g) return -1;
        b /= g, m /= g, shift++;
        k = (int)k * a / g % m;
    }

    int sq = sqrt(m) + 1, giant = 1;
    forn(i, sq) giant = (int)giant * a % m;

    vector<pair<int, int>> baby;
    for (int i = 0, cur = b; i <= sq; i++) {
        baby.emplace_back(cur, i);
        cur = (int)cur * a % m;
    }
    sort(all(baby));

    for (int j = 1, cur = k; j <= sq; j++) {
        cur = (int)cur * giant % m;
        auto it = lower_bound(all(baby), make_pair(cur, INF));
        if (it != baby.begin() and (--it)->f == cur) return sq * j - it->s + shift;
    }

    return -1;
}