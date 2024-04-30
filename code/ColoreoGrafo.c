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
        color color = Color(vertice, G);

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
    // printArray(pares, indice2);
    // printf("Impares no divisibles por 4: ");
    // printArray(impares, indice3);
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

typedef struct {
    u32 ocurr;
    color color;
} Par;

int cmpDesc(const void *a, const void *b) {
    const Par *elem1 = (const Par *)a;
    const Par *elem2 = (const Par *)b;

    return elem1->ocurr - elem2->ocurr;
}

void buscarColores(u32 start, u32 end, u32 *Orden, Par *colores, u32 n, u32 *indice, u32 *tmpOrden, Grafo G) {
    for (u32 cr = start; cr < end; cr++) {
        for (u32 i = 0; i < n; i++) {
            u32 vertice = Orden[i];
            color color = Color(vertice, G);
            u32 ocurr = 0;

            if (color == colores[cr].color) {
                tmpOrden[*indice] = vertice;
                *indice += 1;
                ocurr++;
                if (ocurr == colores[cr].ocurr) {
                    break;
                }
            }
        }
    }
}

char ElimGarak(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);
    u32 maxColor = 0;
    u32 ignoreColors = 2;

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        maxColor = max(maxColor, Color(vertice, G));
    }

    Par *colores = malloc(maxColor * sizeof(Par *));

    if (colores == NULL) {
        return '1';
    }

    for (u32 cr = 0; cr < maxColor; cr++) {
        colores[cr].ocurr = 0;
        colores[cr].color = NULL_COLOR;
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        color color = Color(vertice, G);

        colores[color - 1].ocurr++;
        colores[color - 1].color = color;
    }

    qsort((colores + ignoreColors), (maxColor - ignoreColors), sizeof(Par), cmpDesc);

    // for (u32 cr = 0; cr < maxColor; cr++) {
    //     printf("color = %u, ocurrs = %u\n", colores[cr].color, colores[cr].ocurr);
    // }

    u32 *tmpOrden = calloc(n, sizeof(u32));
    u32 indice = 0;

    if (tmpOrden == NULL) {
        return '1';
    }
    
    buscarColores(ignoreColors, maxColor, Orden, colores, n, &indice, tmpOrden, G);
    buscarColores(0, ignoreColors, Orden, colores, n, &indice, tmpOrden, G);

    // printArray(tmpOrden, n);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = tmpOrden[i];
    }

    free(colores);
    colores = NULL;
    free(tmpOrden);
    tmpOrden = NULL;

    return '0';
}

char OrdenNatural(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    return  '0';
}

char OrdenDecreciente(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = n-i-1;
    }

    return  '0';
}

int cmpParImpar(const void *a, const void *b) {
    u32 num1 = *(u32*)a;
    u32 num2 = *(u32*)b;

    // Si ambos son pares, ordénalos en orden decreciente
    if (num1 % 2 == 0 && num2 % 2 == 0) {
        return (num2 - num1);
    }
    // Si ambos son impares, ordénalos en orden creciente
    else if (num1 % 2 != 0 && num2 % 2 != 0) {
        return (num1 - num2);
    }
    // Los pares van primero
    else if (num1 % 2 == 0) {
        return -1;
    }
    // Los impares van después
    else {
        return 1;
    }
}

char OrdenParImpar(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    qsort(Orden, n, sizeof(u32), cmpParImpar);

    return  '0';
}

char OrdenGradoDecreciente(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    GRAFO = G;

    qsort(Orden, n, sizeof(u32), compararPorMayorGrado);

    return  '0';
}

// Función para verificar si un número es primo
bool esPrimo(u32 num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (u32 i = 5; i * i <= num; i = i + 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    return true;
}

int cmpPrimos(const void *a, const void *b) {
    u32 num1 = *(u32*)a;
    u32 num2 = *(u32*)b;

    // Si ambos son primos, ordénalos en orden creciente
    if (esPrimo(num1) && esPrimo(num2)) {
        return (num1 - num2);
    }
    // Si uno es primo y el otro no, el primo va primero
    else if (esPrimo(num1)) {
        return -1;
    }
    else if (esPrimo(num2)) {
        return 1;
    }
    // Si ninguno es primo, ordénalos normalmente
    else {
        return (num1 - num2);
    }
}

char OrdenPrimosCreciente(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    qsort(Orden, n, sizeof(u32), cmpPrimos);

    return  '0';
}
