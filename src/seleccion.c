// El algoritmo de ordenamiento de seleccion es uno basado en comparaciones,
// en donde repetidas veces se elige el menor valor de la porcion desordenada
// de un vector y se "susitituye" en el elemento actual, avanzando hasta ordenar
// el array.
// Por ejemplo, en el array desordenado [5, 9, 10, 1]:
//      - Empezamos con 5 siendo nuestro elemento actual y "menor valor".
//      - Avanzamos sobre el array, en cada iteracion haciendo que el "elemento
//      actual" sea el indice siguiente al previo.
//      - Una vez que el valor actual "caiga" sobre un valor menor a nuestro
//      menor valor actual, se cambian de lugar los nros. y luego se "achica"
//      la porcion sin ordenar de manera acorde.

void ordenamientoSeleccion(int arr[], int n) {
  // Toma el array a ordenar y el nro. de elementos que tiene.
  for (int i = 0; i < n - 1; i++) {

    int minIndice = i;

    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndice]) {
        // Itero sobre los elementos del array siguientes al menor actual.
        // "Cambio" el menor actual unicamente si encuentro un valor mas chico.
        // En caso de no encontrarlo, simplemente avanzo al siguiente indice.
        minIndice = j;
      }
    }

    // Muevo el minimo elemento a su posicion correcta.
    int temp = arr[i]; // Asigno a una variable temporal el valor en i para no "perderlo".
    arr[i] = arr[minIndice];
    arr[minIndice] = temp;
  }
}
