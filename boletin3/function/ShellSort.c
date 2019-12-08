/**
 * @file
 * @brief ShellSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include <Common.h>
#include <stdio.h>
#include <ShellSort.h>

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 */
void shellSort(int *array, int size, char *outputFilePath) {

    int i, j, interval, temp;
    interval = calcIncrementSize(size);
    while (interval > 0) {
        for (i = interval; i < size; i++) {
            j = i;
            temp = array[i];
            while ((j >= interval) && (array[j - interval] > temp)) {
                array[j] = array[j - interval];
                j = j - interval;
            }
            array[j] = temp;
        }
        interval = interval / 3;
    }



    char aux[255];
    sprintf(aux, "%s\\ShellSort%d.txt", outputFilePath, size);
    writeFile(array, size, aux);
}

/**
 * Calcs the first increment to apply
 * Uses the knuth algorithm
 * @param size
 * @return
 */
int calcIncrementSize(int size){
    int increment = 1;
    for (int i = 0; i < size; ++i) {
        increment = increment * 3 + 1;
    }
    return increment;
}


