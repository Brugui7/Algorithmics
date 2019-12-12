/**
 * @file
 * @brief SelectionSort implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include <Common.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <SelectionSort.h>

/**
 * Reads the file and calls the main method
 */
void readFileAndExecuteSelectionSort(){
    FILE *file = askForFileToLoad();
    char* savePath = askForSavePath();
    int *array = (int*) malloc(sizeof(int));
    array = loadFile(file, array);
    int size = countElements(file);
    fclose(file);

    mainSelectionSort(array, size, savePath);

    free(array);
    free(savePath);
}

/**
 *
 * @param array
 * @param size
 * @param outputFilePath
 */
void mainSelectionSort(int *array, int size, char *outputFilePath){
    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    double swaps = 0;
    double comparisons = 0;

    int *arrayCopy = (int*) malloc(sizeof(int) * size);
    arrayCopy = copyArray(array, size, arrayCopy);

    //########## BASIC ##########

    gettimeofday(&start, NULL);
    basicSelectionSort(arrayCopy, size, &comparisons, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    sprintf(aux, "%s\\SelectionSortBasic%d.txt", outputFilePath, size);
    writeFile(arrayCopy, size, aux);


    printf(
            "\n-------------------- \nSELECTION SORT\n--------------------\n"
            "Tiempo Invertido: %f\nComparaciones: %f\nIntercambios: %f\n",
            timeInvested, comparisons, swaps
    );

    //########## IMPROVED ##########

    comparisons = 0;
    swaps = 0;
    arrayCopy = copyArray(array, size, arrayCopy);

    gettimeofday(&start, NULL);
    improvedSelectionSort(arrayCopy, size, &comparisons, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    sprintf(aux, "%s\\SelectionSortImproved%d.txt", outputFilePath, size);
    writeFile(arrayCopy, size, aux);



    printf(
            "\n-------------------- \nSELECTION SORT MEJORADO\n--------------------\n"
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
void basicSelectionSort(int *array, int size, double *comparisons, double *swaps) {

    int i, j, pos, interc;
    for (i = 0; i < size - 1; i++) {
        pos = i;
        for (j = i + 1; j < size; j++) {
            *comparisons += 1;
            if (array[j] < array[pos]) {
                pos = j;
            }
        }
        (*swaps)++;
        interc = array[pos];
        array[pos] = array[i];
        array[i] = interc;

    }

}


/**
 * This method is like the basic one but checks if the actual pivot is in the correct position
 * @param array
 * @param size
 * @param comparisons
 * @param swaps
 */
void improvedSelectionSort(int *array, int size, double *comparisons, double *swaps) {

    int i, j, pos, interc;
    for (i = 0; i < size - 1; i++) {
        pos = i;
        for (j = i + 1; j < size; j++) {
            *comparisons += 1;
            if (array[j] < array[pos]) {
                pos = j;
            }
        }
        if (i != pos){
            interc = array[pos];
            array[pos] = array[i];
            array[i] = interc;
            (*swaps)++;
        }

    }

}

