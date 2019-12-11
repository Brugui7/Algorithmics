/**
 * @file
 * @brief Common functions implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include <stdio.h>
#include <stdlib.h>
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

/**
 * Copies the unordered array to other so the file has not to be read everytime
 * @param arraySource
 * @param size
 * @param arrayDestination
 * @return
 */
int* copyArray(int *arraySource, int size, int *arrayDestination){
    for (int i = 0; i < size; ++i) {
        arrayDestination[i] = arraySource[i];
    }
    return arrayDestination;
}

FILE *askForFileToLoad(){
    char fileName[255] = "";
    FILE *file = NULL;

    //Asks for the file to load the data
    while (file == NULL) {
        printf("Introduzca la ruta al archivo de datos\n>");
        gets(fileName);
        fflush(stdin);
        file = fopen(fileName, "r");
    }

    return file;
}

/**
 * Loads the file and returns a list of songs
 * @param songList
 * @param file
 * @return songs list
 */
int *loadFile(FILE *file, int* array){
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t bufferSize = 255;

    int i = 0;
    while(fgets(buffer, bufferSize, file) != NULL){
        if (i != 0){
            array = (int*) realloc(array, sizeof(int) * (i + 1));
        }

        array[i] = atoi(buffer);
        i++;

    }
    free(buffer);

    return array;
}

/**
 * Counts all the elements on a file
 * Other solution could be storing it in a global variable at the loadFile method, but I don't like globals
 * @param file
 * @return
 */
int countElements(FILE *file){
    char *buffer = (char *) malloc(sizeof(char) * 255);
    size_t bufferSize = 255;
    int numbers = 0;
    //Puts the pointer on the first line of the file
    rewind(file);
    while(fgets(buffer, bufferSize, file) != NULL){
        numbers++;
    }
    free(buffer);

    return numbers;
}
