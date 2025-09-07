/*
input
1 2
ab
6 4
abba
baab
abba
baab
abba
baab

output
ab..
..ab
ab..
..ab
ab..
..ab
*/


int n, m; cin >> n >> m;
vector<string> a(n);

forn(i, n) cin >> a[i];
Hash2D ha(a);

int Ha_full = ha.get(0, 0, n - 1, m - 1);

int nn, mm; cin >> nn >> mm;
vector<string> b(nn);
forn(i, nn) cin >> b[i];
Hash2D hb(b);



auto check = [&](int x, int y) {
    int x1 = x;
    int y1 = y;
    int x2 = x + n - 1;
    int y2 = y + m - 1;

    return hb.get(x1, y1, x2, y2) == Ha_full;
    };


vector<string> ans(nn, string(mm, '.'));
vector<vector<int>> vis(nn + 2, vector<int>(mm + 2, 0));
auto paint = [&](int x, int y) {
    int X = x + 1;
    int Y = y + 1;
    vis[X][Y] += 1;
    vis[X + n][Y] -= 1;
    vis[X][Y + m] -= 1;
    vis[X + n][Y + m] += 1;
    };

forn(i, nn - n + 1) {
    forn(j, mm - m + 1) {
        if (a[0][0] != b[i][j]) continue;
        if (check(i, j)) {
            paint(i, j);
        }
    }
}

forne(i, 1, nn + 1) {
    forne(j, 1, mm + 1) {
        vis[i][j] += vis[i][j - 1];
    }
}

forne(i, 1, nn + 1) {
    forne(j, 1, mm + 1) {
        vis[i][j] += vis[i - 1][j];
    }
}


forn(i, nn) {
    forn(j, mm) {
        if (vis[i + 1][j + 1]) cout << b[i][j];
        else cout << '.';
    }
    cout << endl;
}