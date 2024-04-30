#ifndef APIG24_H
#define APIG24_H


#include <stdio.h>
#include <stdlib.h>


//el .h de abajo debe tener definida GrafoSt, u32 y color.
#include "EstructuraGrafo24.h"



//Grafo es un puntero a una estructura GrafoSt, la cual debe estar definida en el .h de arriba

typedef GrafoSt *Grafo;


//construccion/destruccion

//debe leer desde stdin
Grafo ConstruirGrafo();

void DestruirGrafo(Grafo G);



//funciones para extraer datos del grafo. u32 debe estar definida en el .h de arriba

u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);

// Devuelve el grado del grafo
u32 Delta(Grafo G);


//funciones de extraccion de informacion de vertices 

// Devuelve el grado del vertice i
u32 Grado(u32 i, Grafo G);

// Devuelve el color del vertice i
color Color(u32 i, Grafo G);

// Devuelve el j-ésimo vecino de i
u32 Vecino(u32 j, u32 i, Grafo G);



//funciones con colores

// Asigna el color x al vertice i
void AsignarColor(color x, u32 i, Grafo  G);

// Asigna a Color los colores de los vertices
void ExtraerColores(Grafo G, color* Color);

// Asigna a los vertices los colores de Color
void ImportarColores(color* Color, Grafo  G);

#endif