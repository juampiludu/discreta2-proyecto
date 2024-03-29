#include <stdlib.h>
#include <stdio.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"

int main() {
    Grafo grafo = ConstruirGrafo();
    u32 n = NumeroDeVertices(grafo);
    u32 m = NumeroDeLados(grafo);
    u32 delta = Delta(grafo);

    printf("n = %u, m = %u, delta = %u\n", n, m, delta);

    DestruirGrafo(grafo);

    return 0;
}