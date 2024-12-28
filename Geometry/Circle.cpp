//Requiere pt y line

pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * c.norm() - c * b.norm()) * (1.0 / cross(b,c)/2.0);
}
// (x- x0)^2 + (y-y0)^2
// (x0 + r cos(ang), y0 + r sin(ang))

template <typename ld> int64_t sgn(ld x) {
    return (ld(0) < x) - (x < ld(0));
}

int64_t circleLine(pt o, ld r, line l, pair<pt,pt> &out) {
    ld h2 = r * r - l.sqDist(o);
    if (h2 >= 0) { // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v*sqrt(h2) * (1.0 / abs(l.v)); // vector parallel to l, of
        //length h
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

int64_t circleCircle(pt o1, ld r1, pt o2, ld r2, pair<pt,pt> &out) {
    pt d=o2-o1; ld d2= d.norm();
    if (d2 == 0) {assert(r1 != r2); return 0;} // concentric circles
    ld pd = (d2 + r1 * r1 - r2 * r2)/2; // = |O_1P| * d
    ld h2 = r1 * r1 - pd * pd / d2; // = h^2
    if (h2 >= 0) {
        pt p = o1 + (d * pd)*(1.0 / d2), h = perp(d) * sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

int64_t tangents(pt o1, ld r1, pt o2, ld r2, bool inner, vector<pair<pt,pt>> &out) {
    if (inner) r2 = -r2;
    pt d = o2-o1;
    ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (ld sign : {-1, 1}) {
        pt v = (d * dr + perp(d) * sqrt(h2) * sign) * (1.0 / d2);
        out.push_back({o1 + v * r1, o2 + v * r2});
    }
    return 1 + (h2 > 0);
}
