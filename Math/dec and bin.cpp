string dec_to_bin(int64_t n) {
    bitset<32> bs(n);
    string s = bs.to_string();
    return s;
}
int64_t bin_to_dec(string s) {
    bitset<32> bs(s);
    int64_t n = bs.to_ullong();
    return n;
}

string dec_to_bin(int64_t n) {
    string s;
    while (n) {
        if (n & 1) s.pb('1');
        else s.pb('0');
        n >>= 1;
    }
    reverse(all(s));
    return s;
}
int64_t bin_to_dec(string s) {
    int64_t res = 0;
    for (auto&& i : s) {
        res <<= 1;
        res += i - '0';
    }
    return res;
}