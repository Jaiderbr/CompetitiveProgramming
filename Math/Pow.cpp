#define int int64_t
int binpow(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

#define int int64_t
int binpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}


// usar esta pow cuando el modulo puede llegar hasta 1e18 (segura contra overflow)

int mul(int a, int b, int m) {
    int ret = a * b - int((long double)1 / m * a * b + 0.5) * m;
    return ret < 0 ? ret + m : ret;
}

int pow(int x, int y, int m) {
    if (!y) return 1;
    int ans = pow(mul(x, x, m), y / 2, m);
    return y % 2 ? mul(x, ans, m) : ans;
}