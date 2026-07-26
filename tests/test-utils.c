#include <stdio.h>
#include "../include/utils.h"

void imprimirArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main(void)
{
    int arr[15];

    // Pruebo el mejor caso de QuickSort.
    for (int i = 0; i < 15; i++)
        arr[i] = i;

    generarMejorCasoQuick(arr, 15);

    printf("Quick mejor caso:\n");
    imprimirArray(arr, 15);

    // Aproximo el peor caso de Shell.
    generarPeorCasoShell(arr, 15);

    printf("\nShell peor caso:\n");
    imprimirArray(arr, 15);

    return 0;
}