#define PI acos(-1)
struct chash {
    // any random-ish large odd number will do
    const uint64_t C = uint64_t(4e18 * PI) + 71;
    const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    size_t operator()(uint64_t x) const { return __builtin_bswap64((x ^ RANDOM) * C); }
};

template <class K, class V> using u_map = unordered_map<K, V, chash>;
template <class K> using u_set = unordered_set<K, chash>;