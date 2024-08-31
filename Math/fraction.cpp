struct fraction {
    int num, den;

    fraction(int num, int den) :num(num), den(den) {
        check_den();
        simplify();
    }
    void check_den() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }
    void simplify() {
        int mcd = __gcd(abs(num), abs(den));
        num /= mcd;
        den /= mcd;
    }
    pair<int, int> x() { return { num,den }; }

    fraction operator + (const fraction& x) const {
        return fraction(num * x.den + den * x.num, den * x.den);
    }
    fraction operator - (const fraction& x) const {
        return fraction(num * x.den - den * x.num, den * x.den);
    }
    fraction operator * (const fraction& x) const {
        return fraction(num * x.num, den * x.den);
    }
    fraction operator / (const fraction& x) const {
        return fraction(num * x.den, den * x.num);
    }
    friend ostream& operator << (ostream& os, const fraction& x) {
        return os << x.num << " / " << x.den;
    }
};