/**
 * @file
 * @brief ShellSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include <Common.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ShellSort.h>

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 */
void mainShellSort(int *array, int size, char *outputFilePath) {
    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    int swaps = 0;
    int comparisons = 0;

    int *arrayCopy = (int*) malloc(sizeof(int) * size);
    arrayCopy = copyArray(array, size, arrayCopy);

    gettimeofday(&start, NULL);
    shellSort(arrayCopy, size, &comparisons, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    sprintf(aux, "%s\\ShellSort%d.txt", outputFilePath, size);
    writeFile(arrayCopy, size, aux);

    printf(
            "\n-------------------- \nSHELL SORT\n--------------------\n"
            "Tiempo Invertido: %f\nComparaciones: %d\nIntercambios: %d\n",
            timeInvested, comparisons, swaps
    );


    free(arrayCopy);
}

/**
 * ShellSort implementations using the knuth method
 * @param array
 * @param size
 * @param comparisons
 * @param swaps
 */
void shellSort(int *array, int size, int *comparisons, int *swaps) {

    int i, j, interval, temp;
    interval = calcIncrementSize(size);
    while (interval > 0) {
        for (i = interval; i < size; i++) {
            j = i;
            temp = array[i];

            *comparisons += 1;
            while ((j >= interval)) {
                *comparisons += 2;
                if((array[j - interval] > temp)){
                    array[j] = array[j - interval];
                    j = j - interval;

                    *swaps += 1;
                } else {
                    *comparisons -= 1;
                    //Overkill but a possible solution to count the comparisons without changing the "process" of the while
                    break;
                }

            }
            array[j] = temp;
        }

        //returns interval /2 or interval/3 depending of the data size
        //Because the knuth formula is better for mid-sized data
        interval = size > 50000 ?  interval / 2 : interval / 3;
    }
}

/**
 * Calculates the first increment to apply
 * Uses the knuth algorithm
 * @param size
 * @return
 */
int calcIncrementSize(int size) {
    if (size > 2) return size / 2;

    int increment = 1;
    int limit = (size - 1) / 3;
    for (int i = 0; i < limit; ++i) {
        increment = increment * 3 + 1;
    }
    return increment;

}