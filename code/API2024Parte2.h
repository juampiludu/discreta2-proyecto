#ifndef API2024PARTE2_H
#define API2024PARTE2_H

#include "APIG24.h"
#include "EstructuraGrafo24.h"

u32 Greedy(Grafo G, u32 *Orden);

char GulDukat(Grafo G, u32 *Orden);

char ElimGarak(Grafo G, u32 *Orden);

char OrdenNatural(Grafo G, u32 *Orden);

u32 max(u32 x, u32 y);

#endif