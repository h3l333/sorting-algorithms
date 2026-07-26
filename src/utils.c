#include "../include/utils.h"
#include <stdio.h>

void imprimirVector(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void construirMejorQuick(int arr[], int izq, int der)
{
    if (izq >= der)
        return;

    int med = (izq + der) / 2;

    construirMejorQuick(arr, izq, med - 1);
    construirMejorQuick(arr, med + 1, der);

    swap(&arr[med], &arr[der]);
}

void generarMejorCasoQuick(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;

    construirMejorQuick(arr, 0, n - 1);
}

void generarPeorCasoShell(int arr[], int n)
{
    int bajo = 0;
    int alto = n - 1;

    int k = 0;

    while (bajo <= alto)
    {
        arr[k++] = bajo++;

        if (bajo <= alto)
            arr[k++] = alto--;
    }
}