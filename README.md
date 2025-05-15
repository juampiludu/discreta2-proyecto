# Coloreo de Grafos

Este proyecto fue desarrollado como parte de la materia Matemática Discreta II en la carrera de Ciencias de la Computación @ FaMAF - UNC.  
El objetivo principal es implementar un algoritmo de coloreo de grafos, tomando como entrada un archivo en formato DIMACS y produciendo como salida el número cromático del grafo, $\chi(G)$.  
Quiero agradecer a [Dianela Fernández](https://github.com/Diane-bc) y [Guadalupe Galindo](https://github.com/GuadaGalindo) que fueron de gran ayuda para el armado preciso de los algoritmos.

## 1. Descripción del Problema

Se necesita minimizar el número de colores utilizados en el coloreo de un grafo para optimizar la asignación de recursos en contextos donde existen restricciones de compatibilidad o interferencia. Esto permite resolver problemas prácticos como la planificación de horarios, la asignación de frecuencias en redes, y la organización eficiente de tareas, minimizando conflictos y mejorando el aprovechamiento del sistema.

- **Entrada:** Archivo TXT en formato DIMACS.
- **Salida:** $\chi(G)$.

## 2. Diseño e Implementación

### 2.1 Representación del grafo

- Lista de adyacencia / matriz de vecinos.

### 2.2 Algoritmos de coloreo

- **Greedy**: asignación de colores según primer disponible.
- **GulDukat**: heurística basada en grados máximos/mínimos.
- **ElimGarak**: heurística basada en ocurrencias de colores.
- **Órdenes de procesado**: natural, decreciente, par-impar, grado-decreciente, primos.

## 3. Complejidad Computacional de las Funciones Principales

### Estructura del Grafo

- **ConstruirGrafo:** $O(n + m)$
- **DestruirGrafo:** $O(n)$

### Extraccion de datos del Grafo

- **ExtraerColores:** $O(n)$
- **ImportarColores:** $O(n)$

> Todas las otras funciones de extracción tienen complejidad $O(1)$.

### Coloreo del Grafo

- **Greedy:** $O(n + m)$
- **GulDukat:** $O(n \log n)$
- **ElimGarak:** $O(n \log n)$

### Ordenes de Vertices

- **OrdenNatural / OrdenDecreciente:** $O(n)$
- **OrdenParImpar:** $O(n \log n)$
- **OrdenGradoDecreciente:** $O(n \log n)$
- **OrdenPrimosCreciente:** $O(n)$

<br>

> Ver [Enunciado Parte 1](/EnunciadoParte1.pdf) y [Enunciado Parte 2](/EnunciadoParte2.pdf) para definición formal de las funciones listadas.

## 4. Requisitos

- Compilador C compatible con C99 o superior.
- `make` instalado (GNU Make).

Clonar el repositorio:

```bash
git clone https://github.com/juampiludu/discreta2-proyecto.git
cd discreta2-proyecto
```

## 5. Uso del Programa

Primero, dirigirse al directorio de código:

```bash
cd code/
```

Compilar el programa con `make` y ejecutarlo pasando un archivo en formato DIMACS:

```bash
make
./grafo < ruta/al/grafo.txt
```

> El directorio `grafos` contiene instancias de prueba que pueden utilizarse para testear el programa.  
> Si se desea crear nuevos grafos, se recomienda guardarlos también en este directorio para mantener la organización del proyecto.

Para eliminar archivos temporales generados durante la compilación:

```bash
make clean
```

## 6. Formato de Entrada

```
c <comentario>

p edge <cantidad_vertices> <cantidad_aristas>
e <v1> <v2>
...
```

Los vértices deben estar etiquetados con los enteros $`\{0, 1, 2, \ldots, n - 1\}`$, donde $n$ es la cantidad total de vértices. <br>
Es decir, se deben usar exactamente los primeros $n-1$ números naturales, por lo tanto, el conjunto de vertices aceptado es:

```math
V = \{v_x \in \mathbb{N} \cup \{0\} : v_1 = 0 \ \wedge \ v_2 = 1 \ \wedge \ \ldots \ \wedge \ v_n = n-1 \}
```

## 7. Ejemplo de Entrada/Salida

Archivo de entrada (`grafo.txt`):

```
p edge 4 3
e 0 1
e 1 2
e 2 3
```

Salida:

```
χ(G) = 2
```

> La salida corresponde a la ejecución del archivo `main.c`.

## 8. Archivos Principales

- `main.c`: implementación principal, definida según el punto 4 del [Enunciado Parte 2](/EnunciadoParte2.pdf).
- `main2.c`: pruebas básicas para validar el funcionamiento general de los algoritmos.
- `test.c`: pruebas unitarias y de robustez para cada función implementada.
