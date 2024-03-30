#include <stdio.h>
#include <stdlib.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"

#define MAX_LINE_SIZE 1000

struct LadoSt {
    u32 vert1;
    u32 vert2;
};

typedef struct LadoSt *lado;

struct VerticeSt {
    u32 grado;
    color color;
};

typedef struct VerticeSt *vertice;

struct _GrafoSt {
    u32 cantidadVertices;
    u32 cantidadLados;
    u32 delta;
    vertice *vertices;
    u32 **vecinos;
};

u32 max(u32 x, u32 y) {
    return x > y ? x : y;
}

Grafo ConstruirGrafo() {

    u32 cantidadVertices = 0, cantidadLados = 0;
    u32 vert1, vert2;
    u32 indiceLado = 0, ladosLeidos = 0;
    char line[MAX_LINE_SIZE], edge[5];
    char p;
    lado *listaLados = NULL;
    while (fgets(line, MAX_LINE_SIZE, stdin)) {
        // salteamos todos los comentarios
        if (line[0] == 'c' || line[0] == '\n') {
            continue;

        // procesamos la cantidad de vertices y lados
        } else if (line[0] == 'p'){
            if (sscanf(line, "%c %4s %u %u", &p, edge, &cantidadVertices, &cantidadLados) != 4)
                return NULL;
            if (cantidadVertices < 2 || cantidadLados == 0) 
                return NULL;
            // como ya se cuantos lados hay, creo la lista con 2*m lugares
            listaLados = malloc(2*cantidadLados * sizeof(lado));
    
        // procesamos los lados
        } else if (line[0]=='e') {
            if (sscanf(line, "%c %u %u", &p, &vert1, &vert2) != 3)
                return NULL;
            // cargar lados (lado2 es el lado1 invertido)
            lado lado1 = malloc(sizeof(lado));
            lado lado2 = malloc(sizeof(lado));
            lado1->vert1 = vert1;
            lado1->vert2 = vert2;
            lado2->vert1 = vert2;
            lado2->vert2 = vert1;
            listaLados[indiceLado] = lado1; // lado1 = (v->vert1, w->vert2)
            listaLados[++indiceLado] = lado2; // lado2 = (v->vert2, w->vert1)
            indiceLado++;
            ladosLeidos++;

            if (ladosLeidos == cantidadLados)
                break;   
        } else {
            return NULL;
        }
    }

    Grafo grafo = malloc(sizeof(struct _GrafoSt));
    
    if (grafo == NULL)
        return NULL;

    grafo->delta = 0;
    grafo->cantidadLados = cantidadLados;
    grafo->cantidadVertices = cantidadVertices;
    grafo->vertices = malloc(cantidadVertices * sizeof(struct VerticeSt));

    u32 *grados = calloc(cantidadVertices, sizeof(u32)); // cuenta las ocurrencias de cada vertice
    u32 **vecinos = malloc(cantidadVertices * sizeof(u32*)); // guarda los vecinos de cada vertice

    // inicializamos una lista de vecinos de tamaño n para cada vertice
    for (u32 i = 0; i < cantidadVertices; i++) {
        vecinos[i] = malloc(cantidadVertices * sizeof(u32));
    }

    // calculamos el grado de cada vertice y armamos la lista de vecinos
    for (u32 i = 0; i < 2*cantidadLados; i++) {
        u32 indice = listaLados[i]->vert1; // v
        u32 indiceVecino = listaLados[i]->vert2; // w
        u32 grado = ++grados[indice]; // grado[v]

        grafo->delta = max(grafo->delta, grado);

        vecinos[indice][grado-1] = indiceVecino;
    }

    // creamos la estructura vertice y asignamos cada uno a la lista de vertices del grafo
    for (u32 i = 0; i < cantidadVertices; i++) {
        vertice vertice = malloc(sizeof(struct VerticeSt));
        vertice->color = NULL_COLOR;
        vertice->grado = grados[i];
        
        grafo->vertices[i] = vertice;
    }

    grafo->vecinos = vecinos; // asignamos el array vecinos al grafo

    // frees
    for (u32 i = 0; i < 2*cantidadLados; i++) {
        free(listaLados[i]);
        listaLados[i] = NULL;
    }
    free(listaLados);
    listaLados = NULL;
    free(grados);
    grados = NULL;

    // for (u32 i = 0; i < cantidadVertices; i++) {
    //     printf("vertice:%u, color: %u, grado: %u\n", i, grafo->vertices[i]->color, grafo->vertices[i]->grado);
    //     for (u32 j = 0; j < grafo->vertices[i]->grado; j++) {
    //         printf("\tvecino: %u\n", grafo->vecinos[i][j]);
    //     }
    // }

    return grafo;
}

void DestruirGrafo(Grafo G) {
    //Liberar memoria de la lista de vecinos de cada vertice
    for (u32 i = 0; i < G->cantidadVertices; i++) {
        free(G->vecinos[i]);
        G->vecinos[i] = NULL;
        free(G->vertices[i]);
        G->vertices[i] = NULL;
    }

    //Liberar memoria de la lista de vertices del grafo y el grafo
    free(G->vecinos);
    G->vecinos = NULL;
    free(G->vertices);
    G->vertices = NULL;
    free(G);
    G = NULL;
}

u32 NumeroDeVertices(Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);

    return G->cantidadVertices;
}

u32 NumeroDeLados(Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);

    return G->cantidadLados;
}

u32 Delta(Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);

    return G->delta;
}

u32 Grado(u32 i, Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);
        
    if (i >= NumeroDeVertices(G))
        return NULL_COLOR;
    return G->vertices[i]->grado;
}

u32 Vecino(u32 j, u32 i, Grafo G) {
    if (G==NULL) 
        exit(EXIT_FAILURE);

    if (i >= NumeroDeVertices(G) && j >= NumeroDeVertices(G))
        return -1;

    if (i >= NumeroDeVertices(G) || (i < NumeroDeVertices(G) && j >= Grado(i, G)))
        return -1;

    return G->vecinos[i][j];
}