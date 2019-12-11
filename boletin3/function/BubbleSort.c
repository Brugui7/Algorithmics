/**
 * @file
 * @brief BubbleSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "BubbleSort.h"

/**
 * Reads the file and calls the main method
 */
void readFileAndExecuteBubbleSort(){
    FILE *file = askForFileToLoad();
    char* savePath = askForSavePath();
    int *array = (int*) malloc(sizeof(int));
    array = loadFile(file, array);
    int size = countElements(file);
    fclose(file);

    mainBubbleSort(array, size, savePath);

    free(array);
    free(savePath);
}

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
    double swaps = 0;
    double comparisons = 0;

    //########## BASIC ##########

    int *arrayCopy = (int*) malloc(sizeof(int) * size);
    arrayCopy = copyArray(array, size, arrayCopy);

    gettimeofday(&start, NULL);
    basicBubbleSort(arrayCopy, size, &comparisons, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    sprintf(aux, "%s\\BubbleSortBasic%d.txt", outputFilePath, size);
    writeFile(arrayCopy, size, aux);

    printf(
            "\n-------------------- \nBUBBLE SORT\n--------------------\n"
            "Tiempo Invertido: %f\nComparaciones: %f\nIntercambios: %f\n",
            timeInvested, comparisons, swaps
    );

    //########## IMPROVED ##########

    arrayCopy = copyArray(array, size, arrayCopy);
    swaps = 0;
    comparisons = 0;

    gettimeofday(&start, NULL);
    improvedBubbleSort(arrayCopy, size, &comparisons, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;


    sprintf(aux, "%s\\BubbleSortImproved%d.txt", outputFilePath, size);
    writeFile(arrayCopy, size, aux);

    printf(
            "\n-------------------- \nBUBBLE SORT MEJORADO\n--------------------\n"
            "Tiempo Invertido: %f\nComparaciones: %f\nIntercambios: %f\n",
            timeInvested, comparisons, swaps
    );

    free(arrayCopy);
}

/**
 *
 * @param array
 * @param size
 * @param comparisons
 * @param swaps
 */
void basicBubbleSort(int *array, int size, double *comparisons, double *swaps) {
    int i, j, interc;
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            *comparisons += 1;
            if (array[j] < array[i]) {
                interc = array[j];
                array[j] = array[i];
                array[i] = interc;
                (*swaps)++;
            }
        }
    }

}


/**
 * Adds a new variable to count the swaps and if after a full pivot iteration there are no swaps,
 * that's mean that the array is ordered
 * @param array
 * @param size
 * @param comparisons
 * @param swaps
 */
void improvedBubbleSort(int *array, int size, double *comparisons, double *swaps) {
    int i, j, interc;
    int swapsAux;
    for (i = 0; i < size - 1; i++) {
        swapsAux = 0;
        for (j = i + 1; j < size; j++) {
            *comparisons += 1;
            if (array[j] < array[i]) {
                interc = array[j];
                array[j] = array[i];
                array[i] = interc;
                (*swaps)++;
                swapsAux++;
            }
        }

        //This comparison won't be counted
        if (swapsAux == 0) return;
    }

}

