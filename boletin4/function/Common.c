/**
 * @file
 * @brief Common functions implementations
 * @author Alejandro Brugarolas
 * @since 2019-12
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/Common.h"

/**
 *
 * @return FILE
 */
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
 *
 * @return string pattern to find
 */
char *askForPattern(){
    char *pattern = (char*) malloc(sizeof(char) * 255);
    printf("Introduzca la subcadena a buscar\n>");
    gets(pattern);
    fflush(stdin);
    realloc(pattern, sizeof(char) * (strlen(pattern) + 1));
    return pattern;
}

/**
 * Loads the file and returns the array
 * @param file
 * @param array
 * @return char array
 */
char *loadFile(FILE *file, char* array){
    int size = 0;
    //Gets the size of the text in the file
    while(fgetc(file) != EOF) size++;
    //Sets the file pointer on the start of the file
    rewind(file);

    array = (char *) malloc(sizeof(char) * (size + 1));
    fread(array, size, 1, file);

    return array;
}