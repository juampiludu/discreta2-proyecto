#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "API2024Parte2.h"

u32 max(u32 x, u32 y) {
    return x > y ? x : y;
}

u32 min(u32 x, u32 y) {
    return x < y ? x : y;
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

Grafo GRAFO;

bool isDivBy(color x, u32 y) {
    u32 a = (u32)x;
    return a % y == 0;
}

// M(x)
int compararPorMayorGrado(const void *a, const void *b) {
    const u32 *verticeA = (const u32 *)a;
    const u32 *verticeB = (const u32 *)b;

    int gradoA = (int)Grado(*verticeA, GRAFO);
    int gradoB = (int)Grado(*verticeB, GRAFO);

    if (gradoA != gradoB) {
        return gradoB - gradoA;
    }
    else {
        return verticeB - verticeA;
    }
}

// m(x)
int compararPorMenorGrado(const void *a, const void *b) {
    const u32 *verticeA = (const u32 *)a;
    const u32 *verticeB = (const u32 *)b;

    int gradoA = (int)Grado(*verticeA, GRAFO);
    int gradoB = (int)Grado(*verticeB, GRAFO);

    if (gradoA != gradoB) {
        return gradoA - gradoB;
    }
    else {
        return verticeB - verticeA;
    }
}

// M(x) + m(x)
// int compararPorSumaGrados(const void *a, const void *b) {
//     const u32 *verticeA = (const u32 *)a;
//     const u32 *verticeB = (const u32 *)b;

//     int gradoA = (int)Grado(*verticeA, GRAFO);
//     int gradoB = (int)Grado(*verticeB, GRAFO);

//     int sumaA = gradoA + gradoB;
//     int sumaB = gradoB + gradoA;

//     if (sumaA != sumaB) {
//         return sumaB - sumaA;
//     }
//     else {
//         return verticeB - verticeA;
//     }
// }

char GulDukat(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    u32 indice1 = 0, indice2 = 0, indice3 = 0; // indices de las respectivas listas
    u32 *divisible4 = malloc(n * sizeof(u32));
    u32 *pares = malloc(n * sizeof(u32));
    u32 *impares = malloc(n * sizeof(u32));

    if (divisible4 == NULL || pares == NULL || impares == NULL) {
        return '1';
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        u32 color = Color(vertice, G);

        if (isDivBy(color, 4)) {
            divisible4[indice1++] = vertice;
        }
        else if (isDivBy(color, 2)) {
            pares[indice2++] = vertice;
        }
        else {
            impares[indice3++] = vertice;
        }
    }

    divisible4 = realloc(divisible4, indice1 * sizeof(u32));
    pares = realloc(pares, indice2 * sizeof(u32));
    impares = realloc(impares, indice3 * sizeof(u32));

    GRAFO = G;

    qsort(divisible4, indice1, sizeof(u32), compararPorMayorGrado);
    qsort(pares, indice2, sizeof(u32), compararPorMayorGrado);
    qsort(impares, indice3, sizeof(u32), compararPorMenorGrado);

    // printf("Divisibles por 4           : ");
    // printArray(divisible4, indice1);
    // printf("Pares no divisibles por 4  : ");
    // printArray(noDivisible4Par, indice2);
    // printf("Impares no divisibles por 4: ");
    // printArray(noDivisible4Impar, indice3);
    // printArray(Orden, n);

    u32 i = 0;

    for (u32 j = 0; j < indice1; j++) {
        Orden[i] = divisible4[j];
        i++;
    }

    for (u32 j = 0; j < indice2; j++) {
        Orden[i] = pares[j];
        i++;
    }

    for (u32 j = 0; j < indice3; j++) {
        Orden[i] = impares[j];
        i++;
    }

    free(divisible4);
    divisible4 = NULL;
    free(pares);
    pares = NULL;
    free(impares);
    impares = NULL;

    // printArray(Orden, n);

    return '0';
}

char ElimGarak(Grafo G, u32 *Orden) {
    return '0';
}

char OrdenNatural(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    return  '0';
}
