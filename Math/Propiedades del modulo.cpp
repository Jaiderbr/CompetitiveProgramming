constexpr int MOD = 1e9 + 7;
inline int add(int a, int b, const int& mod = MOD) { return a + b >= mod ? a + b - mod : a + b; }
inline int sbt(int a, int b, const int& mod = MOD) { return a - b < 0 ? a - b + mod : a - b; }
inline int mul(int a, int b, const int& mod = MOD) { return 1ll * a * b % mod; }