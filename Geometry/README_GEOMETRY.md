# Geometry
- Circle.cpp: funciones para circunferencias (centro circunscrito, interseccion recta-circ, interseccion circ-circ, tangentes).
- geometria.cpp: primitivas 2D (pt, line), dist, sarea, ccw, proj, inter, interseg, distseg y transformaciones.
- geometria3D.cpp: primitivas 3D (pt), proyecciones, distancias, intersecciones con planos, rotaciones en 3D.
- GeometriaInt.cpp: version entera (pt con int) con area, inpol, convex_hull, segpoints y operaciones enteras robustas.
- isfigure.cpp: programa que clasifica un cuadrilatero (square, rectangle, rhombus, parallelogram, trapezium, kite, none).
- Polygon.cpp: area, punto en poligono, convex_hull, cortar poligono por recta, interseccion y distancia entre poligonos.
- sweep line.cpp: utilidades de sweep (comparadores y estructuras), detection de intersecciones y algoritmo closest-pair (par mas cercano).

Notas: usar GeometriaInt.cpp para coordenadas enteras grandes; usar geometria.cpp/geometria3D.cpp para calculos con doubles.