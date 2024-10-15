__builtin_popcount(x);  // Cuenta el numero de bits '1' en la representacion binaria de x.
__builtin_parity(x);    // Devuelve 1 si el numero de bits '1' en la representacion binaria de x es impar, 0 si es par.
__builtin_clz(x);       // Cuenta el numero de bits en '0' a la izquierda, desde el bit mas significativo hasta el primer '1'.
__builtin_ctz(x);       // Cuenta el numero de bits en '0' a la derecha, desde el bit menos significativo hasta el primer '1'.
__builtin_ffs(x);       // Encuentra la posicion del primer bit en '1' (contando desde 1, desde el bit menos significativo).
__lg(x);                // Devuelve el logaritmo en base 2
n & ~(1 << (x - 1));    // Apaga el m-esimo bit de n (bit 1 si m=1 es el menos significativo), Si m=1, apaga el bit menos significativo.
x &(-x);                // Aisla el bit menos significativo en '1' de x (devuelve el bit mas bajo en '1' de x).
~x & (x + 1);           // Aisla el bit menos significativo en '0' de x.
x | (x + 1);            // Enciende el bit menos significativo en '0' de x.
x &(x - 1);             // Apaga el bit menos significativo en '1' de x.
-~n;                    // Suma 1 a n. 
~- n;                   // Resta 1 a n.
x && (!(x & (x - 1)));  // Comprueba si x es una potencia de 2. 

#define forn(i, n) for (int i = 0; i < n; ++i)
#define forne(i, n) for (int i = 0; i <= n; ++i)
#define rforn(i, n) for (int i = n-1; i >= 0; --i)
#define forab(i, a, b) for (int i = a; i < b; ++i)
#define forabe(i, a, b) for (int i = a; i <= b; ++i)
#define form(i, n, m, x) for (int i = n; i < m; i += x)
#define rform(i, n, m, x) for (int i = n; i >= m; i -= x)

//Rotar una matriz 90 grados
int n;
vector<vector<int>> rotar(vector<vector<int>> &a) {
  vector<vector<int>> v(n, vi(n));
  forn(i,n) forn(j, n)
    v[i][j] = a[n - 1 - j][i];
  return v;
}