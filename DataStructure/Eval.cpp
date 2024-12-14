template <typename T> struct eval {
    string s;
    int n;
    eval(string s) : s(s), n(sz(s)) {}

    stack <T> nums;
    stack <char> oper;

    int order(char op) {
        if (op < 0) return 3;
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    bool is_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

    bool is_unary(char c) { return c == '+' || c == '-'; }

    T apply(T a, T b, char op) {
        if (op == '+') return a + b;
        if (op == '-') return a - b;
        if (op == '*') return a * b;
        if (op == '/') return a / b;
        return 0;
    }

    T go() {
        int op = oper.top(); oper.pop();
        if (op < 0) {
            T v = nums.top(); nums.pop();
            return apply(0, v, -op);
        }
        T v2 = nums.top(); nums.pop();
        T v1 = nums.top(); nums.pop();
        return apply(v1, v2, op);
    }

    T get() {
        bool ok = 1;
        forn(i, n) {
            if (s[i] == ' ') continue;
            if (s[i] == '(') oper.push('('), ok = 1;
            else if (s[i] == ')') {
                while (oper.top() != '(') nums.push(go());
                oper.pop(), ok = 0;
            }
            else if (is_op(s[i])) {
                char alt = s[i];
                if (ok && is_unary(alt)) alt = -alt;
                while (sz(oper) && ((alt >= 0 && order(oper.top()) >= order(alt)) || (alt < 0 && order(oper.top()) > order(alt)))) nums.push(go());
                oper.push(alt), ok = 1;
            }

            // else {
            //     int val = 0;
            //     while (i < n && isalnum(s[i])) val = val * 10 + s[i++] - '0';
            //     --i;
            //     nums.push(val), ok = 0;
            // }

            else {
                T val = 0;
                int dec = -1;
                while (i < n && (isdigit(s[i]) || s[i] == '.')) {
                    if (s[i] == '.') dec = 0;
                    else {
                        val = val * 10 + (s[i] - '0');
                        if (dec >= 0) ++dec;
                    }
                    ++i;
                }
                if (dec > 0) val /= pow(10, dec);
                --i;
                nums.push(val);
                ok = 0;
            }
        }

        while (sz(oper)) nums.push(go());

        return nums.top();
    }

};
