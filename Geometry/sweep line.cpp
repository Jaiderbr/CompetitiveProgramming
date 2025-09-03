/*
O(nlogn)
Par de puntos cuya distancia es la mas corta
ans = idx de los puntos en el vector de puntos dado
best = la mejor distancia entre dos puntos (la mas corta)
*/

struct P {
    //double para puntos con decimales ej (x , y) -> (1.234, 2.341)
    double x, y;
    int id;

    //int x, y, id; 
};

struct Cx {
    bool operator()(const P& a, const P& b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};
struct Cy {
    bool operator()(const P& a, const P& b) const {
        return a.y < b.y;
    }
};

int n;
vector<P> a, buf;
double best;
pair<int, int> ans = { -1, -1 };

inline void upd(const P& u, const P& v) {
    double dx = u.x - v.x, dy = u.y - v.y;
    double d = sqrt(dx * dx + dy * dy);
    if (d < best) { best = d; ans = { u.id, v.id }; }
}

void rec(int l, int r) {
    if (r - l <= 3) {
        for (int i = l; i < r; i++)
            for (int j = i + 1; j < r; j++)
                upd(a[i], a[j]);
        sort(a.begin() + l, a.begin() + r, Cy());
        return;
    }
    int m = (l + r) >> 1;
    //double para puntos con decimales ej (x , y) -> (1.234, 2.341)
    double midx = a[m].x;
    //int midx = a[m].x;
    rec(l, m);
    rec(m, r);
    merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, buf.begin(), Cy());
    copy(buf.begin(), buf.begin() + (r - l), a.begin() + l);
    int sz = 0;
    for (int i = l; i < r; i++) {
        if (fabs(double(a[i].x) - midx) < best) {
            for (int j = sz - 1, k = 0; j >= 0 && k < 8; --j, ++k) {
                if ((a[i].y - buf[j].y) >= best) break;
                upd(a[i], buf[j]);
            }
            buf[sz++] = a[i];
        }
    }
}

//test con enteros

void test() {
    cin >> n;
    a.resize(n);
    buf.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
    }
    sort(all(a), Cx());
    best = 1e18;
    rec(0, n);
    int i = ans.f, j = ans.s;
    if (i > j) {
        swap(i, j);
    }
    cout << i << ' ' << j << ' ' << fixed << setprecision(6) << best << '\n';
}

//test con decimales

void testd() {
    int n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        a.resize(n);
        buf.resize(n);
        vector<pair< string, string >> tempA;
        for (int i = 0; i < n; i++) {
            string sx, sy; cin >> sx >> sy;
            P p;
            p.x = stod(sx);
            p.y = stod(sy);
            p.id = i;
            a[i] = p;
            tempA.pb({ sx, sy });
        }
        buf.assign(n, {});
        sort(all(a), Cx());
        best = 1e300;
        ans = { 0, 0 };
        rec(0, n);
        int idx1 = ans.f, idx2 = ans.s;
        cout << tempA[idx1].f << ' ' << tempA[idx1].s << ' ' << tempA[idx2].f << ' ' << tempA[idx2].s << endl;
    }


}
