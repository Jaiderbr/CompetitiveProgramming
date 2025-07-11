// Problema: hallar el radio maximo de los circulos externos que rodean
// un circulo interno de radio R, tocandolo y tocandose entre ellos

ld n, R; cin >> n >> R; // n = numero de circulos externos, R = radio circulo interno

ld l = 0, r = 1e9, eps = 1e-8; // inicializa binaria: l minimo, r grande, eps precision

while (r - l > eps) { // mientras el rango sea mayor que la precision

    ld mid = l + (r - l) / 2; // mid = radio candidato circulos externos

    ld sinv = sin(pi / n); // sin(pi/n) = factor trigonometrico para distancia entre centros

    ld d = 2 * (R + mid) * sinv; // d = distancia entre centros de dos circulos externos

    if (d >= 2 * mid) l = mid; // si se tocan o sobra espacio, mid valido, busca mayor
    else r = mid; // si no se tocan, radio muy grande, busca menor
}

cout << fixed << setprecision(7) << l << endl;