/*
You are given n circles numbered from 1 to n. 
Each circle is defined by an integer center (xi,yi) and an integer radius ri.

Then we will ask you q questions. In each question, 
we will give you an integer point (xi,yi),
and you have to find the number of circles that cover this point.
*/

void solve() {
 
    map<pair<int, int>, vector<array<int, 3>>> mp;
    map<pair<int, int>, int> mpans;
 
    int n, q, x, y, r; cin >> n >> q;
 
    forn(i, n) {
        cin >> x >> y >> r;
        mp[{int(x / 10), int(y / 10)}].pb({ x,y,r });
    }
 
    while (q--) {
        cin >> x >> y;
        int gX = int(x / 10), gY = int(y / 10);
        int ans = 0;
        if (!mpans.count({ x,y })) {
            forne(dx, -1, 2) {
                forne(dy, -1, 2) {
                    auto it = mp.find({ gX + dx,  gY + dy });
                    if (it != mp.end()) {
                        each(i, it->s) {
                            int xc = i[0], yc = i[1], rc = i[2];
                            if ((x - xc) * (x - xc) + (y - yc) * (y - yc) <= rc * rc) ans++;
                        }
                    }
                }
            }
            cout << ans << endl;
            mpans[{x, y}] = ans;
        }
        else cout << mpans[{x, y}] << endl;
 
    } 
}
