#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "ordenamientos.h"

static int estaOrdenado(int arr[], int n) {
    for (int i = 1; i < n; i++)
        if (arr[i - 1] > arr[i]) return 0;
    return 1;
}

// Ejecuta un algoritmo multiples veces y reporta ordenamiento exitoso/fallido.
static void probarCaso(const char *nombre, void (*ordenar)(int[], int),
                       int arr[], int n) {
    ordenar(arr, n);
    assert(estaOrdenado(arr, n));
    printf("%s: OK (n=%d)\n", nombre, n);
}

static void probarCasoQuickSort(const char *nombre, int arr[], int n) {
    ordenamientoQuickSort(arr, 0, n - 1);
    assert(estaOrdenado(arr, n));
    printf("QuickSort - %s: OK (n=%d)\n", nombre, n);
}

int main(void) {
    // (nombre, funcion) para los 4 algoritmos con firma (int[], int).
    struct { const char *nombre; void (*ordenar)(int[], int); } algoritmos[] = {
        {"Burbujeo",  ordenamientoBurbujeo},
        {"Seleccion", ordenamientoSeleccion},
        {"Insercion", ordenamientoInsercion},
        {"Shell",     ordenamientoShell},
    };

    // Casos fijos a probar contra cada algoritmo.
    struct { const char *nombre; int datos[6]; int n; } casos[] = {
        {"vacio",         {0},                0},
        {"un elemento",   {7},                1},
        {"ya ordenado",   {1, 2, 3, 4, 5},    5},
        {"orden inverso", {5, 4, 3, 2, 1},    5},
        {"duplicados",    {4, 2, 4, 2, 4, 2}, 6},
        {"aleatorio",     {5, 3, 8, 1, 9, 2}, 6},
    };

    int numAlgoritmos = sizeof(algoritmos) / sizeof(algoritmos[0]);
    int numCasos = sizeof(casos) / sizeof(casos[0]);

    for (int i = 0; i < numAlgoritmos; i++) {
        for (int j = 0; j < numCasos; j++) {
            int copia[6];
            memcpy(copia, casos[j].datos, sizeof(copia));

            char etiqueta[64];
            snprintf(etiqueta, sizeof(etiqueta), "%s - %s",
                     algoritmos[i].nombre, casos[j].nombre);

            probarCaso(etiqueta, algoritmos[i].ordenar, copia, casos[j].n);
        }
    }

    for (int j = 0; j < numCasos; j++) {
        int copia[6];
        memcpy(copia, casos[j].datos, sizeof(copia));
        probarCasoQuickSort(casos[j].nombre, copia, casos[j].n);
    }

    printf("Todos los casos pasaron.\n");
    return 0;
}