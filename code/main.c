#include <stdlib.h>
#include <stdio.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"
#include "API2024Parte2.h"

typedef struct {
    u32 *Orden;
    u32 actualCantidadColores;
    u32 prevCantidadColores;
    u32 ji_x;
} CuatroUpla;

int main() {
    Grafo grafo = ConstruirGrafo();
    
    if (grafo == NULL) {
        printf("Error creando grafo.\n");
    }

    u32 n = NumeroDeVertices(grafo);

    CuatroUpla t1;
    t1.Orden = malloc(n * sizeof(u32));
    t1.actualCantidadColores = 0;

    OrdenNatural(grafo, t1.Orden);

    t1.actualCantidadColores = Greedy(grafo, t1.Orden);
    t1.prevCantidadColores = t1.actualCantidadColores;
    printf("nat- ji_x: %u\n", t1.actualCantidadColores);

    for (u32 i = 0; i < 50; i++) {  
        if (GulDukat(grafo, t1.Orden) == '1') {
            printf("Error de ordenamiento.\n");
            exit(EXIT_FAILURE);
        }

        t1.actualCantidadColores = Greedy(grafo, t1.Orden);
        printf("duk- ji_x: %u\n", t1.actualCantidadColores);

        if (t1.actualCantidadColores > t1.prevCantidadColores) {
            printf("No se cumple el teorema VIT.\n");
            exit(EXIT_FAILURE);   
        }

        t1.prevCantidadColores = t1.actualCantidadColores;

        if (ElimGarak(grafo, t1.Orden) == '1') {
            printf("Error de ordenamiento.\n");
            exit(EXIT_FAILURE);
        }

        t1.actualCantidadColores = Greedy(grafo, t1.Orden);
        printf("gar- ji_x: %u\n", t1.actualCantidadColores);

        if (t1.actualCantidadColores > t1.prevCantidadColores) {
            printf("No se cumple el teorema VIT.\n");
            exit(EXIT_FAILURE);   
        }

        t1.prevCantidadColores = t1.actualCantidadColores;

        t1.ji_x = t1.actualCantidadColores;
    }

    printf("ji_x: %u\n", t1.ji_x);

    DestruirGrafo(grafo);

    return 0;
}