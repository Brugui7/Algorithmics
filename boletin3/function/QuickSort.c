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
#include <stdlib.h>


/**
 * Reads the file and calls the main method
 */
void readFileAndExecuteQuickSort(){
    FILE *file = askForFileToLoad();
    char* savePath = askForSavePath();
    int *array = (int*) malloc(sizeof(int));
    array = loadFile(file, array);
    int size = countElements(file);
    fclose(file);

    mainQuickSort(array, size, savePath, 1);
    mainQuickSort(array, size, savePath, 2);
    mainQuickSort(array, size, savePath, 3);
    free(array);
    free(savePath);
}

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
    double swaps = 0;
    double comparisons = 0;

    int *arrayCopy = (int*) malloc(sizeof(int) * size);
    arrayCopy = copyArray(array, size, arrayCopy);

    gettimeofday(&start, NULL);
    quickSortRec(arrayCopy, 0, size - 1, pivotOption, &comparisons, &swaps);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    char aux[255];
    if (pivotOption == 1){
        sprintf(aux, "%s\\QuickSortMidPivot%d.txt", outputFilePath, size);
    } else {
        sprintf(aux, "%s\\QuickSort%sPivot%d.txt", outputFilePath, pivotOption == 2 ? "Rand" : "Median", size);
    }

    writeFile(arrayCopy, size, aux);

    printf("\n-------------------- \nQUICK SORT");

    if (pivotOption == 1){
        printf(" | Pivote medio ");
    } else {
        printf(" | %s ", pivotOption == 2 ? "Pivote aleatorio" : "Pivote mediana");
    }

    printf(
            "\n--------------------\n"
            "Tiempo Invertido: %f\nComparaciones: %f\nIntercambios: %f\n",
            timeInvested, comparisons, swaps
    );

    free(arrayCopy);
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
 * @param comparisons
 * @param swaps
 */
void quickSortRec(int *array, int ini, int fin, int pivotOption, double *comparisons, double *swaps) {

    int pivot;
    int i, j;

    //Array with only one element
    if (ini >= fin) return;

    //If the array has two elements check if they are in order and swaps them if not
    if (ini + 1 == fin) { //I don't count this one
        (*comparisons)++;
        if (array[ini] > array[fin]){
            (*swaps)++;
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
            pivotPosition = getRandAsPivot(ini, fin);
            break;
        case 3:
            pivotPosition = getMedianAsPivot(array, ini, fin, comparisons);
            break;
        default:
            return;
    }

    // Swaps the pivot with the last element
    swap(array, pivotPosition, fin);
    (*swaps)++;

    pivot = array[fin];

    // starts the partition
    for (i = ini, j = fin - 1;;) {


        (*comparisons)++;
        while ((i <= fin - 1)){
            *comparisons += 2; // Counts the two next comparisons
            if (array[i] < pivot){
                i++;
            } else {
                *comparisons -= 1; // Te while will not be evaluated
                break;
            }
        }

        (*comparisons)++;
        while (j >= ini){
            *comparisons += 2; // Counts the two next comparisons
            if(pivot < array[j]){
                j--;
            } else {
                *comparisons -= 1; // Te while will not be evaluated
                break;
            }
        }

        (*comparisons)++;
        if (i < j) {  // Checks if the indexes passed each other
            swap(array, i, j);
            *swaps += 1;
            i++;
            j--;
        } else {  // No swaps
            break;
        }
    }

    //colocación del pivot en su sitio
    *swaps += 1;
    swap(array, i, fin);
    //termina particion; //llamadas recursivas
    quickSortRec(array, ini, i - 1, pivotOption, comparisons, swaps);
    quickSortRec(array, i + 1, fin, pivotOption, comparisons, swaps);
}

/**
 * Returns the position in the middle of the array
 * @param startPosition
 * @param endPosition
 * @return
 */
int getMidAsPivot(int startPosition, int endPosition){
    return (startPosition + endPosition) / 2;
}

/**
 * Returns a Random int number between start and end
 * @param startPosition
 * @param endPosition
 * @return
 */
int getRandAsPivot(int startPosition, int endPosition){
    return (rand() % (endPosition - startPosition + 1)) + startPosition;
}

/**
 *
 * @param array
 * @param startPosition
 * @param endPosition
 * @param comparisons
 * @return
 */
int getMedianAsPivot(const int *array, int startPosition, int endPosition, double *comparisons){
    //For code reuse
    int middlePosition = getMidAsPivot(startPosition, endPosition);

    (*comparisons)++;
    if (array[startPosition] >= array[endPosition]){
        (*comparisons)++;
        if (array[startPosition] <= array[middlePosition]){
            return startPosition;
        } else if(array[endPosition] <= array[middlePosition]){
            (*comparisons)++;
            return middlePosition;
        }
        (*comparisons)++;
        return endPosition;
    } else {
        (*comparisons)++;
        if (array[startPosition] >= array[middlePosition]){
            return startPosition;
        } else if (array[endPosition] >= array[middlePosition]){
            (*comparisons)++;
            return middlePosition;
        }
        return endPosition;
    }
}