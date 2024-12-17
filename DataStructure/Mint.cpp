template <typename T, T m>
struct modint {
    T x;
    constexpr static T mod() { return m; }
    constexpr T val() const { return x; }
    constexpr modint() : x(0) {}
    modint(T x_) :x(x_% mod()) { if (x < 0) x += mod(); }
    modint& operator+=(modint b) { if ((x += b.x) >= mod()) x -= mod(); return *this; }
    modint& operator-=(modint b) { if ((x -= b.x) < 0) x += mod(); return *this; }
    modint& operator*=(modint b) { x = (T)(x)*b.x % mod(); return *this; }
    modint pow(T e) const {
        modint r = 1, b = *this;
        while (e) {
            if (e & 1) r *= b;
            b *= b, e >>= 1;
        }
        return r;
    }
    modint inv() { return pow(mod() - 2); }
    modint& operator /=(modint b) { return *this *= b.pow(mod() - 2); }
    friend modint operator+ (modint a, modint b) { return a += b; }
    friend modint operator- (modint a, modint b) { return a -= b; }
    friend modint operator/ (modint a, modint b) { return a /= b; }
    friend modint operator* (modint a, modint b) { return a *= b; }
    friend bool   operator< (modint a, modint b) { return a.x < b.x; }
    friend bool   operator> (modint a, modint b) { return a.x > b.x; }
    friend bool   operator==(modint a, modint b) { return a.x == b.x; }
    friend bool   operator!=(modint a, modint b) { return a.x != b.x; }
    friend ostream& operator<<(ostream& os, const modint& a) { return os << a.val(); }
};
constexpr int mod = 1000000007;
using mint = modint<int, mod>;