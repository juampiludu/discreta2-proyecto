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
    u32 *vecinos;
};

typedef struct VerticeSt *vertice;

struct _GrafoSt {
    u32 cantidadVertices;
    u32 cantidadLados;
    u32 delta;
    vertice *vertices;
};

u32 max(u32 x, u32 y) {
    return x > y ? x : y;
}

Grafo ConstruirGrafo() {

    u32 cantidadVertices = 0, cantidadLados = 0;
    u32 vert1, vert2;
    u32 indiceLado = 0, ladosLeidos = 0;
    char line[MAX_LINE_SIZE], edge[4];
    char p;
    lado *listaLados = NULL;
    while (fgets(line, MAX_LINE_SIZE, stdin) && ladosLeidos <= cantidadLados) {
        // salteamos todos los comentarios
        if (line[0] == 'c' || line[0] == '\n') {
            continue;

        // procesamos la cantidad de vertices y lados
        } else if (line[0] == 'p'){
            if (sscanf(line, "%c %s %u %u", &p, edge, &cantidadVertices, &cantidadLados) != 4)
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
            listaLados[indiceLado] = lado1;
            listaLados[++indiceLado] = lado2;
            indiceLado++;
            ladosLeidos++;
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

    u32 *grados = calloc(cantidadVertices, sizeof(u32));
    u32 **vecinos = malloc(cantidadVertices * sizeof(u32*));

    for (u32 i = 0; i < cantidadVertices; i++) {
        vecinos[i] = malloc(sizeof(u32));
    }

    for (u32 i = 0; i < 2*cantidadLados; i++) {
        u32 indice = listaLados[i]->vert1;
        u32 indiceVecino = listaLados[i]->vert2;
        u32 grado = ++grados[indice];

        vertice vertice = malloc(sizeof(struct VerticeSt));
        vertice->color = NULL_COLOR;
        vertice->grado = grado;
        vertice->vecinos = malloc(cantidadVertices * sizeof(u32));

        grafo->delta = max(grafo->delta, grado);
        grafo->vertices[indice] = vertice;

        vecinos[indice][grado-1] = indiceVecino;
    }

    for (u32 i = 0; i < cantidadVertices; i++) {
        realloc(vecinos[i], grafo->vertices[i]->grado * sizeof(u32));
        grafo->vertices[i]->vecinos = vecinos[i];
    }

    // frees
    free(listaLados);
    listaLados = NULL;
    free(grados);
    grados = NULL;

    for (u32 i = 0; i < cantidadVertices; i++) {
        printf("vertice:%u, color: %u, grado: %u\n", i, grafo->vertices[i]->color, grafo->vertices[i]->grado);
        for (u32 j = 0; j < grafo->vertices[i]->grado; j++) {
            printf("\tvecino: %u\n", grafo->vertices[i]->vecinos[j]);
        }
    }

    return grafo;
}
