/**
 * @file
 * @brief QuickSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */
#include "QuickSort.h"
#include <Common.h>
#include <stdio.h>
#include <sys/time.h>

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 * @param pivotOption int 1 | 2 | 3
 */
void mainQuickSort(int *array, int size, char *outputFilePath, int pivotOption) {
    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    int swaps = 0;
    int comparations = 0;

    gettimeofday(&start, NULL);
    quickSortRec(array, 0, size - 1, pivotOption, &comparations, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    sprintf(aux, "%s\\QuickSort%d.txt", outputFilePath, size);
    writeFile(array, size, aux);

    printf("\n-------------------- \nQUICK SORT");

    if (pivotOption == 1){
        printf(" | Pivote medio ");
    } else {
        printf(" | %s ", pivotOption == 2 ? "Pivote aleatorio" : "Pivote mediana");
    }

    printf(
            "\n--------------------\n"
            "Tiempo Invertido: %f\tComparaciones: %d\tIntercambios: %d\n",
            timeInvested, comparations, swaps
    );
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
 * The algorithm itself
 * @param array
 * @param ini
 * @param fin
 * @param pivotOption
 * @param comparations
 * @param swaps
 */
void quickSortRec(int *array, int ini, int fin, int pivotOption, int *comparations, int *swaps) {

    int pivot;
    int i, j;

    //Array with only one element
    if (ini >= fin) return;

    //If the array has two elements check if they are in order and swaps them if not
    if (ini + 1 == fin) {
        *comparations += 1;
        if (array[ini] > array[fin]){
            *swaps += 1;
            swap(array, ini, fin);
        }

        return;
    }

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

    // Swaps the pivot with the last element
    swap(array, pivotPosition, fin);
    *swaps += 1;

    pivot = array[fin];

    // starts the partition
    for (i = ini, j = fin - 1;;) {

        while ((i <= fin - 1) && (array[i] < pivot)){
            i++;
        }
        while ((j >= ini) && (pivot < array[j])){
            j--;
        }

        if (i < j) {  // Checks if the indexes passed each other
            swap(array, i, j);
            *swaps += 1;
            i++;
            j--;
        } else  // No swaps
            break;
    }

    //colocación del pivot en su sitio
    swap(array, i, fin);
    //termina particion; //llamadas recursivas
    quickSortRec(array, ini, i - 1, pivotOption, comparations, swaps);
    quickSortRec(array, i + 1, fin, pivotOption, comparations, swaps);
}


int getMidAsPivot(int startPosition, int endPosition){
    return (startPosition + endPosition) / 2;
}