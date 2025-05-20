#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "API2024Parte2.h"

#define CICLOS_INICIALES 50
#define CICLOS_FINALES   500
#define NUM_ORDENES      5

int main() {
    Grafo G = ConstruirGrafo();
    if (!G) {
        fprintf(stderr, "Error creando grafo\n");
        return EXIT_FAILURE;
    }
    u32 n = NumeroDeVertices(G);
    u32 delta = Delta(G);

    u32 *Orden = malloc(n * sizeof(u32));
    u32 *Color = malloc(n * sizeof(u32));
    if (!Orden || !Color) {
        fprintf(stderr, "Error de memoria\n");
        return EXIT_FAILURE;
    }

    char (*ordenes[NUM_ORDENES])(Grafo, u32*) = {
        OrdenNatural,
        OrdenDecreciente,
        OrdenParImpar,
        OrdenGradoDecreciente,
        OrdenPrimosCreciente
    };

    u32 numCrom = delta + 1;

    for (int o = 0; o < NUM_ORDENES; o++) {
        ordenes[o](G, Orden);

        u32 tempNumCrom = Greedy(G, Orden);
        if (tempNumCrom > delta + 1) {
            fprintf(stderr, "No se cumple cota Δ+1 en Greedy inicial\n");
            return EXIT_FAILURE;
        }
        printf("Run %d - Greedy inicial: %u colores\n", o+1, tempNumCrom);
        u32 prevNumCrom = tempNumCrom;

        for (int i = 0; i < CICLOS_INICIALES; i++) {
            if (GulDukat(G, Orden)) {
                fprintf(stderr, "Error de ordenamiento (GulDukat)\n");
                return EXIT_FAILURE;
            }
            tempNumCrom = Greedy(G, Orden);
            if (tempNumCrom > delta + 1) {
                fprintf(stderr, "No se cumple cota Δ+1 tras GulDukat+Greedy\n");
                return EXIT_FAILURE;
            }
            if (tempNumCrom > prevNumCrom) {
                fprintf(stderr, "No se cumple el teorema VIT tras GulDukat+Greedy\n");
                return EXIT_FAILURE;
            }
            printf("  Ciclo %2d.GD: %u\n", i+1, tempNumCrom);
            prevNumCrom = tempNumCrom;

            if (ElimGarak(G, Orden)) {
                fprintf(stderr, "Error de ordenamiento (ElimGarak)\n");
                return EXIT_FAILURE;
            }
            tempNumCrom = Greedy(G, Orden);
            if (tempNumCrom > delta + 1) {
                fprintf(stderr, "No se cumple cota Δ+1 tras ElimGarak+Greedy\n");
                return EXIT_FAILURE;
            }
            if (tempNumCrom > prevNumCrom) {
                fprintf(stderr, "No se cumple el teorema VIT tras ElimGarak+Greedy\n");
                return EXIT_FAILURE;
            }
            printf("  Ciclo %2d.EG: %u\n", i+1, tempNumCrom);
            prevNumCrom = tempNumCrom;
        }

        if (prevNumCrom < numCrom) {
            numCrom = prevNumCrom;
            ExtraerColores(G, Color);
        }
    }

    ImportarColores(Color, G);
    printf("Mejor coloreo inicial: %u colores → relanzando %d iteraciones finales\n",
           numCrom, CICLOS_FINALES);

    srand((unsigned)time(NULL));
    u32 prevNumCrom = numCrom;

    for (int i = 0; i < CICLOS_FINALES; i++) {
        if (rand() % 2 == 0) {
            if (GulDukat(G, Orden)) {
                fprintf(stderr, "Error de ordenamiento (GulDukat final)\n");
                return EXIT_FAILURE;
            }
        } else {
            if (ElimGarak(G, Orden)) {
                fprintf(stderr, "Error de ordenamiento (ElimGarak final)\n");
                return EXIT_FAILURE;
            }
        }
        u32 tempNumCrom = Greedy(G, Orden);
        if (tempNumCrom > delta + 1) {
            fprintf(stderr, "No se cumple cota Δ+1 en iteración final %d\n", i+1);
            return EXIT_FAILURE;
        }
        if (tempNumCrom > prevNumCrom) {
            fprintf(stderr, "No se cumple el teorema VIT en iteración final %d\n", i+1);
            return EXIT_FAILURE;
        }
        printf("Final %3d: %u colores\n", i+1, tempNumCrom);
        prevNumCrom = tempNumCrom;
    }

    numCrom = prevNumCrom;

    printf("\nχ(G) = %u\n", numCrom);

    free(Orden);
    free(Color);
    DestruirGrafo(G);

    return EXIT_SUCCESS;
}
