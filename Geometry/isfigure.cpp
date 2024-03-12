#include <bits/stdc++.h>
using namespace std;
#define endl     '\n' 
#define f        first
#define s        second
#define ins      insert
#define pb       push_back
#define eb       emplace_back
#define sz(x)    int((x).size())
#define all(x)   begin(x), end(x)
typedef long long ll;
typedef unsigned long long ull;
#define forn(i, n) for (int i = 0; i < n; ++i)
#define each(i, x) for (auto &&i : x)
#define forne(i,x,n) for (int i = x; i < n; ++i)
#define show(x) for (auto &&i : x) {cerr << i <<' ';} cerr<< endl;


#define LOCAL
void dbg_out() { cerr << ']' << endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) { cerr << H;if (sizeof...(T)) cerr << ',' << ' '; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cerr << '|' << __LINE__ << '|'<< '{' << #__VA_ARGS__ << '}'<<':'<<' '<<'[', dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif



typedef ll T;
struct pt {
    T x, y;
    pt() : x(0), y(0) {}
    pt(T _x, T _y) : x(_x), y(_y) {}
    pt operator+(pt p) { return { x + p.x, y + p.y }; }
    pt operator-(pt p) { return { x - p.x, y - p.y }; }
    pt operator*(T d) { return { x * d, y * d }; }
    pt operator/(T d) { return { x / d, y / d }; }
    bool operator==(pt b) { return x == b.x && y == b.y; }
    bool operator!=(pt b) { return x != b.x || y != b.y; }
    bool operator<(pt b) { return x == b.x ? y < b.y : x < b.x; }

    void read() {
        cin >> x >> y;
    }
};
const double PI = acos(-1);
double DEG_TO_RAD(double n) { return n * PI / 180.0; }
double RAD_TO_DEG(double n) { return n * 180.0 / PI; }
T sq(pt p) { return p.x * p.x + p.y * p.y; }
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
double abs(pt p) { return sqrt(sq(p)); }
T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
T dis(pt a, pt b) { return sq(a - b); }
//Transformaciones
pt translate(pt v, pt p) { return p + v; }
pt scale(pt c, double factor, pt p) { return c + (p - c) * factor; }
pt rot(pt p, double ang) { return { p.x * cos(ang) - p.y * sin(ang), p.x * sin(ang) + p.y * cos(ang) }; }
pt perp(pt p) { return { -p.y, p.x }; }
T isParall(pt v, pt w) { return cross(v, w) == 0; }


// A square has four right angles and four sides with equal lengths.
bool isSquare(pt a, pt b, pt c, pt d) {
    T ab = dis(a, b);
    T bc = dis(b, c);
    T cd = dis(c, d);
    T ad = dis(a, d);
    return isParall(a - b, c - d) && isParall(a - d, b - c) && dot(b - a, d - a) == 0 && ab == bc && bc == cd && cd == ad;
}

// A rectangle has four right angles.
bool isRectangle(pt a, pt b, pt c, pt d) {
    return isParall(a - b, c - d) && isParall(a - d, b - c) && dot(b - a, d - a) == 0;
}

// A rhombus has four sides with equal lengths.
bool isRhombus(pt a, pt b, pt c, pt d) {
    T ab = dis(a, b);
    T bc = dis(b, c);
    T cd = dis(c, d);
    T ad = dis(a, d);
    return ab == bc && bc == cd && cd == ad;
}

// A parallelogram has two pairs of parallel sides.
bool isParallelogram(pt a, pt b, pt c, pt d) {
    return isParall(a - b, c - d) && isParall(a - d, b - c);
}

// A trapezium has one pair of parallel sides.
bool isTrapezium(pt a, pt b, pt c, pt d) {
    return isParall(a - b, c - d) || isParall(a - d, b - c);
}

// A kite has reflection symmetry across a diagonal.
bool isKite(pt a, pt b, pt c, pt d) {
    T ab = dis(a, b);
    T bc = dis(b, c);
    T cd = dis(c, d);
    T ad = dis(a, d);
    return (ab == bc && cd == ad) || (ab == ad && bc == cd);
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    pt a, b, c, d;
    a.read(); b.read(); c.read(); d.read();

    if (isSquare(a, b, c, d))             cout << "square" << endl;
    else if (isRectangle(a, b, c, d))     cout << "rectangle" << endl;
    else if (isRhombus(a, b, c, d))       cout << "rhombus" << endl;
    else if (isParallelogram(a, b, c, d)) cout << "parallelogram" << endl;
    else if (isTrapezium(a, b, c, d))     cout << "trapezium" << endl;
    else if (isKite(a, b, c, d))          cout << "kite" << endl;
    else cout << "none" << endl;











    cout << flush;
    return 0;
}