#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ColoreoGrafo.h"
#include "API2024Parte2.h"

u32 max(u32 x, u32 y) {
    return x > y ? x : y;
}

void printArray(u32 *arr, u32 n) {
    printf("[");
    for (u32 i = 0; i < n; i++) {
        if (i == n-1) {
            printf("%u", arr[i]);
        }
        else {
            printf("%u, ", arr[i]);
        }
    }
    printf("]\n");
}

bool verificarBiyeccion(u32 *Orden, u32 n) {
    bool *marcados = calloc(n, sizeof(bool));
    if (marcados == NULL) {
        return false;
    }

    for (u32 i = 0; i < n; i++) {
        if (Orden[i] >= n) {
            free(marcados);
            return false;
        }
        marcados[Orden[i]] = true;
    }

    for (u32 i = 0; i < n; i++) {
        if (!marcados[i]) {
            free(marcados);
            return false;
        }
    }

    free(marcados);
    marcados = NULL;

    return true;
}

u32 Greedy(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);
    u32 maxColor = 0;
    u32 *result = calloc(n, sizeof(u32)); // lista de vertices coloreados inicializados en 0 (NULL_COLOR)
    u32 *available = calloc(n, sizeof(u32)); // lista de vecinos disponibles

    if (result == NULL || available == NULL) { // error de alocacion de memoria
        return -1;
    }

    if (!verificarBiyeccion(Orden, n)) { // Orden no induce biyeccion
        free(result);
        result = NULL;
        free(available);
        available = NULL;
        
        return -1;
    }

    // recorremos todos los vertices en el orden dado
    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        u32 grado = Grado(vertice, G);

        // recorremos todos los vecinos del vertice
        for (u32 j = 0; j < grado; j++) {
            u32 indiceVecino = Vecino(j, vertice, G);
            // si encontramos un vecino coloreado, lo marcamos
            if (result[indiceVecino] != NULL_COLOR)
                available[result[indiceVecino] - 1] = 1;
        }

        // recorremos lista de vecinos coloreados hasta encontrar el primer color disponible
        u32 cr = 1;
        for (u32 i = 0; i < n; i++) {
            if (available[i] == 0)
                break;
            cr++;
        }

        result[vertice] = cr;
        AsignarColor(cr, vertice, G);

        // printf("vertice %u:\n", vertice);
        // printArray(available, n);
        // printArray(result, n);
        // printf("\n");

        // reseteamos lista de vecinos para la proxima iteracion
        for (u32 j = 0; j < grado; j++) {
            u32 indiceVecino = Vecino(j, vertice, G);
            if (result[indiceVecino] != NULL_COLOR)
                available[result[indiceVecino]] = 0;
        }

        maxColor = max(cr, maxColor);
    }

    free(result);
    result = NULL;
    free(available);
    available = NULL;

    return maxColor;
}


void OrdenNatural(u32 *Orden, u32 n) {
    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }
}
