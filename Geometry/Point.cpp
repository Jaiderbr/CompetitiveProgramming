typedef long double T;
const T PI = acos(-1.0);
struct pt {
    T x, y;
    pt() : x(0), y(0) {}
    pt(T _x, T _y) : x(_x), y(_y) {}
    pt& operator+=(const pt& a) { x += a.x; y += a.y; return *this; }
    pt& operator-=(const pt& a) { x -= a.x; y -= a.y; return *this; }
    pt& operator*=(T mult) { x *= mult; y *= mult; return *this; }
    pt operator+(const pt& a) const { return pt(*this) += a; }
    pt operator-(const pt& a) const { return pt(*this) -= a; }
    pt operator*(T mult) const { return pt(*this) *= mult; }
    bool operator==(const pt& a) const { return x == a.x && y == a.y; }
    bool operator!=(const pt& a) const { return !(*this == a); }
    bool operator<(const pt& a) { return x == a.x ? y < a.y : x < a.x; }
    pt operator-() const { return pt(-x, -y); }
    pt rotate90() const { return pt(-y, x); }
    T norm() const { return (T)x * x + (T)y * y; }
    T dist() const { return sqrt(T(norm())); }
    bool top_half() const { return y > 0 || (y == 0 && x > 0); }
    friend ostream& operator<<(ostream& os, const pt& p) { return os << '(' << p.x << ", " << p.y << ')'; }
    friend istream& operator>>(istream& is, pt& p) { return is >> p.x >> p.y; }
};

T DEG_TO_RAD(T n) { return n * PI / 180.0; }
T RAD_TO_DEG(T n) { return n * 180.0 / PI; }
T abs(pt p) { return sqrt(p.norm()); }
pt perp(pt p) { return { -p.y, p.x }; }

// Producto Cruz
T cross(const pt& a, const pt& b) { return (T)a.x * b.y - (T)b.x * a.y; }

// Producto Escalar -> a * b = b * a -> (ang * a) * b = ang * (a * b) -> (a + b) * c = a * c + b * c
T dot(const pt& a, const pt& b) { return (T)a.x * b.x + (T)a.y * b.y; }
pt rot(pt p, double ang) { return { p.x * cos(ang) - p.y * sin(ang), p.x * sin(ang) + p.y * cos(ang) }; }
bool isPerp(pt v, pt w) { return !dot(v, w); }
// colinear == 0, left > 0, right < 0
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
//Angulo(b-a, c-a), de 0 a 180
T angle(pt v, pt w) {
    T cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(T(-1.0), min(T(1.0), cosTheta)));
}

//De 0 a 360
T angle_complete(pt a, pt b, pt c) {
    pt ab = { b.x - a.x, b.y - a.y };
    pt cb = { b.x - c.x, b.y - c.y };
    T rslt = atan2(ab.y, ab.x) - atan2(cb.y, cb.x);
    return fabs((rslt * 180.0) / PI);
}

//Si un pt se encuentra dentro del angulo ABC
bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

T orientedAngle(pt a, pt b, pt c) {
    if (orient(a, b, c) >= 0) return angle(b - a, c - a);
    return 2 * PI - angle(b - a, c - a);
}

// Si un poligono es convexo
bool isConvex(vector<pt> p) {
    bool hasPos = 0, hasNeg = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        int64_t o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = 1;
        if (o < 0) hasNeg = 1;
    }
    return !(hasPos && hasNeg);
}

// Devuelve el doble del area formada por tres puntos de un triangulo. Positivo cuando a -> b -> c es un giro a la izquierda.
T area_signed_2x(const pt& a, const pt& b, const pt& c) { return cross(b - a, c - a); }

T distance_to_line(const pt& p, const pt& a, const pt& b) {
    assert(a != b);
    return T(abs(area_signed_2x(p, a, b))) / (a - b).dist();
}

T manhattan_dist(const pt& a, const pt& b) {
    return (T)abs(a.x - b.x) + abs(a.y - b.y);
}
T euclidean_dist(const pt& a, const pt& b) {
    return (a - b).dist();
}

T infinity_norm_dist(const pt& a, const pt& b) {
    return max(abs(a.x - b.x), abs(a.y - b.y));
}

// Ordenar en orden creciente de y, deshaciendo los empates en orden creciente de x.
bool yx_compare(const pt& a, const pt& b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}