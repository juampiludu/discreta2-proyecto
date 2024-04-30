#ifndef API2024PARTE2_H
#define API2024PARTE2_H

#include "APIG24.h"

u32 Greedy(Grafo G, u32 *Orden);

char GulDukat(Grafo G, u32 *Orden);

char ElimGarak(Grafo G, u32 *Orden);

char OrdenNatural(Grafo G, u32 *Orden);

char OrdenDecreciente(Grafo G, u32 *Orden);

char OrdenParImpar(Grafo G, u32 *Orden);

char OrdenGradoDecreciente(Grafo G, u32 *Orden);

char OrdenPrimosCreciente(Grafo G, u32 *Orden);

void printArray(u32 *arr, u32 n);

u32 max(u32 x, u32 y);

u32 min(u32 x, u32 y);

#endif