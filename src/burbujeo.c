// El ordenamiento a traves de burbujeo es un algoritmo bastante simple que
// funciona con una serie de "intercambios" entre los indices vecinos dentro
// de un vector.
// Suponiendo un orden de menor a mayor, lo que se hace es recorrer el vector
// de a dos celdas e intercambiar las celdas en caso de que la 2da sea menor
// que la 1ra.
// En su version optimizada, se va "achicando" el rango de comparacion a medida
// que avanzamos, con la nocion de que los ultimos i elementos no necesitaran
// ser ordenados, y se frena el bucle al detectar que no hubieron pases dentro
// de una iteracion.
// Eso dicho, esta implementacion representa su version sin optimizar.

#include <stdbool.h>

void intercambiar(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void ordenamientoBurbujeo(int arr[], int n) {
  int i, j;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        intercambiar(&arr[j], &arr[j + 1]);
      }
    }
  }
}