/**
 * @file
 * @brief Common functions implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include <stdio.h>
#include "../model/Common.h"

/**
 *
 * @param array
 * @param outputFileName
 */
void writeFile(int *array, int size, char *outputFileName){

    FILE *file = NULL;
    if ((file = fopen(outputFileName, "w")) == NULL){
        printf("Error al abrir el fichero en modo escritura");
    }

    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d\n", array[i]);
    }

    fclose(file);
}