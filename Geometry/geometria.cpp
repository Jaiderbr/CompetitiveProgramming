//Tomado y adaptado de: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria.cpp

typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))
bool eq(ld a, ld b) { return abs(a - b) <= eps; }

// Punto: (x, y)
struct pt {
    ld x, y;
    pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}

    bool operator < (const pt p) const {
        if (!eq(x, p.x)) return x < p.x;
        if (!eq(y, p.y)) return y < p.y;
        return 0;
    }
    bool operator == (const pt p) const { return eq(x, p.x) and eq(y, p.y); }
    pt operator + (const pt p) const { return pt(x + p.x, y + p.y); }
    pt operator - (const pt p) const { return pt(x - p.x, y - p.y); }
    pt operator * (const ld c) const { return pt(x * c, y * c); }
    pt operator / (const ld c) const { return pt(x / c, y / c); }
    ld operator * (const pt p) const { return x * p.x + y * p.y; }
    ld operator ^ (const pt p) const { return x * p.y - y * p.x; }
    friend istream& operator >> (istream& in, pt& p) { return in >> p.x >> p.y; }
    friend ostream& operator << (ostream& out, const pt& p) { return out << p.x << ' ' << p.y; }
};

ld DEG_TO_RAD(ld n) { return n * pi / 180.0; }
ld RAD_TO_DEG(ld n) { return n * 180.0 / pi; }


// Recta: (p(x,y), q(x,y))
struct line {
    pt p, q;
    line() {}
    line(pt p_, pt q_) : p(p_), q(q_) {}
    friend istream& operator >> (istream& in, line& r) {
        return in >> r.p >> r.q;
    }
};


// distancia
ld dist(pt p, pt q) {
    return hypot(p.y - q.y, p.x - q.x);
}

ld dist2(pt p, pt q) { // cuadrado de la distancia
    return sq(p.x - q.x) + sq(p.y - q.y);
}

ld norm(pt v) { // norma euclidiana del vector
    return dist(pt(0, 0), v);
}

ld angle(pt v) { // angulo del vector con el eje x
    ld ang = atan2(v.y, v.x);
    if (ang < 0) ang += 2 * pi;
    return ang;
}

ld sarea(pt p, pt q, pt r) { // area con signo
    return ((q - p) ^ (r - q)) / 2;
}

bool col(pt p, pt q, pt r) { // si p, q y r son colineales
    return eq(sarea(p, q, r), 0);
}

bool ccw(pt p, pt q, pt r) { // si p, q, r estan en sentido antihorario
    return sarea(p, q, r) > eps;
}

pt rotate(pt p, ld th) { // rota el punto th radianes
    return pt(p.x * cos(th) - p.y * sin(th), p.x * sin(th) + p.y * cos(th));
}

pt rotate90(pt p) { // rota 90 grados
    return pt(-p.y, p.x);
}

// RECTA

bool isvert(line r) { // si r es vertical
    return eq(r.p.x, r.q.x);
}

bool isinseg(pt p, line r) { // si p pertenece al segmento de r
    pt a = r.p - p, b = r.q - p;
    return eq((a ^ b), 0) and (a * b) < eps;
}

ld get_t(pt v, line r) { // retorna t tal que t*v pertenece a la recta r
    return (r.p ^ r.q) / ((r.p - r.q) ^ v);
}

pt proj(pt p, line r) { // proyeccion del punto p en la recta r
    if (r.p == r.q) return r.p;
    r.q = r.q - r.p; p = p - r.p;
    pt proj = r.q * ((p * r.q) / (r.q * r.q));
    return proj + r.p;
}

pt inter(line r, line s) { // interseccion de r con s
    if (eq((r.p - r.q) ^ (s.p - s.q), 0)) return pt(DINF, DINF);
    r.q = r.q - r.p, s.p = s.p - r.p, s.q = s.q - r.p;
    return r.q * get_t(r.q, s) + r.p;
}

bool interseg(line r, line s) { // si el segmento de r intersecta el segmento de s
    if (isinseg(r.p, s) or isinseg(r.q, s)
        or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

    return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
        ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

ld disttoline(pt p, line r) { // distancia del punto a la recta
    return 2 * abs(sarea(p, r.p, r.q)) / dist(r.p, r.q);
}

ld disttoseg(pt p, line r) { // distancia del punto al segmento
    if ((r.q - r.p) * (p - r.p) < 0) return dist(r.p, p);
    if ((r.p - r.q) * (p - r.q) < 0) return dist(r.q, p);
    return disttoline(p, r);
}

ld distseg(line a, line b) { // distancia entre segmentos
    if (interseg(a, b)) return 0;

    ld ret = DINF;
    ret = min(ret, disttoseg(a.p, b));
    ret = min(ret, disttoseg(a.q, b));
    ret = min(ret, disttoseg(b.p, a));
    ret = min(ret, disttoseg(b.q, a));

    return ret;
}