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

// void PrintEstructuraGrafo(Grafo G) {
//     printf("Vertice | Color  | Vecinos\n");
//     printf("---------------------------\n");
//     for (u32 i = 0; i < NumeroDeVertices(G); i++) {
//         printf("   %c   | %-6s | ", //vertice, //color);
//         for (int j = 0; j < //grado; j++) {
//             printf("%c", //vecinos);
//             if (j < //grado - 1)
//                 printf(", ");
//         }
//         printf("\n");
//     }
// }

int main() {
    printf("Construyendo grafo...\n\n");
    Grafo grafo = ConstruirGrafo();
    // u32 n = NumeroDeVertices(grafo);

    InfoGrafo(grafo);

    DestruirGrafo(grafo);

    return 0;
}
