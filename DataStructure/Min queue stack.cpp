// para max negar...
template<class T> struct Stack {
    stack<pair<T, T>> s;

    void push(T x) {
        if (!sz(s)) s.push({ x, x });
        else s.emplace(x, min(s.top().second, x));
    }
    T top() { return s.top().first; }
    T pop() {
        T ans = s.top().first;
        s.pop();
        return ans;
    }
    int size() { return sz(s); }
    T min() { return s.top().second; }
};