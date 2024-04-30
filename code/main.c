#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "APIG24.h"
#include "EstructuraGrafo24.h"
#include "API2024Parte2.h"

typedef struct {
    u32 *Orden;
    u32 *Color;
    u32 actualCantidadColores;
    u32 prevCantidadColores;
    u32 ji_x;
} CincoUpla;

void LoopDukatGarak(CincoUpla *t, Grafo grafo) {
    for (u32 i = 0; i < 50; i++) {  
        if (GulDukat(grafo, t->Orden) == '1') {
            printf("Error de ordenamiento.\n");
            exit(EXIT_FAILURE);
        }

        t->actualCantidadColores = Greedy(grafo, t->Orden);

        if (t->actualCantidadColores > t->prevCantidadColores) {
            printf("No se cumple el teorema VIT.\n");
            exit(EXIT_FAILURE);   
        }

        t->prevCantidadColores = t->actualCantidadColores;

        if (ElimGarak(grafo, t->Orden) == '1') {
            printf("Error de ordenamiento.\n");
            exit(EXIT_FAILURE);
        }

        t->actualCantidadColores = Greedy(grafo, t->Orden);

        if (t->actualCantidadColores > t->prevCantidadColores) {
            printf("No se cumple el teorema VIT.\n");
            exit(EXIT_FAILURE);   
        }

        t->prevCantidadColores = t->actualCantidadColores;

        t->ji_x = t->actualCantidadColores;
    }
}

int main() {
    Grafo grafo = ConstruirGrafo();
    
    if (grafo == NULL) {
        printf("Error creando grafo.\n");
    }

    u32 n = NumeroDeVertices(grafo);

    CincoUpla t1;
    CincoUpla t2;
    CincoUpla t3;
    CincoUpla t4;
    CincoUpla t5;
    CincoUpla t_min;

    // orden natural
    t1.Orden = malloc(n * sizeof(u32));
    t1.Color = malloc(n * sizeof(u32));
    t1.actualCantidadColores = 0;
    t1.ji_x = 0;

    OrdenNatural(grafo, t1.Orden);

    t1.actualCantidadColores = Greedy(grafo, t1.Orden);
    t1.prevCantidadColores = t1.actualCantidadColores;

    LoopDukatGarak(&t1, grafo);

    ExtraerColores(grafo, t1.Color);

    t_min = t1;

    // orden decreciente
    t2.Orden = malloc(n * sizeof(u32));
    t2.Color = malloc(n * sizeof(u32));
    t2.actualCantidadColores = 0;
    t2.ji_x = 0;

    OrdenDecreciente(grafo, t2.Orden);

    t2.actualCantidadColores = Greedy(grafo, t2.Orden);
    t2.prevCantidadColores = t2.actualCantidadColores;

    LoopDukatGarak(&t2, grafo);

    ExtraerColores(grafo, t2.Color);

    if (t2.ji_x < t_min.ji_x) {
        t_min = t2;
    }

    // orden par impar
    t3.Orden = malloc(n * sizeof(u32));
    t3.Color = malloc(n * sizeof(u32));
    t3.actualCantidadColores = 0;
    t3.ji_x = 0;

    OrdenParImpar(grafo, t3.Orden);

    t3.actualCantidadColores = Greedy(grafo, t3.Orden);
    t3.prevCantidadColores = t3.actualCantidadColores;

    LoopDukatGarak(&t3, grafo);

    ExtraerColores(grafo, t3.Color);

    if (t3.ji_x < t_min.ji_x) {
        t_min = t3;
    }

    // orden grado decreciente
    t4.Orden = malloc(n * sizeof(u32));
    t4.Color = malloc(n * sizeof(u32));
    t4.actualCantidadColores = 0;
    t4.ji_x = 0;

    OrdenGradoDecreciente(grafo, t4.Orden);

    t4.actualCantidadColores = Greedy(grafo, t4.Orden);
    t4.prevCantidadColores = t4.actualCantidadColores;

    LoopDukatGarak(&t4, grafo);

    ExtraerColores(grafo, t4.Color);

    if (t4.ji_x < t_min.ji_x) {
        t_min = t4;
    }

    // orden primos creciente
    t5.Orden = malloc(n * sizeof(u32));
    t5.Color = malloc(n * sizeof(u32));
    t5.actualCantidadColores = 0;
    t5.ji_x = 0;

    OrdenPrimosCreciente(grafo, t5.Orden);

    t5.actualCantidadColores = Greedy(grafo, t5.Orden);
    t5.prevCantidadColores = t5.actualCantidadColores;

    LoopDukatGarak(&t5, grafo);

    ExtraerColores(grafo, t5.Color);

    if (t5.ji_x < t_min.ji_x) {
        t_min = t5;
    }

    // terminan las 5 primeras corridas

    ImportarColores(t_min.Color, grafo);

    for (u32 i = 0; i < 500; i++) {
        srand(time(NULL));

        int random = rand() % 2;

        if (random == 0) {
            if (GulDukat(grafo, t_min.Orden) == '1') {
                printf("Error de ordenamiento.\n");
                exit(EXIT_FAILURE);
            }

            t_min.actualCantidadColores = Greedy(grafo, t_min.Orden);

            if (t_min.actualCantidadColores > t_min.prevCantidadColores) {
                printf("No se cumple el teorema VIT.\n");
                exit(EXIT_FAILURE);   
            }

            t_min.prevCantidadColores = t_min.actualCantidadColores;
        }
        else {
            if (ElimGarak(grafo, t_min.Orden) == '1') {
                printf("Error de ordenamiento.\n");
                exit(EXIT_FAILURE);
            }

            t_min.actualCantidadColores = Greedy(grafo, t_min.Orden);

            if (t_min.actualCantidadColores > t_min.prevCantidadColores) {
                printf("No se cumple el teorema VIT.\n");
                exit(EXIT_FAILURE);   
            }

            t_min.prevCantidadColores = t_min.actualCantidadColores;

            t_min.ji_x = t_min.actualCantidadColores;
        }
    }

    printf("\nχ(G) = %u\n", t_min.ji_x);

    free(t1.Orden);
    free(t1.Color);
    free(t2.Orden);
    free(t2.Color);
    free(t3.Orden);
    free(t3.Color);
    free(t4.Orden);
    free(t4.Color);
    free(t5.Orden);
    free(t5.Color);
    
    DestruirGrafo(grafo);

    return 0;
}