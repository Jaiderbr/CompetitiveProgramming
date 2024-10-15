// Requiere struct pt
struct line {
    pt v; ld c;

    //vector v and offset c
    line(pt v, ld c) : v(v), c(c) {}
    //ax+by=c
    line(ld a, ld b, ld c) : v({b, -a}), c(c) {}
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
    // - these work with ld = int

    ld side(pt p) {return cross(v, p)-c;}
    ld dist(pt p) {return abs(side(p)) / abs(v);}
    ld sqDist(pt p) {return side(p) * side(p) / (ld)(v.norm());}
    line perpThrough(pt p) {return {p, p + perp(v)};}

    //Para ordenar pts sobre la linea
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }

    line translate(pt t) {return {v, c + cross(v, t)};}
    // - these require ld = double
    line shiftLeft(double dist) {return {v, c + dist*abs(v)};}
    pt proj(pt p) {return p - (perp(v) * side(p)) * (1.0/(v.norm()));}
    pt refl(pt p) {return p - (perp(v) * 2 * side(p)) * (1.0/(v.norm()));}
};

bool inter(line l1, line l2, pt &out) {
    ld d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) * (1.0 / d); // requires floating-point coordinates
    return true;
}

line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    ld sign = interior ? 1 : -1;
    return {l2.v * (1.0 / abs(l2.v)) + l1.v * (1.0 / abs(l1.v)) * sign, l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}
