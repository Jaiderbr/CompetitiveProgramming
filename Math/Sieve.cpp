const int MAX = int(1e6);
bitset<MAX + 5> bs;
vector<int> prime;

void sieve() {
    bs.set();
    bs[0] = bs[1] = 0;
    for (int i = 2; i <= MAX; i++) {
        if (bs[i]) {
            prime.pb(i);
            for (int j = i * i; j <= MAX; j += i) {
                bs[j] = 0;
            }
        }
    }
}