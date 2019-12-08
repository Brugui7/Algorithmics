/**
 * @file
 * @brief SelectionSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include <Common.h>
#include <stdio.h>

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 */
void basicSelectionSort(int *array, int size, char *outputFilePath) {

    int i, j, pos, interc;
    for (i = 0; i < size - 1; i++) {
        pos = i;
        for (j = i + 1; j < size; j++) {
            if (array[j] < array[pos]) {
                pos = j;
            }
        }
        interc = array[pos];
        array[pos] = array[i];
        array[i] = interc;
    }

    char aux[255];
    sprintf(aux, "%s\\SelectionSortBasic%d.txt", outputFilePath, size);
    writeFile(array, size, aux);
}


