void ordenamientoInsercion(int arr[], int n) {
  for (int i = 1; i < n; ++i) {
    int valorAInsertar = arr[i];
    int j = i - 1;

    // Mientras j sea mayor o igual a cero y el valor en el indice j sea
    // mayor que el valor a insertar...
    while (j >= 0 && arr[j] > valorAInsertar) {
      arr[j + 1] = arr[j];
      j = j - 1;
      // ... se intercambian los valores en los indices adyacentes de tal
      // modo de ordenar el vector. "Retrocedemos" con j hasta encontrar
      // la posicion correcta.
    }
    arr[j + 1] = valorAInsertar;
    // Recien al llegar a la pos. correcta insertamos el valor de manera
    // ordenada.
  }
}