/**
 * @file
 * @brief QuickSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */
#include "QuickSort.h"
#include <Common.h>
#include <stdio.h>

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 * @param pivotOption int 1 | 2 | 3
 */
void quickSort(int *array, int size, char *outputFilePath, int pivotOption) {

    quickSortRec(array, 0, size - 1, pivotOption);

    char aux[255];
    sprintf(aux, "%s\\QuickSort%d.txt", outputFilePath, size);
    writeFile(array, size, aux);
}

/**
 *
 * @param array
 * @param i
 * @param j
 */
void swap(int *array, int i, int j) {
    int interc;

    interc = array[i];
    array[i] = array[j];
    array[j] = interc;
}

/**
 *
 * @param array
 * @param ini
 * @param fin
 * @param pivotOption
 */
void quickSortRec(int *array, int ini, int fin, int pivotOption) {

    int pivot;
    int i, j;

    // Caso vector con 1 solo número --> No hacer nada
    if (ini >= fin) return;

    // Caso vector con 2 números --> Comprobar si es necesario ordenarlos
    if (ini + 1 == fin) {
        if (array[ini] > array[fin])  // No están ordenados los dos números, intercambiar
            swap(array, ini, fin);
        return;
    }

    // Resto de casos --> vector con 3 números o más

    // Pivote --> La posición de mitad del vector
    int pivotPosition;
    switch (pivotOption){
        case 1:
            pivotPosition = getMidAsPivot(ini, fin);
            break;
        case 2:
            //TODO
            break;
        case 3:
            //TODO
            break;
        default:
            return;
    }

    // Intercambiar pivot por el último elemento
    swap(array, pivotPosition, fin);
    pivot = array[fin];

    // empezamos la particion
    for (i = ini, j = fin - 1;;) {
        while ((i <= fin - 1) && (array[i] < pivot)) i++;
        while ((j >= ini) && (pivot < array[j])) j--;

        if (i < j) {  // Todavía no se han intercambiado los índices, intercambiar números
            swap(array, i, j);
            i++;
            j--;
        } else  // Se han intercambiando los índices, fin de la particion
            break;
    }

    //colocación del pivot en su sitio
    swap(array, i, fin);
    //termina particion; //llamadas recursivas
    quickSortRec(array, ini, i - 1, pivotOption);  // Vector de la izquierda del pivot
    quickSortRec(array, i + 1, fin, pivotOption);  // Vector de la derecha del pivot
}


int getMidAsPivot(int startPosition, int endPosition){
    return (startPosition + endPosition) / 2;
}