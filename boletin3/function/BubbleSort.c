/**
 * @file
 * @brief BubbleSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include "../model/BubbleSort.h"
#include "Common.h"
#include <stdio.h>

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 * @return
 */
void basicBubbleSort(int *array, int size, char *outputFilePath) {
    int i, j, interc;
    for (i = 0; i < size - 1; i++){
        for (j = i + 1; j < size; j++) {
            if (array[j] < array[i]) {
                interc = array[j];
                array[j] = array[i];
                array[i] = interc;
            }
        }
    }

    sprintf(outputFilePath, "%s\\BubbleSortBasic%d.txt", outputFilePath, size);
    writeFile(array, size, outputFilePath);
}

