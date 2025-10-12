//__builtin_popcount(x);  -> Cuenta el numero de bits '1' en la representacion binaria de x.
//__builtin_parity(x);    -> Devuelve 1 si el numero de bits '1' en la representacion binaria de x es impar, 0 si es par.
//__builtin_clz(x);       -> Cuenta el numero de bits en '0' a la izquierda, desde el bit mas significativo hasta el primer '1'.
//__builtin_ctz(x);       -> Cuenta el numero de bits en '0' a la derecha, desde el bit menos significativo hasta el primer '1'.
//__builtin_ffs(x);       -> Encuentra la posicion del primer bit en '1' (contando desde 1, desde el bit menos significativo).
//__lg(x);                -> Devuelve el logaritmo en base 2
//__builtin_bswap32(x);   -> Intercambia los bytes de un entero de 32 bits.
//__builtin_bswap64(x);   -> Intercambia los bytes de un entero de 64 bits.
// x ^ (1 << (x & -x));   -> Invierte el bit menos significativo en '1' de x.
//n & ~(1 << (x - 1));    -> Apaga el m-esimo bit de n (bit 1 si m=1 es el menos significativo), Si m=1, apaga el bit menos significativo.
//-~n;                    -> Suma 1 a n.
//~- n;                   -> Resta 1 a n.
//x && (!(x & (x - 1)));  -> Comprueba si x es una potencia de 2.
// x & (1<<i)             -> Verifica si el i-esimo bit esta encendido
// x = x | (1<<i)         -> Enciende el i-esimo bit
// x = x & ~(1<<i)        -> Apaga el i-esimo bit
// x = x ^ (1<<i)         -> Invierte el i-esimo bit
// x = ~x                 -> Invierte todos los bits
// x & -x                 -> Devuelve el bit encendido mas a la derecha (potencia de 2, no el indice)
// ~x & (x+1)             -> Devuelve el bit apagado mas a la derecha (potencia de 2, no el indice)
// x = x | (x+1)          -> Enciende el bit apagado mas a la derecha
// x = x & (x-1)          -> Apaga el bit encendido mas a la derecha
// x = x & ~y             -> Apaga en x los bits encendidos de y

// elementos unicos 
sort(all(nums));
nums.resize(unique(all(nums)) - nums.begin());

//Rotar una matriz 90 grados
vector<vector<int>> rotar(vector<vector<int>>& a) {
    int n = sz(a), m = sz(a[0]);
    vector<vector<int>> v(m, vector<int>(n));
    forn(i, n) {
        forn(j, m) {
            v[j][n - 1 - i] = a[i][j];
        }
    }
    return v;
}

//1234567891011121314151617... what is the digit at position n?
char digit_at_pos(int n) {
    n--; // 0 index
    int len = 9, mm = 1;
    forne(i, 1, 32) { // change 32 to 64 if needed
        if (n < len) {
            int num = n / i + mm, pos = n % i;
            return to_string(num)[pos];
        }
        n -= len, mm *= 10, len = 9 * mm * (i + 1);
    }
}

// sum of even or odd numbers from l to r
auto eve = [&](int l, int r) { return ((r / 2) * ((r / 2) + 1)) - (((l - 1) / 2) * (((l - 1) / 2) + 1));};
auto odd = [&](int l, int r) { return (r * (r + 1) / 2) - ((l - 1) * ((l - 1) + 1) / 2) - eve(l, r); };

// > need
auto upper_bound = [&](int need) ->int {
    int l = -1, r = n;
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (nums[mid] <= need) l = mid;
        else r = mid;
    }
    return l;
    };
// >= need
auto lower_bound = [&](int need) ->int {
    int l = -1, r = n;
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (nums[mid] < need) l = mid;
        else r = mid;
    }
    return r;
    };
// == need
auto search = [&](int need) ->bool {
    int l = -1, r = n;
    while (r - l > 1) {
        int mid = l + (r - l) / 2;
        if (nums[mid] < need) l = mid;
        else r = mid;
    }
    return nums[r] == need;
    };

// xor sum from 0 to x
int xorsum(int x) {
    if (x % 4 == 0) return x;
    else if (x % 4 == 2) return x + 1;
    else if (x % 4 == 1) return 1;
    else return 0;
};

/* resultado de & en el rango [l, r] */
int rangeAND(int l, int r) {
    int ans = 0;
    for (int i = 63 - 1; i >= 0; i--) {
        if ((l & (1ll << i)) != (r & (1ll << i))) break;
        ans |= (l & (1ll << i));
    }
    return ans;
}
