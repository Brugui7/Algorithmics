/**
 * @file
 * @brief ShellSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include <Common.h>
#include <stdio.h>
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
    int comparations = 0;

    gettimeofday(&start, NULL);
    shellSort(array, size, &comparations, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    sprintf(aux, "%s\\ShellSort%d.txt", outputFilePath, size);
    writeFile(array, size, aux);

    printf(
            "\n-------------------- \nSHELL SORT\n--------------------\n"
            "Tiempo Invertido: %f\tComparaciones: %d\tIntercambios: %d\n",
            timeInvested, comparations, swaps
    );
}

/**
 * ShellSort implementations using the knuth method
 * @param array
 * @param size
 * @param comparations
 * @param swaps
 */
void shellSort(int *array, int size, int *comparations, int *swaps) {

    int i, j, interval, temp;
    interval = calcIncrementSize(size);
    while (interval > 0) {
        for (i = interval; i < size; i++) {
            j = i;
            temp = array[i];

            while ((j >= interval) && (array[j - interval] > temp)) {
                array[j] = array[j - interval];
                j = j - interval;

                *swaps += 1;
            }
            array[j] = temp;
        }
        interval = interval / 3;
    }
}

/**
 * Calcs the first increment to apply
 * Uses the knuth algorithm
 * @param size
 * @return
 */
int calcIncrementSize(int size) {
    int increment = 1;
    for (int i = 0; i < size; ++i) {
        increment = increment * 3 + 1;
    }
    return increment;
}


