//[-n to n-1]
template<typename T>
struct offvec {

    vector<T> v;
    int offset;

    offvec(int n = 0, T def = T()) {
        offset = n;
        v = vector<T>(2 * n, def);
    }

    T& operator[](int id) { return v[id + offset]; }
};
