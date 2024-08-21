/*
ahobit: used to search for a pattern in a string
    - query(l,r): searches for how many times the pattern is repeated in the range [l,r]
    - numoc: number of occurrences of the pattern in the string
    - a: vector with the positions of the occurrences of the pattern
    - szp: size of the pattern
    - bs: bitset of the characters in the string
    - oc: bitset of the occurrences of the pattern
    - N: maximum size of the string
*/
struct ahobit {
    static constexpr int N = 1e5 + 9;
    bitset<N>bs[26], oc;
    vector<int> a;
    int numoc = 0, szp;
    ahobit(const string& s) {
        for (int i = 0; s[i]; i++) bs[s[i] - 'a'][i] = 1;
    }
    void add(const string& p) {
        numoc = 0; oc.set(); szp = sz(p);
        for (int i = 0; p[i]; i++) oc &= (bs[p[i] - 'a'] >> i);
        numoc = oc.count();
        build();
    }
    void build() {
        int pos = oc._Find_first();
        a.clear(); a.pb(pos);
        pos = oc._Find_next(pos);
        while (pos < N) {
            a.pb(pos);
            pos = oc._Find_next(pos);
        }
    }

    int query(int l, int r) {
        //1-indexed
        if (szp > r - l + 1) return 0;
        return (oc >> (l - 1)).count() - (oc >> (r - szp + 1)).count();
    }
};