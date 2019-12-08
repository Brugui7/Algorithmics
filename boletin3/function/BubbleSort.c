/**
 * @file
 * @brief BubbleSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include "Common.h"
#include <stdio.h>
#include "BubbleSort.h"

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 */
void basicBubbleSort(int *array, int size, char *outputFilePath) {
    int i, j, interc;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (array[j] < array[i]) {
                interc = array[j];
                array[j] = array[i];
                array[i] = interc;
            }
        }
    }

    char aux[255];
    sprintf(aux, "%s\\BubbleSortBasic%d.txt", outputFilePath, size);
    writeFile(array, size, aux);
}

