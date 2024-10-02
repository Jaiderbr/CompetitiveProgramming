    __builtin_popcount(x);  // Cuenta el número de bits '1' en la representación binaria de x.
    __builtin_parity(x);    // Devuelve 1 si el número de bits '1' en la representación binaria de x es impar, 0 si es par.
    __builtin_clz(x);       // Cuenta el número de bits en '0' a la izquierda, desde el bit más significativo hasta el primer '1'.
    __builtin_ctz(x);       // Cuenta el número de bits en '0' a la derecha, desde el bit menos significativo hasta el primer '1'.
    __builtin_ffs(x);       // Encuentra la posición del primer bit en '1' (contando desde 1, desde el bit menos significativo).
    __lg(x);                // Devuelve el logaritmo en base 2
    n & ~(1 << (x - 1));    // Apaga el m-ésimo bit de n (bit 1 si m=1 es el menos significativo), Si m=1, apaga el bit menos significativo.
    x &(-x);                // Aísla el bit menos significativo en '1' de x (devuelve el bit más bajo en '1' de x).
    ~x & (x + 1);           // Aísla el bit menos significativo en '0' de x.
    x | (x + 1);            // Enciende el bit menos significativo en '0' de x.
    x &(x - 1);             // Apaga el bit menos significativo en '1' de x.
    -~n;                    // Suma 1 a n. 
    ~- n;                   // Resta 1 a n.
    x && (!(x & (x - 1)));  // Comprueba si x es una potencia de 2. 

