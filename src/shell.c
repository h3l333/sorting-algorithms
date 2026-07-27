void ordenamientoShell(int arr[], int n) {

  // Empiezo con un espacio grande y lo reduzco progresivamente.
  for (int espacio = n / 2; espacio > 0; espacio /= 2) {

    // Realizo un ordenamiento por insercion considerando el espacio actual.
    for (int i = espacio; i < n; i++) {

      // Elemento actual que debe ubicarse en su posicion correcta.
      int temp = arr[i];
      int j = i;

      // Desplazo los elementos mayores que temp para hacer espacio.
      while (j >= espacio && arr[j - espacio] > temp) {
        arr[j] = arr[j - espacio];
        j -= espacio;
      }

      // Coloco temp en su posicion definitiva.
      arr[j] = temp;
    }
  }
}