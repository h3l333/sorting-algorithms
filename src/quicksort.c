#include "../include/utils.h"

// particion() retorna el indice final en donde queda el pivote una vez que
// todos los elementos han sido ordenados.
int particion(int arr[], int min, int max) {

  // Elijo un pivote para dividir el arreglo en 2 partes:
  int pivote = arr[max];

  // i indica la posicion del ultimo elemento examinado menor que el pivote.
  // La primera vez que se ejecuta la funcion i = -1, dado que aun no conocemos
  // dentro del arreglo a un elemento que sea menor que el elemento en la pos.
  // min.
  int i = min - 1;

  // Itero sobre el arreglo y voy swapeando segun corresponda.
  for (int j = min; j <= max - 1; j++) {
    if (arr[j] < pivote) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  // Muevo el pivote de tal modo que este despues de los elementos mas chicos
  // que el y retorno su posicion.
  swap(&arr[i + 1], &arr[max]);
  return i + 1;
}

void ordenamientoQuickSort(int arr[], int min, int max) {
  if (min < max) {

    int pi = particion(arr, min, max);

    // Implemento recursividad para ordenar el arreglo.
    ordenamientoQuickSort(arr, min, pi - 1);
    ordenamientoQuickSort(arr, pi + 1, max);
  }
}
