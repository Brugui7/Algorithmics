/**
 * @file
 * @brief BubbleSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include "Common.h"
#include <stdio.h>
#include <sys/time.h>
#include "BubbleSort.h"

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 */
void mainBubbleSort(int *array, int size, char *outputFilePath) {
    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    int swaps = 0;
    int comparations = 0;

    gettimeofday(&start, NULL);
    basicBubbleSort(array, size, &comparations, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    sprintf(aux, "%s\\BubbleSortBasic%d.txt", outputFilePath, size);
    writeFile(array, size, aux);

    printf(
            "\n-------------------- \nBUBBLE SORT\n--------------------\n"
            "Tiempo Invertido: %f\tComparaciones: %d\tIntercambios: %d\n",
            timeInvested, comparations, swaps
    );
}

/**
 *
 * @param array
 * @param size
 * @param comparations
 * @param swaps
 */
void basicBubbleSort(int *array, int size, int *comparations, int *swaps) {
    int i, j, interc;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            *comparations += 1;
            if (array[j] < array[i]) {
                interc = array[j];
                array[j] = array[i];
                array[i] = interc;
                *swaps += 1;
            }
        }
    }

}

