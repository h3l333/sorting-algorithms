#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/ordenamientos.h"
#include "../include/utils.h"

void copiarArray(int *dest, int *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void compararAlgoritmosOrdenamiento(int n, int caso) {
    
    int *original = malloc(n * sizeof(int));
    int *arrBurbujeo = malloc(n * sizeof(int));
    int *arrSeleccion = malloc(n * sizeof(int));
    int *arrInsercion = malloc(n * sizeof(int));
    int *arrShell = malloc(n * sizeof(int));
    int *arrQuickSort = malloc(n * sizeof(int));

    switch(caso)
    {
        case 1:
            for(int i = 0; i < n; i++)
                original[i] = i;

            copiarArray(arrShell, original, n);
            copiarArray(arrQuickSort, original, n);
            generarMejorCasoQuick(arrQuickSort, n);
            break;

        case 2:
            for(int i = 0; i < n; i++)
                original[i] = rand();

            copiarArray(arrShell, original, n);
            copiarArray(arrQuickSort, original, n);
            break;

        case 3:
            for(int i = 0; i < n; i++)
                original[i] = n - i - 1;

            copiarArray(arrQuickSort, original, n);

            generarPeorCasoShell(arrShell, n);
            break;
    }

    copiarArray(arrBurbujeo, original, n);
    copiarArray(arrSeleccion, original, n);
    copiarArray(arrInsercion, original, n);

    // Burbujeo
    clock_t inicioBurbujeo = clock();
    ordenamientoBurbujeo(arrBurbujeo, n);
    clock_t finBurbujeo = clock();

    double tiempoBurbujeo =
        (double)(finBurbujeo - inicioBurbujeo) / CLOCKS_PER_SEC;

    printf("Burbujeo: %f segundos\n", tiempoBurbujeo);

    // Seleccion
    clock_t inicioSeleccion = clock();
    ordenamientoSeleccion(arrSeleccion, n);
    clock_t finSeleccion = clock();

    double tiempoSeleccion =
        (double)(finSeleccion - inicioSeleccion) / CLOCKS_PER_SEC;

    printf("Seleccion: %f segundos\n", tiempoSeleccion);

    // Insercion
    clock_t inicioInsercion = clock();
    ordenamientoInsercion(arrInsercion, n);
    clock_t finInsercion = clock();

    double tiempoInsercion =
        (double)(finInsercion - inicioInsercion) / CLOCKS_PER_SEC;

    printf("Insercion: %f segundos\n", tiempoInsercion);

    // Shell
    clock_t inicioShell = clock();
    ordenamientoShell(arrShell, n);
    clock_t finShell = clock();

    double tiempoShell =
        (double)(finShell - inicioShell) / CLOCKS_PER_SEC;

    printf("Shell: %f segundos\n", tiempoShell);

    // QuickSort
    clock_t inicioQuickSort = clock();
    ordenamientoQuickSort(arrQuickSort, 0, n - 1);
    clock_t finQuickSort = clock();

    double tiempoQuickSort =
        (double)(finQuickSort - inicioQuickSort) / CLOCKS_PER_SEC;

    printf("QuickSort: %f segundos\n", tiempoQuickSort);

    free(original);
    free(arrBurbujeo);
    free(arrSeleccion);
    free(arrInsercion);
    free(arrShell);
    free(arrQuickSort);
}

int main(int argc, char *argv[]) {
    /*// Con propositos de testeo:

    int arrBurbujeo[] = {17, 4, 29, 12, 8, 25, 1, 19, 14, 27, 6, 21, 3, 16, 10};
    int arrInsercion[] = {17, 4, 29, 12, 8, 25, 1, 19, 14, 27, 6, 21, 3, 16, 10};
    int arrQuickSort[] = {17, 4, 29, 12, 8, 25, 1, 19, 14, 27, 6, 21, 3, 16, 10};
    int arrSeleccion[] = {17, 4, 29, 12, 8, 25, 1, 19, 14, 27, 6, 21, 3, 16, 10};
    int arrShell[] = {17, 4, 29, 12, 8, 25, 1, 19, 14, 27, 6, 21, 3, 16, 10};
    int n = 15;*/

    srand(time(NULL));

    if(argc < 2) return 1;
    // Para asegurar el pasaje de la variable "caso".
    
    int n[] = {2500, 5000, 10000, 25000, 70000, 120000, 150000};
    int nLargo = 7;
    int caso = atoi(argv[1]); // 1 en mejor caso, 2 medio y 3 peor.

    for(int i = 0; i < nLargo; i++)
    {
        printf("Caso para n = %d\n", n[i]);
        compararAlgoritmosOrdenamiento(n[i], caso);
        printf("\n");
    }

    return 0;
}