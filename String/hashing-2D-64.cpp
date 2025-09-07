#define int int64_t
const int MOD = (1ll << 61) - 1;

int mulmod(int a, int b) {
    const static int L = (1ll << 30) - 1, _31 = (1ll << 31) - 1;
    int l1 = a & L, h1 = a >> 30, l2 = b & L, h2 = b >> 30;
    int m = l1 * h2 + l2 * h1, h = h1 * h2;
    int ans = l1 * l2 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & _31) << 30) + 1;
    ans = (ans & MOD) + (ans >> 61), ans = (ans & MOD) + (ans >> 61);
    return ans - 1;
}

int rnd(int l, int r) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(l, r)(rng);
}

struct Hash2D {
    static int P, Q;
    vector<vector<int>> H;
    vector<int> powP, powQ, invP, invQ;
    static int modexp(int a, int e) {
        int r = 1;
        while (e > 0) {
            if (e & 1) r = mulmod(r, a);
            a = mulmod(a, a);
            e >>= 1;
        }
        return r;
    }

    Hash2D(vector<string>& g) {
        int n = sz(g), m = sz(g[0]);
        H.assign(n + 1, vector<int>(m + 1, 0));
        powP.assign(n + 1, 1), powQ.assign(m + 1, 1), invP.assign(n + 1, 1), invQ.assign(m + 1, 1);

        int invBaseP = modexp(P, MOD - 2);
        int invBaseQ = modexp(Q, MOD - 2);
        forne(i, 1, n + 1) {
            powP[i] = mulmod(powP[i - 1], P);
            invP[i] = mulmod(invP[i - 1], invBaseP);
        }
        forne(j, 1, m + 1) {
            powQ[j] = mulmod(powQ[j - 1], Q);
            invQ[j] = mulmod(invQ[j - 1], invBaseQ);
        }

        forne(i, 1, n + 1) {
            forne(j, 1, m + 1) {
                int val = g[i - 1][j - 1];
                H[i][j] = (H[i - 1][j] + H[i][j - 1] - H[i - 1][j - 1] + mulmod(val, mulmod(powP[i], powQ[j]))) % MOD;
                if (H[i][j] < 0) H[i][j] += MOD;
            }
        }
    }

    int raw(int x1, int y1, int x2, int y2) {
        int res = H[x2 + 1][y2 + 1];
        res = (res - H[x1][y2 + 1] - H[x2 + 1][y1] + H[x1][y1]) % MOD;
        if (res < 0) res += MOD;
        return res;
    }

    int get(int x1, int y1, int x2, int y2) {
        int res = raw(x1, y1, x2, y2);
        res = mulmod(res, invP[x1]);
        res = mulmod(res, invQ[y1]);
        return res;
    }

    /*
    (x1 = 0, y1 = 0, x2 = n-1, y2 = m-1)
    get(i, j, i + n - 1, j + m - 1)
    x1,y1   ──────────  x1,y2
    │                   │
    │     submatriz     │
    │                   │
    x2,y1   ──────────  x2,y2
    */
};