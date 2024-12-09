// para max negar...
template<class T> struct minqueue {
    deque<pair<T, int>> q;

    void push(T x) {
        int ct = 1;
        while (sz(q) and x < q.front().first)
            ct += q.front().second, q.pop_front();
        q.emplace_front(x, ct);
    }
    void pop() {
        if (q.back().second > 1) q.back().second--;
        else q.pop_back();
    }
    T min() { return q.back().first; }
};
