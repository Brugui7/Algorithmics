/**
 * @file
 * @brief Main menu for the third task
 * @author Alejandro Brugarolas
 * @since 2019-12
 */

#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
#include "QuickSort.h"




void showMenu();
int *loadFile(FILE *file, int* array);
int countNumbers(FILE *file);
FILE *askForFileToLoad();
void doAllSortings();


/**
 * Shows all the options and calls the appropriate function depending of the chosen option
 */
void showMenu() {

    int option = 0;
    while (option != 3) {
        printf("\n############### MENU BOLETÍN 3 ###############\n"
               "Indique qué acción desea realizar\n"
               "\t1. Ejecutar todos los algoritmos.\n"
               "\t2. TODO.\n"
               "\t3. Salir.\n");
        printf("> ");

        scanf("%d", &option);
        fflush(stdin);
        switch (option) {
            case 1:
                doAllSortings();
                break;
            case 2:
                break;
            case 3:
                printf("Saliendo...");
                break;
            default:
                printf("Por favor seleccione una opción válida\n");
                break;
        }
    }
}



/**
 * Calls all the algorithms' functions to sort a given file
 */
void doAllSortings(){
    FILE *file = askForFileToLoad();
    char savePath[255] = "";
    int *arrayCopy;
    printf("Introduzca la ruta a la carpeta donde se almacenarán los ficheros de salida\n>");
    gets(savePath);
    int *array = (int*) malloc(sizeof(int));
    array = loadFile(file, array);
    int size = countNumbers(file);
    fclose(file);
    arrayCopy = (int*) malloc(sizeof(int) * size);

    arrayCopy = copyArray(array, size, arrayCopy);
    mainBubbleSort(arrayCopy, size, savePath);
    mainSelectionSort(array, size, savePath);
    mainShellSort(array, size, savePath);
    mainQuickSort(arrayCopy, size, savePath, 1);
    mainQuickSort(arrayCopy, size, savePath, 2);
    mainQuickSort(arrayCopy, size, savePath, 3);

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
 * Counts all the numbers on a file
 * Other solution could be storing it in a global variable at the loadFile method, but I don't like globals
 * @param file
 * @return
 */
int countNumbers(FILE *file){
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




int main() {
    showMenu();
}