using ld = long double;

struct pt {
    int64_t x, y;

    pt() : x(0), y(0) {}
    pt(int64_t _x, int64_t _y) : x(_x), y(_y) {}

    pt& operator+=(const pt &other) { x += other.x; y += other.y; return *this; }
    pt& operator-=(const pt &other) { x -= other.x; y -= other.y; return *this; }
    pt& operator*=(int64_t mult) { x *= mult; y *= mult; return *this; }

    pt operator+(const pt &other) const { return pt(*this) += other; }
    pt operator-(const pt &other) const { return pt(*this) -= other; }
    pt operator*(int64_t mult) const { return pt(*this) *= mult; }

    bool operator==(const pt &other) const { return x == other.x && y == other.y; }
    bool operator!=(const pt &other) const { return !(*this == other); }
    bool operator<(const pt &other) {return x == other.x? y < other.y : x < other.x;}

    pt operator-() const { return pt(-x, -y); }
    pt rotate90() const { return pt(-y, x); }

    int64_t norm() const {
        return (int64_t) x * x + (int64_t) y * y;
    }

    ld dist() const {
        return sqrt(ld(norm()));
    }

    bool top_half() const {
        return y > 0 || (y == 0 && x > 0);
    }

    friend ostream& operator<<(ostream &os, const pt &p) {
        return os << '(' << p.x << ", " << p.y << ')';
    }
};

const ld PI = acos(-1);
ld DEG_TO_RAD(ld n){ return n * PI / 180.0; }
ld RAD_TO_DEG(ld n){ return n * 180.0 / PI; }
ld abs(pt p) {return sqrt(p.norm());}

pt perp(pt p) {return {-p.y, p.x};}

// Producto Cruz
int64_t cross(const pt &a, const pt &b) {
    return (int64_t) a.x * b.y - (int64_t) b.x * a.y;
}

// Producto Escalar -> a * b = b * a -> (ang * a) * b = ang * (a * b) -> (a + b) * c = a * c + b * c
int64_t dot(const pt &a, const pt &b) {
    return (int64_t) a.x * b.x + (int64_t) a.y * b.y;
}

pt rot(pt p, double ang) { return {p.x * cos(ang) - p.y * sin(ang), p.x * sin(ang) + p.y * cos(ang)};}

bool isPerp(pt v, pt w) {return !dot(v, w);}

//Angulo(b-a, c-a), de 0 a 180
ld angle(pt v, pt w) {
    ld cosTheta = dot(v,w) / abs(v) / abs(w);
    return acos(max(ld(-1.0), min(ld(1.0), cosTheta)));
}

//De 0 a 360
ld angle_complete(pt a, pt b, pt c){
	pt ab = {b.x - a.x, b.y - a.y};
	pt cb = {b.x - c.x, b.y - c.y};
	ld rslt = atan2(ab.y, ab.x) - atan2(cb.y, cb.x);
	return fabs((rslt * 180.0) / PI);
}

//Si un pt se encuentra dentro del angulo ABC
bool inAngle(pt a, pt b, pt c, pt p) { 
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b,c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

ld orientedAngle(pt a, pt b, pt c) {
    if (orient(a,b,c) >= 0) return angle(b-a, c-a);
    return 2*M_PI - angle(b-a, c-a);
}

// Si un poligono es convexo
bool isConvex(vector<pt> p) {
    bool hasPos = 0, hasNeg = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        int64_t o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if (o > 0) hasPos = 1;
        if (o < 0) hasNeg = 1;
    }
    return !(hasPos && hasNeg);
}

// colinear == 0, left > 0, right < 0
ld orient(pt a, pt b, pt c) {return cross(b-a, c-a);} 

// Devuelve el doble del area formada por tres puntos de un triangulo. Positivo cuando a -> b -> c es un giro a la izquierda.
int64_t area_signed_2x(const pt &a, const pt &b, const pt &c) {
    return cross(b - a, c - a);
}

ld distance_to_line(const pt &p, const pt &a, const pt &b) {
    assert(a != b);
    return ld(abs(area_signed_2x(p, a, b))) / (a - b).dist();
}

int64_t manhattan_dist(const pt &a, const pt &b) {
    return (int64_t) abs(a.x - b.x) + abs(a.y - b.y);
}

int64_t infinity_norm_dist(const pt &a, const pt &b) {
    return max(abs(a.x - b.x), abs(a.y - b.y));
}

// Ordenar en orden creciente de y, deshaciendo los empates en orden creciente de x.
bool yx_compare(const pt &a, const pt &b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}
