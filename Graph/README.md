# graph

- `ArtiBridges.cpp`: articulaciones y puentes en un grafo (tarjan).
- `Bellman Ford.cpp`: camino minimo con aristas negativas (Bellman-Ford).
- `Biconnected Components.cpp`: componentes biconexas y articulaciones.
- `bipartite Graph.cpp`: checks y algoritmos para grafos bipartitos.
- `cycle len.cpp`: deteccion y longitud de ciclos.
- `Dijkstra.cpp`: algoritmo Dijkstra para shortest paths no-negativos.
- `Floyd Warshall.cpp`: all-pairs shortest paths (APSP).
- `hld.cpp`: heavy-light decomposition para queries en arboles.
- `Kosaraju.cpp`: orden topologica y componentes fuertemente conectadas (SCC).
- `Kruskal.cpp`: MST via Kruskal.
- `LCA Binary Lifting.cpp`: LCA con binary lifting.
- `LCA.cpp`: otra implementacion de LCA.
- `nx-ny-4.cpp`, `nx-ny-8.cpp`: traversales en cuadrilla 4/8 direcciones.
- `Prim.cpp`: Prim para MST.
- `Tarjan.cpp`: algoritmo de Tarjan para SCC o bridges.
- `Topo Sort BFS.cpp`, `Topo Sort DFS.cpp`: orden topologico via BFS (Kahn) y DFS.
- `Two Sat.cpp`: 2-SAT via SCC.

Notas rapidas:

- Para shortest path con pesos no-negativos usar Dijkstra.
- Para MST usa Kruskal o Prim segun el caso.
- Para queries en arboles considera `hld.cpp` o `LCA`.
