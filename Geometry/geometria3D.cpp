//Tomado y adaptado de: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria3d.cpp

typedef double ld;
const ld DINF = 1e18;
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) { return abs(a - b) <= eps; }

struct pt { // punto
    ld x, y, z;
    pt(ld x_ = 0, ld y_ = 0, ld z_ = 0) : x(x_), y(y_), z(z_) {}
    bool operator < (const pt p) const {
        if (!eq(x, p.x)) return x < p.x;
        if (!eq(y, p.y)) return y < p.y;
        if (!eq(z, p.z)) return z < p.z;
        return 0;
    }
    bool operator == (const pt p) const {
        return eq(x, p.x) and eq(y, p.y) and eq(z, p.z);
    }
    pt operator + (const pt p) const { return pt(x + p.x, y + p.y, z + p.z); }
    pt operator - (const pt p) const { return pt(x - p.x, y - p.y, z - p.z); }
    pt operator * (const ld c) const { return pt(x * c, y * c, z * c); }
    pt operator / (const ld c) const { return pt(x / c, y / c, z / c); }
    ld operator * (const pt p) const { return x * p.x + y * p.y + z * p.z; }
    pt operator ^ (const pt p) const { return pt(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
    friend istream& operator >> (istream& in, pt& p) {
        return in >> p.x >> p.y >> p.z;
    }
};

ld DEG_TO_RAD(ld n) { return n * acos(-1) / 180.0; }
ld RAD_TO_DEG(ld n) { return n * 180.0 / acos(-1); }


struct line { // recta
    pt p, q;
    line() {}
    line(pt p_, pt q_) : p(p_), q(q_) {}
    friend istream& operator >> (istream& in, line& r) {
        return in >> r.p >> r.q;
    }
};

struct plane { // plano
    array<pt, 3> p;  // puntos que definen el plano
    array<ld, 4> eq; // ecuacion del plano
    plane() {}
    plane(pt p_, pt q_, pt r_) : p({ p_, q_, r_ }) { build(); }

    friend istream& operator >> (istream& in, plane& P) {
        return in >> P.p[0] >> P.p[1] >> P.p[2];
        P.build();
    }
    void build() {
        pt dir = (p[1] - p[0]) ^ (p[2] - p[0]);
        eq = { dir.x, dir.y, dir.z, dir * p[0] * (-1) };
    }
};

// convierte de coordenadas polares a cartesianas
// (angulos deben estar en radianes)
// phi es el angulo con el eje z (arriba) theta es el angulo de rotacion alrededor de z
pt convert(ld rho, ld th, ld phi) {
    return pt(sin(phi) * cos(th), sin(phi) * sin(th), cos(phi)) * rho;
}

// proyeccion del punto p en la recta r
pt proj(pt p, line r) {
    if (r.p == r.q) return r.p;
    r.q = r.q - r.p; p = p - r.p;
    pt proj = r.q * ((p * r.q) / (r.q * r.q));
    return proj + r.p;
}

// proyeccion del punto p en el plano P
pt proj(pt p, plane P) {
    p = p - P.p[0], P.p[1] = P.p[1] - P.p[0], P.p[2] = P.p[2] - P.p[0];
    pt norm = P.p[1] ^ P.p[2];
    pt proj = p - (norm * (norm * p) / (norm * norm));
    return proj + P.p[0];
}

// distancia
ld dist(pt a, pt b) {
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y) + sq(a.z - b.z));
}

// distancia punto recta
ld distline(pt p, line r) {
    return dist(p, proj(p, r));
}

// distancia de punto a segmento
ld distseg(pt p, line r) {
    if ((r.q - r.p) * (p - r.p) < 0) return dist(r.p, p);
    if ((r.p - r.q) * (p - r.q) < 0) return dist(r.q, p);
    return distline(p, r);
}

// distancia de punto a plano con signo
ld sdist(pt p, plane P) {
    return P.eq[0] * p.x + P.eq[1] * p.y + P.eq[2] * p.z + P.eq[3];
}

// distancia de punto a plano
ld distplane(pt p, plane P) {
    return abs(sdist(p, P));
}

// si punto pertenece a recta
bool isinseg(pt p, line r) {
    return eq(distseg(p, r), 0);
}

// si punto pertenece al triangulo definido por P.p
bool isinpol(pt p, vector<pt> v) {
    assert(v.size() >= 3);
    pt norm = (v[1] - v[0]) ^ (v[2] - v[1]);
    bool inside = true;
    int sign = -1;
    for (int i = 0; i < v.size(); i++) {
        line r(v[(i + 1) % 3], v[i]);
        if (isinseg(p, r)) return true;

        pt ar = v[(i + 1) % 3] - v[i];
        if (sign == -1) sign = ((ar ^ (p - v[i])) * norm > 0);
        else if (((ar ^ (p - v[i])) * norm > 0) != sign) inside = false;
    }
    return inside;
}

// distancia de punto a poligono
ld distpol(pt p, vector<pt> v) {
    pt p2 = proj(p, plane(v[0], v[1], v[2]));
    if (isinpol(p2, v)) return dist(p, p2);
    ld ret = DINF;
    for (int i = 0; i < v.size(); i++) {
        int j = (i + 1) % v.size();
        ret = min(ret, distseg(p, line(v[i], v[j])));
    }
    return ret;
}

// interseccion de plano y segmento
// BOTH = el segmento esta en el plano
// ONE = uno de los puntos del segmento esta en el plano
// PARAL = segmento paralelo al plano
// CONCOR = segmento concurrente al plano
enum RETCODE { BOTH, ONE, PARAL, CONCOR };
pair<RETCODE, pt> intersect(plane P, line r) {
    ld d1 = sdist(r.p, P);
    ld d2 = sdist(r.q, P);
    if (eq(d1, 0) and eq(d2, 0)) return pair(BOTH, r.p);
    if (eq(d1, 0)) return pair(ONE, r.p);
    if (eq(d2, 0)) return pair(ONE, r.q);
    if ((d1 > 0 and d2 > 0) or (d1 < 0 and d2 < 0)) {
        if (eq(d1 - d2, 0)) return pair(PARAL, pt());
        return pair(CONCOR, pt());
    }
    ld frac = d1 / (d1 - d2);
    pt res = r.p + ((r.q - r.p) * frac);
    return pair(ONE, res);
}

// rota p alrededor del eje u por un angulo a
pt rotate(pt p, pt u, ld a) {
    u = u / dist(u, pt());
    return u * (u * p) + (u ^ p ^ u) * cos(a) + (u ^ p) * sin(a);
}
