#include <stdlib.h>
#include <stdio.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"

void InfoGrafo(Grafo G) {
    printf("\n///// Informacion del Grafo /////\n\n");
    printf(" - Numero de vertices: %u\n", NumeroDeVertices(G));
    printf(" - Numero de lados:    %u\n", NumeroDeLados(G));
    printf(" - Delta:              %u\n", Delta(G));
    printf("\n/////////////////////////////////\n");
}

void PrintEstructuraGrafo(Grafo G) {
    printf("\nVertice | Color | Vecinos\n");
    printf("---------------------------\n");
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        printf("   %u    |   %u   | ", i, (u32) Color(i, G));
        for (u32 j = 0; j < Grado(i, G); j++) {
            printf("%u", Vecino(j, i, G));
            if (j < Grado(i, G) - 1)
                printf(", ");
        }
        printf("\n");
    }
}

int main() {
    printf("Construyendo grafo...\n\n");
    Grafo grafo = ConstruirGrafo();

    InfoGrafo(grafo);

    PrintEstructuraGrafo(grafo);

    DestruirGrafo(grafo);

    return 0;
}
