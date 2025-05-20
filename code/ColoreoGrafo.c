#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "API2024Parte2.h"


// structs para las funciones de ordenamiento

typedef struct {
    u32 min_grado;
    u32 max_grado;
} StructDukat;

typedef struct {
    u32 cond;
    color color;
} StructDukat_2;

typedef struct {
    u32 ocurr;
    color color;
} StructGarak;

typedef struct {
    u32 vertice;
    color color;
} VerticeInfo;

// variables globales para qsort

Grafo GRAFO;
u32 *ORDEN_COLORES;

// helpers

u32 max(u32 x, u32 y) {
    return x > y ? x : y;
}

u32 min(u32 x, u32 y) {
    return x < y ? x : y;
}

bool isDivBy(color x, u32 y) {
    u32 a = (u32)x;
    return a % y == 0;
}

bool esPrimo(u32 num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (u32 i = 5; i * i <= num; i = i + 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    return true;
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

// funciones de comparacion para qsort

int cmpMayorGrado(const void *a, const void *b) {
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

int cmpAscDukat(const void *a, const void *b) {
    const StructDukat_2 *elem1 = (const StructDukat_2 *)a;
    const StructDukat_2 *elem2 = (const StructDukat_2 *)b;

    if (elem1->cond < elem2->cond) {
        return -1;
    } else if (elem1->cond > elem2->cond) {
        return 1;
    } else {
        return 0;
    }
}

int cmpDescDukat(const void *a, const void *b) {
    const StructDukat_2 *elem1 = (const StructDukat_2 *)a;
    const StructDukat_2 *elem2 = (const StructDukat_2 *)b;

    if (elem1->cond < elem2->cond) {
        return 1;
    } else if (elem1->cond > elem2->cond) {
        return -1;
    } else {
        return 0;
    }
}

int cmpOrdenarColores(const void* a, const void* b) {
    const VerticeInfo* verticeA = (const VerticeInfo *)a;
    const VerticeInfo* verticeB = (const VerticeInfo *)b;

    int ordenColorA = ORDEN_COLORES[verticeA->color - 1];
    int ordenColorB = ORDEN_COLORES[verticeB->color - 1];

    if (ordenColorA != ordenColorB) {
        return ordenColorA - ordenColorB;
    }

    return 0;
}

int cmpAscGarak(const void *a, const void *b) {
    const StructGarak *elem1 = (const StructGarak *)a;
    const StructGarak *elem2 = (const StructGarak *)b;

    return elem1->ocurr - elem2->ocurr;
}

int cmpParImpar(const void *a, const void *b) {
    u32 num1 = *(u32*)a;
    u32 num2 = *(u32*)b;

    if (num1 % 2 == 0 && num2 % 2 == 0) {
        return (num2 - num1);
    }
    else if (num1 % 2 != 0 && num2 % 2 != 0) {
        return (num1 - num2);
    }
    else if (num1 % 2 == 0) {
        return -1;
    }
    else {
        return 1;
    }
}

int cmpPrimos(const void *a, const void *b) {
    u32 num1 = *(u32*)a;
    u32 num2 = *(u32*)b;
    
    bool esPrimoNum1 = esPrimo(num1);
    bool esPrimoNum2 = esPrimo(num2);

    if (esPrimoNum1&& esPrimoNum2) {
        return (num1 - num2);
    }
    else if (esPrimoNum1) {
        return -1;
    }
    else if (esPrimoNum2) {
        return 1;
    }
    else {
        return (num1 - num2);
    }
}

// funciones

u32 Greedy(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    if (!verificarBiyeccion(Orden, n)) { // Orden no induce biyeccion
        return -1;
    }

    u32 delta_p_1 = Delta(G) + 1; // maximo de colores permitidos
    u32 maxColor = 0;

    /*
    lista de colores asignados a los vertices
    result[v] es el color del vertice v
    */
    u32 *result = malloc(n * sizeof(u32));

    if (result == NULL) { // error de alocacion de memoria
        return -1;
    }

    result[Orden[0]] = 1; // asignamos el color 1 al primer vertice del orden dado

    for (u32 i = 1; i < n; i++) {
        result[Orden[i]] = NULL_COLOR; // el resto de los vertices no tienen color
    }
    
    /*
    lista temporal para guardar los colores disponibles.
    el valor 1 de available[cr] indica que el color cr
    está asignado a uno de los vertices adyacentes
    */
    u32 *available = malloc(delta_p_1 * sizeof(u32)); 

    if (available == NULL) { // error de alocacion de memoria
        return -1;
    }

    for (u32 cr = 0; cr < delta_p_1; cr++) {
        available[cr] = 0;
    }

    // recorremos los demas n-1 vertices en el orden dado
    for (u32 i = 1; i < n; i++) {
        u32 vertice = Orden[i];
        u32 grado = Grado(vertice, G);

        // recorremos todos los vecinos del vertice
        for (u32 j = 0; j < grado; j++) {
            u32 indiceVecino = Vecino(j, vertice, G);
            // si encontramos un vecino coloreado, lo marcamos como no disponible
            if (result[indiceVecino] != NULL_COLOR) {
                available[result[indiceVecino] - 1] = 1;
            }
        }

        // buscamos el primer color disponible
        u32 cr;
        for (cr = 0; cr < delta_p_1; cr++) {
            if (available[cr] == NULL_COLOR) {
                cr++;
                break;
            }
        }

        result[vertice] = cr; // asignamos color cr a vertice

        // reseteamos la lista a NULL_COLOR para la proxima iteracion
        for (u32 j = 0; j < grado; j++) {
            u32 indiceVecino = Vecino(j, vertice, G);
            if (result[indiceVecino] != NULL_COLOR) {
                available[result[indiceVecino] - 1] = NULL_COLOR;
            }
        }

        maxColor = max(cr, maxColor);
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        AsignarColor(result[vertice], vertice, G);
    }

    free(result);
    result = NULL;
    free(available);
    available = NULL;

    return maxColor;
}

char GulDukat(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    if (Orden == NULL) {
        OrdenNatural(G, Orden);
    }

    u32 maxColor = 0;

    VerticeInfo *vertices = malloc(n * sizeof(VerticeInfo));

    if (vertices == NULL) {
        return 1;
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        color color = Color(vertice, G);
        
        vertices[vertice].vertice = vertice;
        vertices[vertice].color = color;
        
        maxColor = max(maxColor, Color(vertice, G));
    }

    StructDukat *grados = malloc(maxColor * sizeof(StructDukat));

    if (grados == NULL) {
        return 1;
    }

    for (u32 cr = 0; cr < maxColor; cr++) {
        grados[cr].max_grado = 0;
        grados[cr].min_grado = -1;
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        color color = Color(vertice, G) - 1;
        u32 grado = Grado(vertice, G);

        grados[color].min_grado = min(grados[color].min_grado, grado);
        grados[color].max_grado = max(grados[color].max_grado, grado);
    }

    StructDukat_2 *div4 = malloc(maxColor * sizeof(StructDukat_2));
    StructDukat_2 *pares = malloc(maxColor * sizeof(StructDukat_2));
    StructDukat_2 *impares = malloc(maxColor * sizeof(StructDukat_2));

    if (div4 == NULL || pares == NULL || impares == NULL) {
        return 1;
    }

    for (u32 cr = 0; cr < maxColor; cr++) {
        div4[cr].cond = 0;
        div4[cr].color = 0;

        pares[cr].cond = 0;
        pares[cr].color = 0;

        impares[cr].cond = -1;
        impares[cr].color = 0;
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        color color = Color(vertice, G);
        u32 indice = color - 1;

        if (isDivBy(color, 4)) {
            div4[indice].cond = grados[indice].max_grado;
            div4[indice].color = color;
        }
        else if (isDivBy(color, 2)) {
            pares[indice].cond = grados[indice].max_grado + grados[indice].min_grado;
            pares[indice].color = color;
        }
        else {
            impares[indice].cond = grados[indice].min_grado;
            impares[indice].color = color;
        }
    }

    qsort(div4, maxColor, sizeof(StructDukat_2), cmpDescDukat);
    qsort(pares, maxColor, sizeof(StructDukat_2), cmpDescDukat);
    qsort(impares, maxColor, sizeof(StructDukat_2), cmpDescDukat);

    u32 *ordenColores = calloc(maxColor, sizeof(u32));
    u32 indiceCr = 0;

    if (ordenColores == NULL) {
        return 1;
    }

    for (u32 cr = 0; cr < maxColor; cr++) {
        if (div4[cr].color != 0) {
            ordenColores[div4[cr].color - 1] =  indiceCr++;
        }
    }

    for (u32 cr = 0; cr < maxColor; cr++) {
        if (pares[cr].color != 0) {
            ordenColores[pares[cr].color - 1] = indiceCr++;
        }
    }

    for (u32 cr = 0; cr < maxColor; cr++) {
        if (impares[cr].color != 0) {
            ordenColores[impares[cr].color - 1] = indiceCr++;
        }
    }
    
    ORDEN_COLORES = ordenColores;

    qsort(vertices, n, sizeof(VerticeInfo), cmpOrdenarColores);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = vertices[i].vertice;
    }

    free(vertices);
    vertices = NULL;
    free(grados);
    grados = NULL;
    free(div4);
    div4 = NULL;
    free(pares);
    pares = NULL;
    free(impares);
    impares = NULL;
    free(ordenColores);
    ordenColores = NULL;

    return 0;
}

char ElimGarak(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    if (Orden == NULL) {
        OrdenNatural(G, Orden);
    }

    u32 maxColor = 0;
    u32 ignoreColors = 2; // offset para ignorar colores 1 y 2

    VerticeInfo *vertices = malloc(n * sizeof(VerticeInfo));

    if (vertices == NULL) {
        return 1;
    }

    for (u32 i = 0; i < n; i++) {
        u32 vertice = Orden[i];
        color color = Color(vertice, G);

        vertices[vertice].vertice = vertice;
        vertices[vertice].color = color;

        maxColor = max(maxColor, Color(vertice, G));
    }

    StructGarak *colores = malloc(maxColor * sizeof(StructGarak));

    if (colores == NULL) {
        return 1;
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

    // switcheamos primero <-> ultimo y segundo <-> penultimo
    StructGarak tmp_0 = colores[0];
    StructGarak tmp_1 = colores[1];

    colores[0] = colores[maxColor - 1];
    colores[1] = colores[maxColor - 2];
    colores[maxColor - 1] = tmp_0;
    colores[maxColor - 2] = tmp_1;

    // ordenamos colores ignorando 1 y 2
    qsort(colores, (maxColor - ignoreColors), sizeof(StructGarak), cmpAscGarak);

    u32 *ordenColores = malloc(maxColor * sizeof(u32));

    if (ordenColores == NULL) {
        return 1;
    }

    for (u32 i = 0; i < maxColor; i++) {
        u32 color = colores[i].color;
        ordenColores[color - 1] = i;
    }

    ORDEN_COLORES = ordenColores;

    qsort(vertices, n, sizeof(VerticeInfo), cmpOrdenarColores);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = vertices[i].vertice;
    }

    free(vertices);
    vertices = NULL;
    free(colores);
    colores = NULL;
    free(ordenColores);
    ordenColores = NULL;

    return 0;
}

char OrdenNatural(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    return 0;
}

char OrdenDecreciente(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = n-i-1;
    }

    return 0;
}

char OrdenParImpar(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    qsort(Orden, n, sizeof(u32), cmpParImpar);

    return 0;
}

char OrdenGradoDecreciente(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    GRAFO = G;

    qsort(Orden, n, sizeof(u32), cmpMayorGrado);

    return 0;
}

char OrdenPrimosCreciente(Grafo G, u32 *Orden) {
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++) {
        Orden[i] = i;
    }

    qsort(Orden, n, sizeof(u32), cmpPrimos);

    return 0;
}
