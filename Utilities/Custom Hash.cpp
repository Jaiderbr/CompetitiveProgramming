#define PI acos(-1)
struct chash {
    const uint64_t C = uint64_t(4e18 * PI) + 71;
    const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    size_t operator()(uint64_t x) const { return __builtin_bswap64((x ^ RANDOM) * C); }
    template <class A, class B>
    size_t operator()(const pair<A, B>& p) const {
        uint64_t h1 = (*this)(uint64_t(p.f));
        uint64_t h2 = (*this)(uint64_t(p.s));
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

template <class K, class V> using u_map = unordered_map<K, V, chash>;
template <class K> using u_set = unordered_set<K, chash>;
