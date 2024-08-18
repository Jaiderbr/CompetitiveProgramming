int rnd(int l, int r) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(l, r)(rng);
}