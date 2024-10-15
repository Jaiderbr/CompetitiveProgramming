// Requiere pt y line
enum {IN, OUT, ON};
struct polygon {

    vector<pt> p;
    polygon(int64_t n) : p(n) {}
    int64_t top = -1, bottom = -1;

    ld area(bool s = 0) {
        ld ans = 0;
        for (int i = 0, n = p.size(); i < n; i++) ans += cross(p[i], p[(i+1)%n]);
        ans /= 2;
        return s ? ans : abs(ans);
    }

    double perimeter() {
        ld per = 0;
        for(int i = 0, n = p.size(); i < n; i++) per += abs(p[i] - p[(i+1)%n]);
        return per;
    }

    bool above(pt a, pt p) { return p.y >= a.y; }

    bool crosses_ray(pt a, pt p, pt q) { // pq crosses ray from a
        return (above(a, q)-above(a, p)) * orient(a, p, q) > 0;
    }

    bool inDisk(pt a, pt b, pt p) {return dot(a-p, b-p) <= 0;}
    bool onSegment(pt a, pt b, pt p){return !orient(a, b, p) && inDisk(a,b,p);}

    int64_t in_polygon(pt a) {
        int64_t crosses = 0;
        for(int i = 0, n = p.size(); i < n; i++) {
            if(onSegment(p[i], p[(i+1)%n], a)) return ON; //sobre el borde
            crosses += crosses_ray(a, p[i], p[(i+1)%n]);
        }
        return (crosses & 1 ? IN : OUT); 
    }

    void normalize() { /// polygon is CCW
        bottom = min_element(all(p)) - p.begin();
        vector<pt> tmp(p.begin() + bottom, p.end());
        tmp.insert(tmp.end(), p.begin(), p.begin() + bottom);
        p.swap(tmp); bottom = 0;
        top = max_element(all(p)) - p.begin();
    }

    int64_t in_convex(pt a) {
        assert(bottom == 0 && top != -1);
        if(a < p[0] || p[top] < a) return OUT;
        ld orientation = orient(p[0], p[top], a);
        if(!orientation) {
            if(a == p[0] || a == p[top]) return ON;
            return top == 1 || top + 1 == p.size() ? ON : IN;
        } else if (orientation < 0) {
            auto it = lower_bound(p.begin() + 1, p.begin() + top, a);
            ld d = orient(*prev(it), a, *it);
            return d < 0 ? IN : (d > 0 ? OUT: ON);
        } else {
            auto it = upper_bound(p.rbegin(), p.rend() - top - 1, a);
            ld d = orient(*it, a, it == p.rbegin() ? p[0] : *prev(it));
            return d < 0 ? IN : (d > 0 ? OUT: ON);
        }
    }
    polygon cut(pt a, pt b) { // cuts polygon on line ab
        line l(a, b);
        polygon new_polygon(0);
        for(int i = 0, n = p.size(); i < n; ++i) {
            pt c = p[i], d = p[(i+1)%n];
            ld abc = cross(b-a, c-a), abd = cross(b-a, d-a);
            if(abc >= 0) new_polygon.p.push_back(c);
            if(abc * abd < 0) {
                pt out; inter(l, line(c, d), out);
                new_polygon.p.push_back(out);
            }
        }
        return new_polygon;
    }

    void convex_hull() {
        sort(all(p));
        vector<pt> ch;
        ch.reserve(p.size()+1);
        for(int it = 0; it < 2; it++) {
            int64_t start = ch.size();
            for(auto &a : p) {
                // if colineal are needed, use < and remove repeated points
                while(ch.size() >= start+2 && orient(ch[ch.size()-2], ch.back(), a) <= 0)
                    ch.pop_back();
                ch.push_back(a);
            }
            ch.pop_back();
            reverse(p.begin(), p.end());
        }
        if(ch.size() == 2 && ch[0] == ch[1]) ch.pop_back();
        // if colineal are needed, use this
		//if(sz(ch) > sz(p)) ch.resize(p.size());
        p.swap(ch);
    }

    vector<pair<int64_t, int64_t>> antipodal() {
        vector<pair<int64_t, int64_t>> ans;
        int64_t n = p.size();
        if(n == 2) ans.push_back({0, 1});
        if(n < 3) return ans;
        auto nxt = [&](int x) { return (x+1 == n ? 0 : x+1); };
        auto area2 = [&](pt a, pt b, pt c) { return cross(b-a, c-a); };
        int64_t _b = 0;
        while(abs(area2(p[n - 1], p[0], p[nxt(_b)])) > abs(area2(p[n - 1], p[0], p[_b]))) ++_b;
        for(int b = _b, a = 0; b != 0 && a <= _b; ++a) {
            ans.push_back({a, b});
            while (abs(area2(p[a], p[nxt(a)], p[nxt(b)])) > abs(area2(p[a], p[nxt(a)], p[b]))) {
                b = nxt(b);
                if(a != _b || b != 0) ans.push_back({ a, b });
                else return ans;
            }
            if(abs(area2(p[a], p[nxt(a)], p[nxt(b)])) == abs(area2(p[a], p[nxt(a)], p[b]))) {
                if(a != _b || b != n-1) ans.push_back({ a, nxt(b) });
                else ans.push_back({ nxt(a), b });
            }
        }
        return ans;
    }

    pt centroid() {
        pt c{0, 0};
        ld scale = 6. * area(true);
        for(int i = 0, n = p.size(); i < n; ++i) {
            int64_t j = (i+1 == n ? 0 : i+1);
            c = c + (p[i] + p[j]) * cross(p[i], p[j]);
        }
        return c * (1.0 / scale);
    }
    
    int64_t pick() {
        int64_t boundary = 0;
        for(int i = 0, n = p.size(); i < n; i++) {
            int64_t j = (i+1 == n ? 0 : i+1);
            boundary += __gcd((int64_t)abs(p[i].x - p[j].x), (int64_t)abs(p[i].y - p[j].y));
        }
        return area() + 1 - boundary/2;
    }

    pt& operator[] (int64_t i){ return p[i]; }
};

ld areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b-a, c-a)) / 2.0;
}
