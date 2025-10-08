
# string


- `aho corasick.cpp`: Aho-Corasick estandar para buscar multiples patrones en un texto y contar ocurrencias.
- `ahobit.cpp`: version basada en bitsets para consultas rapidas de ocurrencias/posiciones (cuando la longitud es limitada).
- `dynamic aho corasick.cpp`: Aho-Corasick dinamico (merge binario de automatas) para inserciones online.
- `hash table.cpp`: esquema simple de prefijos para contar ocurrencias de un patron fijo por rango.
- `hashing-2D-64.cpp`: hashing 2D para matrices/plantillas (64-bit / mod optimizado).
- `hashing-64.cpp`: implementacion de hashing con modulo 2^61-1 (64-bit) y utilidades.
- `hashing.cpp`: rolling hash modular (varias bases/mods) y helpers.
- `HuffmanCoding.cpp`: ejemplo de codificacion Huffman (frecuencias y codigos binarios).
- `Kmp.cpp`: implementacion de KMP (prefix function) para buscar un patron en O(n + m).
- `Manacher.cpp`: Manacher y utilidades para palindromos (palindromic tree helpers incluidos en otros archivos).
- `Min-Max-SuffixCyclic.cpp`: funciones para minimo/maximo sufijo y shift ciclico (Duval / Lyndon / minimum expression).
- `palindrome range.cpp`: DP para contar palindromos por rangos y/o consultas offline.
- `paltree.cpp`: palindromic tree (Eertree) para contar palindromos distintos y frecuencias.
- `rabin karp.cpp`: implementacion de Rabin-Karp (hashing de patrones, busqueda por rolling-hash).
- `Splitear.cpp`: utilidades para split/parse y limpieza de strings (regex helpers).
- `SThash.cpp`: segment-tree con hashing para queries de substring dinamicas (updates + queries).
- `Suffix Array 1.cpp`: suffix array + Kasai LCP y funciones para buscar substrings y LCS.
- `suffixAutomaton popback.cpp`: suffix automaton con soporte pop_back (dinamico).
- `suffixAutomaton.cpp`: implementacion estandar de suffix automaton y utilidades (conteo, LCS, substr distrib).
- `suffixAutomaton1.cpp`: variante/optimizada de suffix automaton.
- `trie.cpp`: trie basico con conteos por prefijo y kth-word.
- `Z.cpp`: Z-function y helpers para coincidencias y periodos.


Notas rapidas:

- Para multiples patrones en textos largos usa `aho corasick.cpp` o `dynamic aho corasick.cpp` si necesitas insertar patrones online.
- Para busquedas de un patron usa `Kmp.cpp` o `rabin karp.cpp` (KMP es determinista, Rabin-Karp usa hashes).
- Para queries dinamicas sobre substrings (updates) usa `SThash.cpp` o estructuras basadas en segment tree + hashing.
- Para problemas sobre palindromos usa `Manacher.cpp` y `paltree.cpp` segun si necesitas palindromos maximos o todas las ocurrencias/distintas.
- Para problemas de sufijos y substrings avanzados usa `Suffix Array 1.cpp` o `suffixAutomaton.cpp` segun memoria/funcionalidad requerida.

