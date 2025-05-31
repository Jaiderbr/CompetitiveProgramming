using lint = __int128;

istream& operator>>(istream &in, lint &x) {
    string s; in >> s;
    x = 0; bool neg = 0; int i = 0;
    if (s[0] == '-') neg = 1, i = 1;
    for (; i < sz(s); i++) x = x * 10 + (s[i] - '0');
    if (neg) x *= -1;
    return in;
}

ostream& operator<<(ostream &out, lint x) {
    if (x == 0) return out << "0";
    if (x < 0) out << '-', x = -x;
    string s;
    while (x) s += '0' + x % 10, x /= 10;
    reverse(all(s));
    return out << s;
}
