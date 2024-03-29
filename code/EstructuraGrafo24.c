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
    grafo->delta = 0;
    grafo->cantidadLados = cantidadLados;
    grafo->cantidadVertices = cantidadVertices;
    grafo->vertices = malloc(cantidadVertices * sizeof(struct VerticeSt));

    for (u32 i = 0; i < 2*cantidadLados; i++) {
        
    }
}
