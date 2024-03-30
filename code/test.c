#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"

// Función para imprimir el resultado de una prueba
void print_result(const char *test_name, bool result) {
    printf("%s: %s\n", test_name, result ? "PASSED" : "FAILED");
}

// Función para comparar dos enteros sin signo de 32 bits
bool assert_not_equal_u32(u32 expected, u32 actual) {
    return expected != actual;
}

// Función para comparar dos colores
bool assert_equal_color(color expected, color actual) {
    return expected == actual;
}

// Función para realizar pruebas sobre la creación del grafo
void test_ConstruirGrafo(Grafo G) {
    bool result = (G != NULL); // Verifica si se creó correctamente el grafo
    print_result("test_ConstruirGrafo", result);
}

// Función para realizar pruebas sobre el número de vértices y lados del grafo
void test_NumeroDeVerticesYLados(Grafo G) {
    u32 num_vertices = NumeroDeVertices(G);
    u32 num_lados = NumeroDeLados(G);
    bool result = assert_not_equal_u32(0, num_vertices) && assert_not_equal_u32(0, num_lados);
    print_result("test_NumeroDeVerticesYLados", result);
}

// Función para realizar pruebas sobre la asignación y extracción de colores
void test_AsignarYExtraerColores(Grafo G) {
    u32 num_vertices = NumeroDeVertices(G);
    color *colores = (color *)malloc(num_vertices * sizeof(color));
    // Asignar colores a los vértices
    for (u32 i = 0; i < num_vertices; i++) {
        AsignarColor(i % 10, i, G); // Asignar colores del 0 al 9 circularmente
    }
    // Extraer colores y verificar
    ExtraerColores(G, colores);
    bool result = true;
    for (u32 i = 0; i < num_vertices; i++) {
        result = result && assert_equal_color(i % 10, colores[i]);
    }
    print_result("test_AsignarYExtraerColores", result);
    free(colores);
}

int main() {
    Grafo G = ConstruirGrafo();

    test_ConstruirGrafo(G);
    test_NumeroDeVerticesYLados(G);
    test_AsignarYExtraerColores(G);
    
    if (G != NULL) DestruirGrafo(G);

    return 0;
}
