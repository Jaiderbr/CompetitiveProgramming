# geometria

- `Circle.cpp`: funciones para circunferencias (circumCenter, circleLine, circleCircle, tangents).
- `geometria.cpp`: primitivas 2D (pt, line), dist, sarea, ccw, proj, inter, interseg, distseg y transformaciones.
- `geometria3D.cpp`: primitivas 3D (pt), proyecciones, distancias, intersecciones con planos y rotaciones en 3D.
- `GeometriaInt.cpp`: versión entera (pt con int) con polarea2, inpol, convex_hull, segpoints y operaciones enteras robustas.
- `isfigure.cpp`: programa que clasifica un cuadrilátero (ej: square, rectangle, rhombus, parallelogram, trapezium, kite, none).
- `Polygon.cpp`: área, punto en polígono, convex_hull, cut_polygon, intersección y distancia entre polígonos.
- `sweep line.cpp`: utilidades de sweep (comparadores y estructuras), detección de intersecciones y algoritmo closest-pair.


Notas: 
- Usar GeometriaInt.cpp para coordenadas enteras grandes; usar geometria.cpp/geometria3D.cpp para calculos con double. 
- Para problemas de interseccion de muchos segmentos, usar sweep line.