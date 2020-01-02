/**
 * @file
 * @brief Direct Search implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "DirectSearch.h"
#include <string.h>

/**
 * Reads the file and calls the main method
 */
void readFileAndExecuteDirectSearch(){
    FILE *file = askForFileToLoad();
    char* array = NULL;
    char* pattern = askForPattern();
    array = loadFile(file, array);
    fclose(file);


    mainDirectSearch(array, pattern);

    free(array);
    free(pattern);
}

/**
 *
 * @param array
 * @param pattern
 */
void mainDirectSearch(char *array, char *pattern){

    //For time measuring
    struct timeval start, end;
    double timeInvested;

    //For measuring
    double restarts = 0;


    gettimeofday(&start, NULL);
    int* foundPositions = doDirectSearch(array, pattern, &restarts);
    gettimeofday(&end, NULL);
    timeInvested = ((end.tv_sec - start.tv_sec) * 1000000u +
                    end.tv_usec - start.tv_usec) / 1.e6;

    printf(
            "\n-------------------- \nDIRECT SEARCH\n--------------------\n"
            "Tiempo Invertido: %f\nReinicios: %.2f\n",
            timeInvested, restarts
    );

    if (foundPositions[0] == -1){
        printf("No se ha encontrado ninguna coincidencia\n");
    } else {
        printf("Se ha encontrado la subcadena en las siguientes posiciones:\n");
        int i = 0;
        while (foundPositions[i] != -1){
            printf("%d ", foundPositions[i++]);
        }
        printf("\n");
    }

    free(foundPositions);
}

/**
 * The algorithm itself
 * @param array
 * @param restarts
 * @return array with the positions where the pattern was found
 */
int *doDirectSearch(char *array, char *pattern, double *restarts){
    int textSize = strlen(array);
    int patternSize = strlen(pattern);
    int patternPosition;
    int *foundPositions = (int*) malloc(sizeof(int));
    foundPositions[0] = -1;
    int foundPositionsCounter = 0;

    if (patternSize > textSize){
        foundPositions[0] = -1;
        return foundPositions;
    }

    for (int i = 0; i < textSize; i++) {
        patternPosition = i;
        for (int j = 0; j <= patternSize; j++) {
            if (pattern[j] == array[patternPosition]){
                patternPosition++;
            } else if(j == patternSize) {
                foundPositionsCounter++;
                foundPositions = (int*) realloc(foundPositions, sizeof(int) * (foundPositionsCounter + 1));
                foundPositions[foundPositionsCounter - 1] = i;
                foundPositions[foundPositionsCounter] = -1; //To know the end of the array
                break;
            } else {
                (*restarts)++;
                break;
            }
        }
    }

    return foundPositions;
    //TODO si no se ha encontrado
}


