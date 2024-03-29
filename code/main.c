#include <stdlib.h>
#include <stdio.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"

int main() {
    Grafo grafo = ConstruirGrafo();
    u32 n = NumeroDeVertices(grafo);
    u32 m = NumeroDeLados(grafo);
    u32 delta = Delta(grafo);
    u32 grado_1 = Grado(1, grafo);
    u32 vecino = Vecino(1, 1, grafo);

    printf("n = %u, m = %u, delta = %u, grado de 1 = %u, vecino = %u\n", n, m, delta, grado_1, vecino);

    DestruirGrafo(grafo);

    return 0;
}