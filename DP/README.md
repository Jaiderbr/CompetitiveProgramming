# dynamic programming (dp)

- `Digit dp.cpp`: digit DP que cuenta numeros en [l,r] sin digitos iguales consecutivos.
- `Divide and Conquer dp.cpp`: optimizacion Divide & Conquer para DP de particiones (convex hull trick / opt D&C).
- `Edit Distance.cpp`: edit distance clasica, version con memoria optimizada y reconstruccion de operaciones.
- `groups.cpp`: solucion por bitmask para minimo num de grupos con suma <= Q; incluye variante greedy para pares.
- `Knapsack.cpp`: 0/1 knapsack (DP por capacidad) y variante DP por valor segun limites.
- `LCS.cpp`: implementaciones de LCS (O(n*m), espacio optimizado, Hirschberg y reconstruccion).
- `Lis.cpp`: LIS O(n log n) con reconstruccion y variantes aplicadas a subsecuencias de pares.
- `Money Sums.cpp`: DP booleano que lista todas las sumas posibles con un conjunto de monedas.
- `Shortest Hamiltonian Path.cpp`: DP bitmask para TSP/hamiltonian path (n <= ~18).
- `Subsequences.cpp`: conteo de subsecuencias distintas y DP por longitudes.


Notas rapidas:

- Usar bitmask DP para n pequeno (<=20).
- Para knapsack, elegir DP por valor si la suma de valores es limitada.
- Preferir versiones con espacio optimizado cuando la memoria es limitada.

