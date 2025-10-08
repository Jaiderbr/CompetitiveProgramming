# DataStructure


- `bint.cpp`: implementacion de big integer o utilidades relacionadas con enteros grandes (si aplica). Revisar el archivo para detalles.
- `Coo Compress.cpp`: compresion de coordenadas (mapping de valores a indices compactos). Usual para coordenadas discretas.
- `Dsu.cpp`: Union-Find / Disjoint Set Union con union por rango y path compression.
- `Eval.cpp`: evaluador de expresiones o utilidades para evaluar funciones (leer el archivo para el formato esperado).
- `Fenwick Tree.cpp`: BIT / Fenwick Tree para sumas/range queries en O(log n).
- `indexed set.cpp`: contenedor ordenado con orden por indice (basado en policy-based data structures / ordered_set).
- `inversion count.cpp`: conteo de inversiones en un array (merge sort o fenwick).
- `Min queue deque.cpp`: cola minima usando deque (monotonic queue).
- `Min queue stack.cpp`: cola minima implementada usando dos pilas.
- `Mint.cpp`: estructura para aritmetica modular (mint) con operaciones + - * / y pow/inv.
- `Mo's.cpp`: algoritmo Mo para queries offline sobre arreglos (reordenamiento de queries y add/remove).
- `Segment Tree ( ).cpp`: arbol de segmentos para parentesis.
- `Segment Tree 2D.cpp`: arbol de segmentos 2D (queries en rango 2D).
- `Segment Tree Iterative.cpp`: version iterativa de arbol de segmentos (bottom-up).
- `Segment Tree Lazy.cpp`: arbol de segmentos con lazy propagation para updates por rango.
- `Segment Tree.cpp`: otra implementacion de arbol de segmentos (revisar diferencias: iterativo, recursivo, con lazy). 
- `SqrtBlocks.cpp`: tecnica sqrt-decomposition para consultas y actualizaciones.
- `STable.cpp`: Sparse Table para RMQ estatico y consultas O(1).
- `WaveletTree.cpp`: Wavelet Tree para consultas de rango sobre frecuencias y kth.

Notas de uso


- Para queries offline usa `Mo's.cpp` cuando las actualizaciones son pocas o nulas.
- Usa `Fenwick Tree.cpp` para sumas y point-updates; `Segment Tree Lazy.cpp` para updates por rango y queries por rango.
- `indexed set.cpp` requiere policy-based data structures (g++), incluye los headers de PBDS.
- `WaveletTree.cpp` es util para queries kth y contar elementos en rangos; revisa complejidad y memoria antes de usar.
